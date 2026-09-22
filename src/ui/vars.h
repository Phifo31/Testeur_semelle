#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_LED_CAPTEUR_HAUT = 0,
    FLOW_GLOBAL_VARIABLE_LED_CAPTEUR_BAS = 1,
    FLOW_GLOBAL_VARIABLE_NB_CYCLES_TOTAL = 2,
    FLOW_GLOBAL_VARIABLE_NUM_CYCLE_ACTUEL = 3,
    FLOW_GLOBAL_VARIABLE_STR_NB_CYCLES_TOTAL = 4
};

// Native global variables

extern bool get_var_led_capteur_haut();
extern void set_var_led_capteur_haut(bool value);
extern bool get_var_led_capteur_bas();
extern void set_var_led_capteur_bas(bool value);
extern int32_t get_var_nb_cycles_total();
extern void set_var_nb_cycles_total(int32_t value);
extern int32_t get_var_num_cycle_actuel();
extern void set_var_num_cycle_actuel(int32_t value);
extern const char *get_var_str_nb_cycles_total();
extern void set_var_str_nb_cycles_total(const char *value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/