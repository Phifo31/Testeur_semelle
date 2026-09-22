#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_D_MARRAGE = 1,
    SCREEN_ID_EN_COURS = 2,
    SCREEN_ID_NOUVEAU_TEST = 3,
    SCREEN_ID_HISTORIQUE_ = 4,
    SCREEN_ID_MAINTENANCE = 5,
    _SCREEN_ID_LAST = 5
};

typedef struct _objects_t {
    lv_obj_t *d_marrage;
    lv_obj_t *en_cours;
    lv_obj_t *nouveau_test;
    lv_obj_t *historique_;
    lv_obj_t *maintenance;
    lv_obj_t *precedent;
    lv_obj_t *nouveau;
    lv_obj_t *historique;
    lv_obj_t *num_cycle_actuel;
    lv_obj_t *nb_cycles_total;
    lv_obj_t *led_encours_verin_pousse;
    lv_obj_t *led_encours_capteur_bas;
    lv_obj_t *led_encours_verin_tire;
    lv_obj_t *led_encours_capteur_haut;
    lv_obj_t *led_encours_verin_amorti;
    lv_obj_t *retour;
    lv_obj_t *lancer;
    lv_obj_t *obj0;
    lv_obj_t *retour_1;
    lv_obj_t *maintenance_led_capteur_haut;
    lv_obj_t *maintenance_led_capteur_bas;
} objects_t;

extern objects_t objects;

void create_screen_d_marrage();
void tick_screen_d_marrage();

void create_screen_en_cours();
void tick_screen_en_cours();

void create_screen_nouveau_test();
void tick_screen_nouveau_test();

void create_screen_historique_();
void tick_screen_historique_();

void create_screen_maintenance();
void tick_screen_maintenance();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/