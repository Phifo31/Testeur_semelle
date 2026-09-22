

#include "Arduino.h"

#include "ui/actions.h"
#include "ui/ui.h"
#include "ui/vars.h"

#include "canbus.h"
#include "main.h"



#define OUTPUT_ON 0xFF00
#define OUTPUT_OFF 0x0000

static bool state_machine_start = false;
static bool state_machine_stop = false;
static bool canbus_flag = false;
static bool capteur_butee_basse = false;
static bool capteur_butee_haute = false;


struct CONFIGURATIONS {
  uint16_t nb_cycles;
  int16_t timeout_aller;
  int16_t timeout_retour_libre;

} configurations;

typedef enum { ARRET, POUSSE, TIRE, FREINE, STOP, RELACHE } action_t;


/**
 * @brief
 *
 * @param val
 */
void process_input(uint8_t val) {
  capteur_butee_basse = ((val & MASQUE_CAPTEUR_BUTEE_BASSE) != 0) ? true : false;
  set_var_led_capteur_bas(capteur_butee_basse);

  capteur_butee_haute = ((val & MASQUE_CAPTEUR_BUTEE_HAUTE) != 0) ? true : false;
  set_var_led_capteur_haut(capteur_butee_haute);

  canbus_flag = true;
}

/**
 * @brief
 *
 * @param a
 */
void process_output(action_t a) {
  switch (a) {
  case ARRET:
    CANBUS_write_single_coil(VERRIN_PRINCIPAL_POUSSE, OUTPUT_OFF);
    lv_led_set_brightness(objects.led_encours_verin_tire, 10);
    CANBUS_write_single_coil(VERRIN_PRINCIPAL_TIRE, OUTPUT_OFF);
    lv_led_set_brightness(objects.led_encours_verin_pousse, 10);
    CANBUS_write_single_coil(VERRIN_AMORTISSEUR, OUTPUT_OFF);
    lv_led_set_brightness(objects.led_encours_verin_amorti, 10);
    USBSerial.println("Output : ARRET");
    break;

  case POUSSE:
    CANBUS_write_single_coil(VERRIN_PRINCIPAL_TIRE, OUTPUT_OFF);
    lv_led_set_brightness(objects.led_encours_verin_tire, 10);
    CANBUS_write_single_coil(VERRIN_PRINCIPAL_POUSSE, OUTPUT_ON);
    lv_led_set_brightness(objects.led_encours_verin_pousse, 255);
    USBSerial.println("Output : POUSSE");
    break;

  case TIRE:
    CANBUS_write_single_coil(VERRIN_PRINCIPAL_POUSSE, OUTPUT_OFF);
    lv_led_set_brightness(objects.led_encours_verin_pousse, 10);
    CANBUS_write_single_coil(VERRIN_PRINCIPAL_TIRE, OUTPUT_ON);
    lv_led_set_brightness(objects.led_encours_verin_tire, 255);
    USBSerial.println("Output : TIRE");
    break;

  case STOP:
    CANBUS_write_single_coil(VERRIN_PRINCIPAL_TIRE, OUTPUT_OFF);
    lv_led_set_brightness(objects.led_encours_verin_tire, 10);
    CANBUS_write_single_coil(VERRIN_PRINCIPAL_POUSSE, OUTPUT_OFF);
    lv_led_set_brightness(objects.led_encours_verin_pousse, 10);
    USBSerial.println("Output : STOP");
    break;

  case FREINE:
    CANBUS_write_single_coil(VERRIN_AMORTISSEUR, OUTPUT_ON);
    lv_led_set_brightness(objects.led_encours_verin_amorti, 255);
    USBSerial.println("Output : FREINE");
    break;

  case RELACHE:
    CANBUS_write_single_coil(VERRIN_AMORTISSEUR, OUTPUT_OFF);
    lv_led_set_brightness(objects.led_encours_verin_amorti, 10);
    USBSerial.println("Output : RELACHE");
    break;
  }
}

/**
 * Actions liées à l'IHM (partie maintenance)
 */
void action_d_marrage(lv_event_t *e) {
  USBSerial.println("Page démarrage");
  loadScreen(SCREEN_ID_D_MARRAGE);
}

void action_maintenance(lv_event_t *e) {
  USBSerial.println("Mode maintenance");
  loadScreen(SCREEN_ID_MAINTENANCE);
}


void action_pousser(lv_event_t *e) { process_output(POUSSE); }
void action_pousser_arreter(lv_event_t *e) { process_output(ARRET); }
void action_tirer(lv_event_t *e) { process_output(TIRE); }
void action_tirer_arreter(lv_event_t *e) { process_output(ARRET); }
void action_activer_amortisseur(lv_event_t *e) { process_output(FREINE); }
void action_arreter_amortisseur(lv_event_t *e) { process_output(ARRET); }

void action_start_1_cycle(lv_event_t *e) {
  state_machine_start = true;
  configurations.nb_cycles = 1;
}

void action_start_3_cycles(lv_event_t *e) {
  state_machine_start = true;
  configurations.nb_cycles = 3;
}

void application_service_test(void) {
  static uint8_t state = 0;
  static uint8_t cmpt = 1;

  if (--cmpt == 0) {
    switch (state) {
    case 0:
      cmpt = 10;
      state = 1;
      USBSerial.println("State n°0");
      break;

    case 1:
      process_output(TIRE);
      cmpt = 40; // 40 = 2 secondes x 50 ms
      state = 2;
      USBSerial.println("State n°1");
      break;

    case 2:
      process_output(FREINE);
      cmpt = 40; // 40 = 2 secondes x 50 ms
      state = 3;
      USBSerial.println("State n°2");
      break;

    case 3:
      process_output(STOP);
      process_output(RELACHE);
      cmpt = 40; // 40 = 2 secondes x 50 ms
      state = 0;
      USBSerial.println("State n°3");
      break;

    default:
      USBSerial.println("State default");
      break;
    }
  }
}

/**
 * @brief
 *
 */
typedef enum {
  INITIALISATION,
  ATTENTE,
  ALLER,
  RETOUR_LIBRE,
  RETOUR_AMORTI,
  FIN_ESSAI,
  DEFAUT_TIMEOUT
} state_t;

/**
 * @brief
 *
 */
void application_service(void) {
  static state_t state = INITIALISATION;
  static int16_t timeout = APPLICATION_PERIOD;
  static uint16_t nb_cycles = 0;

  timeout = (timeout > APPLICATION_PERIOD) ? timeout - APPLICATION_PERIOD : 0;

  CANBUS_read_discrete_input(0x0000, 2);
  canbus_flag = false;
  while (!canbus_flag) {
    CANBUS_handle_rx_message();
  }

  switch (state) {
  case INITIALISATION:
    state = ATTENTE;
    process_output(ARRET);
    timeout = 1000; // totalement arbitraire (en ms)
    USBSerial.println("State : ATTENTE");
    break;

  case ATTENTE:
    if (timeout <= 0) {
      if (state_machine_start == true) {
        state_machine_start = false;
        USBSerial.println("State : ALLER");
        process_output(POUSSE);
        timeout = configurations.timeout_aller;
      }
    }
    break;

  case ALLER:
    if (capteur_butee_basse) {
      state = RETOUR_LIBRE;
      USBSerial.println("State : RETOUR_LIBRE");
      process_output(TIRE);
      timeout = configurations.timeout_retour_libre;
      break;
    }

    if (state_machine_stop == true) {
      state = ATTENTE;
      USBSerial.println("State : ATTENTE");
      process_output(ARRET);
      break;
    }

    if (timeout <= 0) {
      state = DEFAUT_TIMEOUT;
      USBSerial.println("State : DEFAUT_TIMEOUT");
      process_output(ARRET);
      break;
    }
    break;

  case RETOUR_LIBRE:
    if (timeout <= 0) {
      state = RETOUR_AMORTI;
      USBSerial.println("State : RETOUR_AMORTI");
      process_output(FREINE);
    }
    if (state_machine_stop == true) {
      state = ATTENTE;
      USBSerial.println("State : ATTENTE");
      process_output(ARRET);
      break;
    }
    break;

  case RETOUR_AMORTI:
    if (capteur_butee_haute) {
      if (--nb_cycles > 0) {
        state = ALLER;
        USBSerial.println("State : ALLER");
        timeout = configurations.timeout_aller;
        process_output(POUSSE);
      } else {
        state = FIN_ESSAI;
        process_output(ARRET);
        USBSerial.println("State : ARRET");
      }
      break;
    }

    if (state_machine_stop == true) {
      state = ATTENTE;
      USBSerial.println("State : ATTENTE");
      process_output(ARRET);
      break;
    }

    if (timeout <= 0) {
      state = DEFAUT_TIMEOUT;
      USBSerial.println("State : DEFAUT_TIMEOUT");
      process_output(ARRET);
      break;
    }
    break;

  case FIN_ESSAI:
    state = ATTENTE;
    USBSerial.println("State : ATTENTE");
    break;

  case DEFAUT_TIMEOUT:
  default:
    while (FOREVER) {
      USBSerial.println("Erreur système");
      delay(1000);
    }
    break;
  }
}


// end of file
