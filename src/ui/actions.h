#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_historique_(lv_event_t * e);
extern void action_switch_to_nouveau_test(lv_event_t * e);
extern void action_d_marrage(lv_event_t * e);
extern void action_pousser(lv_event_t * e);
extern void action_switch_to_main(lv_event_t * e);
extern void action_switch_to_maintenance(lv_event_t * e);
extern void action_pousser_arreter(lv_event_t * e);
extern void action_tirer(lv_event_t * e);
extern void action_tirer_arreter(lv_event_t * e);
extern void action_start_1_cycle(lv_event_t * e);
extern void action_start_3_cycles(lv_event_t * e);
extern void action_activer_amortisseur(lv_event_t * e);
extern void action_arreter_amortisseur(lv_event_t * e);
extern void action_switch_to_encours(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/