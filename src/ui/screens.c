#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_d_marrage() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.d_marrage = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    lv_obj_add_event_cb(obj, action_historique_, LV_EVENT_CLICKED, (void *)0);
    {
        lv_obj_t *parent_obj = obj;
        {
            // precedent
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.precedent = obj;
            lv_obj_set_pos(obj, 54, 240);
            lv_obj_set_size(obj, 174, 73);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Test precedent");
                }
            }
        }
        {
            // nouveau
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.nouveau = obj;
            lv_obj_set_pos(obj, 54, 141);
            lv_obj_set_size(obj, 380, 73);
            lv_obj_add_event_cb(obj, action_switch_to_nouveau_test, LV_EVENT_CLICKED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Nouveau test");
                }
            }
        }
        {
            // historique
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.historique = obj;
            lv_obj_set_pos(obj, 248, 240);
            lv_obj_set_size(obj, 186, 73);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Historique des tests");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 248, 383);
            lv_obj_set_size(obj, 186, 71);
            lv_obj_add_event_cb(obj, action_switch_to_maintenance, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Maintenance");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 35, 32);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_label_set_text_static(obj, "Testeur de semelle");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 18, 454);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Page principale");
        }
    }
    
    tick_screen_d_marrage();
}

void tick_screen_d_marrage() {
}

void create_screen_en_cours() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.en_cours = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_bar_create(parent_obj);
            lv_obj_set_pos(obj, 22, 34);
            lv_obj_set_size(obj, 437, 74);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 59, 209);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Nombre de cycle total : ");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 59, 177);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Cycle actuel : ");
        }
        {
            // num_cycle_actuel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.num_cycle_actuel = obj;
            lv_obj_set_pos(obj, 158, 177);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "text");
        }
        {
            // nb_cycles_total
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.nb_cycles_total = obj;
            lv_obj_set_pos(obj, 240, 209);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "text");
        }
        {
            // led_encours_verin_pousse
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.led_encours_verin_pousse = obj;
            lv_obj_set_pos(obj, 59, 274);
            lv_obj_set_size(obj, 18, 17);
            lv_led_set_color(obj, lv_color_hex(0x0000ff));
            lv_led_set_brightness(obj, 255);
            lv_obj_set_style_height(obj, 18, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_y(obj, 275, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_x(obj, 60, LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            // led_encours_capteur_bas
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.led_encours_capteur_bas = obj;
            lv_obj_set_pos(obj, 59, 316);
            lv_obj_set_size(obj, 18, 17);
            lv_led_set_color(obj, lv_color_hex(0x0000ff));
            lv_led_set_brightness(obj, 255);
            lv_obj_set_style_height(obj, 18, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_x(obj, 60, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_y(obj, 315, LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            // led_encours_verin_tire
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.led_encours_verin_tire = obj;
            lv_obj_set_pos(obj, 59, 357);
            lv_obj_set_size(obj, 18, 17);
            lv_led_set_color(obj, lv_color_hex(0x0000ff));
            lv_led_set_brightness(obj, 255);
            lv_obj_set_style_height(obj, 18, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_x(obj, 60, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_y(obj, 345, LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 240, 303);
            lv_obj_set_size(obj, 209, 145);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Stop");
                }
            }
        }
        {
            // led_encours_capteur_haut
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.led_encours_capteur_haut = obj;
            lv_obj_set_pos(obj, 59, 399);
            lv_obj_set_size(obj, 18, 17);
            lv_led_set_color(obj, lv_color_hex(0x0000ff));
            lv_led_set_brightness(obj, 255);
            lv_obj_set_style_height(obj, 18, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_x(obj, 60, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_y(obj, 345, LV_PART_MAIN | LV_STATE_DISABLED);
        }
        {
            // led_encours_verin_amorti
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.led_encours_verin_amorti = obj;
            lv_obj_set_pos(obj, 59, 440);
            lv_obj_set_size(obj, 18, 17);
            lv_led_set_color(obj, lv_color_hex(0x0000ff));
            lv_led_set_brightness(obj, 255);
            lv_obj_set_style_height(obj, 18, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_x(obj, 60, LV_PART_MAIN | LV_STATE_DISABLED);
            lv_obj_set_style_y(obj, 345, LV_PART_MAIN | LV_STATE_DISABLED);
        }
    }
    
    tick_screen_en_cours();
}

void tick_screen_en_cours() {
}

void create_screen_nouveau_test() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.nouveau_test = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    lv_obj_add_event_cb(obj, action_d_marrage, LV_EVENT_CLICKED, (void *)0);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Retour
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.retour = obj;
            lv_obj_set_pos(obj, 302, 379);
            lv_obj_set_size(obj, 142, 52);
            lv_obj_add_event_cb(obj, action_switch_to_main, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Retour");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 49, 379);
            lv_obj_set_size(obj, 143, 52);
            lv_obj_add_event_cb(obj, action_switch_to_encours, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Lancer
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.lancer = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Lancer");
                }
            }
        }
        {
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            lv_obj_set_pos(obj, 44, 96);
            lv_obj_set_size(obj, 400, 255);
            lv_keyboard_set_mode(obj, LV_KEYBOARD_MODE_NUMBER);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 211, 46);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 49, 46);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Nombre de cycles :");
        }
    }
    
    tick_screen_nouveau_test();
}

void tick_screen_nouveau_test() {
    {
        const char *new_val = get_var_str_nb_cycles_total();
        const char *cur_val = lv_label_get_text(objects.obj0);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj0;
            lv_label_set_text(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_historique_() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.historique_ = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Retour_1
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.retour_1 = obj;
            lv_obj_set_pos(obj, 54, 356);
            lv_obj_set_size(obj, 142, 50);
            lv_obj_add_event_cb(obj, action_d_marrage, LV_EVENT_CLICKED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Retour");
                }
            }
        }
    }
    
    tick_screen_historique_();
}

void tick_screen_historique_() {
}

void create_screen_maintenance() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.maintenance = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 26, 65);
            lv_obj_set_size(obj, 214, 50);
            lv_obj_add_event_cb(obj, action_pousser, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, action_pousser_arreter, LV_EVENT_RELEASED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_event_cb(obj, action_pousser, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_add_event_cb(obj, action_pousser_arreter, LV_EVENT_PRESS_LOST, (void *)0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Pousse/Descendre");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 26, 138);
            lv_obj_set_size(obj, 214, 50);
            lv_obj_add_event_cb(obj, action_tirer, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, action_tirer_arreter, LV_EVENT_RELEASED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Tire/Remonte");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 26, 328);
            lv_obj_set_size(obj, 214, 50);
            lv_obj_add_event_cb(obj, action_start_1_cycle, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "1 x cycle");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 26, 400);
            lv_obj_set_size(obj, 214, 50);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_event_cb(obj, action_start_3_cycles, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "3 x cycles");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 313, 15);
            lv_obj_set_size(obj, 152, 50);
            lv_obj_add_event_cb(obj, action_switch_to_main, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_event_cb(obj, action_d_marrage, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Page principale");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 26, 24);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text_static(obj, "Page de maintenance");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 313, 90);
            lv_obj_set_size(obj, 152, 181);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // maintenance_led_capteur_haut
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.maintenance_led_capteur_haut = obj;
                    lv_obj_set_pos(obj, 37, 47);
                    lv_obj_set_size(obj, 32, 32);
                    lv_led_set_color(obj, lv_color_hex(0xff0000));
                    lv_led_set_brightness(obj, 255);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                }
                {
                    // maintenance_led_capteur_bas
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.maintenance_led_capteur_bas = obj;
                    lv_obj_set_pos(obj, 37, 111);
                    lv_obj_set_size(obj, 32, 32);
                    lv_led_set_color(obj, lv_color_hex(0xff0000));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 86, 55);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text_static(obj, "Haut");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 86, 119);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text_static(obj, "Bas");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 20, 8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text_static(obj, "Capteurs");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 26, 211);
            lv_obj_set_size(obj, 214, 50);
            lv_obj_add_event_cb(obj, action_activer_amortisseur, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, action_arreter_amortisseur, LV_EVENT_RELEASED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text_static(obj, "Amortisseur");
                }
            }
        }
    }
    
    tick_screen_maintenance();
}

void tick_screen_maintenance() {
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_d_marrage,
    tick_screen_en_cours,
    tick_screen_nouveau_test,
    tick_screen_historique_,
    tick_screen_maintenance,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 5) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_d_marrage();
    create_screen_en_cours();
    create_screen_nouveau_test();
    create_screen_historique_();
    create_screen_maintenance();
}