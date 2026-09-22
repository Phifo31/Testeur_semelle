// vars.cpp
// Implémentation des variables globales déclarées dans vars.h
// EEZ Studio déclare ces fonctions mais ne les implémente pas
// en mode non-Flow → on les écrit ici manuellement.

#include <stdio.h>
#include <string.h>

#include "vars.h"
#include "screens.h"

// ============================================================
// Stockage interne
// ============================================================

static int32_t var_nb_cycles_total = 25;
static int32_t var_num_cycle_actuel = 0;
static char var_str_nb_cycles_total[24] = "32";
// static bool var_test_termine = false;
// static char var_note[64] = "";
// static char var_commentaire[128] = "";

static bool var_led_capteur_haut = false;
static bool var_led_capteur_bas = false;

// ============================================================
// test_termine
// ============================================================

// bool get_var_test_termine() { return var_test_termine; }
// void set_var_test_termine(bool value) { var_test_termine = value; }

// ============================================================
// note
// ============================================================

// const char *get_var_note() { return var_note; }
// void set_var_note(const char *value) {
//   strncpy(var_note, value, sizeof(var_note) - 1);
//   var_note[sizeof(var_note) - 1] = '\0';
// }

// ============================================================
// commentaire
// ============================================================

// const char *get_var_commentaire() { return var_commentaire; }

// void set_var_commentaire(const char *value) {
//   strncpy(var_commentaire, value, sizeof(var_commentaire) - 1);
//   var_commentaire[sizeof(var_commentaire) - 1] = '\0';
// }

bool get_var_led_capteur_haut(void) { return var_led_capteur_haut; }
bool get_var_led_capteur_bas(void) { return var_led_capteur_bas; }

void set_var_led_capteur_haut(bool value) {
  var_led_capteur_haut = value;
  if (value) {
    lv_led_set_brightness(objects.maintenance_led_capteur_haut, 255);
    lv_led_set_brightness(objects.led_encours_capteur_haut, 255);
  } else {
    lv_led_set_brightness(objects.maintenance_led_capteur_haut, 10);
    lv_led_set_brightness(objects.led_encours_capteur_haut, 10);
  }
}

void set_var_led_capteur_bas(bool value) {
  var_led_capteur_bas = value;
  if (value) {
    lv_led_set_brightness(objects.maintenance_led_capteur_bas, 255);
    lv_led_set_brightness(objects.led_encours_capteur_bas, 255);
  } else {
    lv_led_set_brightness(objects.maintenance_led_capteur_bas, 10);
    lv_led_set_brightness(objects.led_encours_capteur_bas, 10);
  }
}

int32_t get_var_nb_cycles_total(void) { return var_nb_cycles_total; }
void set_var_nb_cycles_total(int32_t value) {
  var_nb_cycles_total = value;
  lv_label_set_text_fmt(objects.nb_cycles_total, "%d", var_nb_cycles_total);
  sprintf (var_str_nb_cycles_total, "%d", var_nb_cycles_total); 
}
int32_t get_var_num_cycle_actuel(void) { return var_num_cycle_actuel; }
void set_var_num_cycle_actuel(int32_t value) {
  var_num_cycle_actuel = value;
  lv_label_set_text_fmt(objects.num_cycle_actuel, "%d", var_num_cycle_actuel);

}

const char *get_var_str_nb_cycles_total() { return var_str_nb_cycles_total; }

void set_var_str_nb_cycles_total(const char *value) {
  strcpy(var_str_nb_cycles_total, value);
}

// int32_t get_var_cycles_cible() { return var_cycles_cible; }
// void set_var_cycles_cible(int32_t value) { var_cycles_cible = value; }

// int32_t get_var_cycles_actuels() { return var_cycles_actuels; }
// void set_var_cycles_actuels(int32_t value) { var_cycles_actuels = value; }
