
#include "Arduino.h"

#include "driver/twai.h"
#include "main.h"

#define CANBUS_LOG 0

#define WRITE_SINGLE_COIL_FUNCTION 0x05
#define READ_DISCRETE_INPUT_FUNCTION 0x02


static bool TWAI_driver_installed = false;
static bool TWAI_acknoledged = true;
static uint8_t TWAI_last_request;

static word_byte_t transaction_id = {.uval = 0x01DA};


/**
 * @brief Traitement du message CAN en réception
 *
 * @param message
 */
void CANBUS_handle_rx_message(void)
{
    twai_message_t rx_message;
    while (twai_receive(&rx_message, 0) == ESP_OK)
    {
        word_byte_t id;
        id.b.hi = rx_message.data[0];
        id.b.lo = rx_message.data[1];
#if CANBUS_LOG == 1
        USBSerial.print("Transmission receive : ");
        USBSerial.print(id.uval);
        USBSerial.print(rx_message.data[2]);
        USBSerial.print(" wait : ");
        USBSerial.print(transaction_id.uval);
        USBSerial.println(TWAI_last_request);
#endif

        if ((id.uval == transaction_id.uval) && (rx_message.data[2] == TWAI_last_request))
        {
            transaction_id.uval += 1;
            TWAI_acknoledged = true;
        }

        if (rx_message.data[2] == READ_DISCRETE_INPUT_FUNCTION)
        {
            process_input(rx_message.data[4]);
            //USBSerial.println(rx_message.data[4], HEX); // debug only
        }
    }
}

/**
 * @brief
 *
 * @param reg
 * @param val
 */
void CANBUS_read_discrete_input(uint16_t reg, uint16_t nb)
{
    word_byte_t r = {.uval = reg};
    word_byte_t v = {.uval = nb};
    twai_message_t tx_message = {.identifier = MASTER_CAN_ID, .data_length_code = 8};

    while (!TWAI_acknoledged)
    {
        CANBUS_handle_rx_message();
    }

    tx_message.data[0] = transaction_id.b.hi;
    tx_message.data[1] = transaction_id.b.lo;
    tx_message.data[2] = READ_DISCRETE_INPUT_FUNCTION;
    tx_message.data[3] = 0;
    tx_message.data[4] = r.b.hi;
    tx_message.data[5] = r.b.lo;
    tx_message.data[6] = v.b.hi;
    tx_message.data[7] = v.b.lo;

    if (twai_transmit(&tx_message, pdMS_TO_TICKS(1000)) == ESP_OK)
    {
#if CANBUS_LOG == 1
        USBSerial.println("Read discrete input frame successfully transmitted");
#endif
        TWAI_acknoledged = false;
        TWAI_last_request = READ_DISCRETE_INPUT_FUNCTION;
    }
    else
    {
        USBSerial.println("Transmission failed");
    }
}

/**
 * @brief
 *
 * @param reg
 * @param val
 */
void CANBUS_write_single_coil(uint16_t reg, uint16_t val)
{
    word_byte_t r = {.uval = reg};
    word_byte_t v = {.uval = val};
    twai_message_t tx_message = {.identifier = MASTER_CAN_ID, .data_length_code = 8};

    while (!TWAI_acknoledged)
    {
        CANBUS_handle_rx_message();
    }

    tx_message.data[0] = transaction_id.b.hi;
    tx_message.data[1] = transaction_id.b.lo;
    tx_message.data[2] = WRITE_SINGLE_COIL_FUNCTION;
    tx_message.data[3] = 0;
    tx_message.data[4] = r.b.hi;
    tx_message.data[5] = r.b.lo;
    tx_message.data[6] = v.b.hi;
    tx_message.data[7] = v.b.lo;

    if (twai_transmit(&tx_message, pdMS_TO_TICKS(1000)) == ESP_OK)
    {
#if CANBUS_LOG == 1
        USBSerial.println("Write single coil frame successfully transmitted");
#endif
        TWAI_acknoledged = false;
        TWAI_last_request = WRITE_SINGLE_COIL_FUNCTION;
    }
    else
    {
        USBSerial.println("Transmission failed");
    }
}
// else
//{
//     USBSerial.println("Not acknoledged");
// }
// }

/**
 * @brief
 *
 */
void CANBUS_setup(void)
{
    USBSerial.println("Initialisation du bus CAN...");
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)CAN_TX_PIN, (gpio_num_t)CAN_RX_PIN, TWAI_MODE_NORMAL);
    //  twai_timing_config_t  t_config = TWAI_TIMING_CONFIG_1MBITS();
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    if (twai_driver_install(&g_config, &t_config, &f_config) != ESP_OK)
    {
        USBSerial.println("ERREUR : installation driver TWAI");
        return;
    }
    if (twai_start() != ESP_OK)
    {
        USBSerial.println("ERREUR : démarrage driver TWAI");
        return;
    }

    // Alertes utiles pour le debug
    uint32_t alerts = TWAI_ALERT_RX_DATA |
                      TWAI_ALERT_TX_SUCCESS |
                      TWAI_ALERT_TX_FAILED |
                      TWAI_ALERT_BUS_ERROR |
                      TWAI_ALERT_ERR_PASS |
                      TWAI_ALERT_RX_QUEUE_FULL;

    if (twai_reconfigure_alerts(alerts, NULL) != ESP_OK)
    {
        USBSerial.println("ERREUR : configuration alertes TWAI");
        return;
    }

    TWAI_driver_installed = true;
    USBSerial.println("Bus CAN prêt à 500 Kbps");
}

// // On extrait le Function ID et le Motor ID depuis l'identifiant étendu
// uint8_t motor_id = message.identifier & 0xFF;
// uint32_t function_id = (message.identifier >> 8) & 0xFFFF;

// // On ne traite que le feedback servo (0x29) de notre moteur
// if (function_id != 0x29 || motor_id != CAN_ID)
// {
//     USBSerial.printf("Trame ignorée — function_id=0x%02X motor_id=%d\n",
//                      function_id, motor_id);
//     return;
// }

// // Décodage des 8 octets
// int16_t pos_int = ((int16_t)message.data[0] << 8) | message.data[1];
// int16_t spd_int = ((int16_t)message.data[2] << 8) | message.data[3];
// int16_t cur_int = ((int16_t)message.data[4] << 8) | message.data[5];
// int8_t temp = (int8_t)message.data[6];
// uint8_t error = message.data[7];

// // Conversion en unités physiques
// float pos_deg = pos_int * 0.1f;
// float spd_erpm = spd_int * 10.0f;
// float cur_A = cur_int * 0.01f;

// Serial.println("─── Feedback moteur ───────────────────");
// Serial.printf("  Position    : %.1f °\n", pos_deg);
// Serial.printf("  Vitesse     : %.0f ERPM\n", spd_erpm);
// Serial.printf("  Courant     : %.2f A\n", cur_A);
// Serial.printf("  Température : %d °C\n", temp);
// Serial.printf("  Erreur      : %d %s\n", error,
//               error == 0 ? "(OK)" : error == 1 ? "(Surchauffe moteur)"
//                                 : error == 2   ? "(Surcourant)"
//                                 : error == 3   ? "(Surtension)"
//                                 : error == 4   ? "(Sous-tension)"
//                                 : error == 5   ? "(Encodeur)"
//                                 : error == 6   ? "(Surchauffe MOSFET)"
//                                 : error == 7   ? "(Moteur bloqué)"
//                                                : "(Inconnu)");
// Serial.println("───────────────────────────────────────");
// }

int8_t CANBUS_service(void)
{
    if (!TWAI_driver_installed)
    {
        delay(1000);
        return -1;
    }

    // Lecture des alertes TWAI
    uint32_t alerts;
    twai_read_alerts(&alerts, pdMS_TO_TICKS(10));
    twai_status_info_t status;
    twai_get_status_info(&status);

    if (alerts & TWAI_ALERT_ERR_PASS)
        USBSerial.println("Alerte : contrôleur TWAI en mode passif erreur");

    if (alerts & TWAI_ALERT_BUS_ERROR)
        USBSerial.printf("Alerte : erreur bus CAN — count=%" PRIu32 "\n", status.bus_error_count);

    if (alerts & TWAI_ALERT_TX_FAILED)
        USBSerial.printf("Alerte : échec TX — failed=%" PRIu32 "\n", status.tx_failed_count);

    if (alerts & TWAI_ALERT_TX_SUCCESS)
    {
#if CANBUS_LOG == 1
        USBSerial.println("Alerte : TX succès");
#endif
    }

    if (alerts & TWAI_ALERT_RX_QUEUE_FULL)
        USBSerial.println("Alerte : queue RX pleine, trame perdue");

    // Réception des trames feedback
    if (alerts & TWAI_ALERT_RX_DATA)
    {
        CANBUS_handle_rx_message();
    }

    return 1;
}

// end of file
