// actions.cpp — fichier manuel, non ecrase par EEZ

#include "actions.h"
#include "ui.h"
//#include "vars.h"
#include "screens.h"

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <Preferences.h>

// --- A RAJOUTER ICI POUR LE COMPILATEUR ---
//void tick_force_refresh();
//void action_detail_cb(lv_event_t *e);
// ------------------------------------------

// // ============================================================
// // HISTORIQUE EN RAM
// // ============================================================

// #define MAX_HISTORIQUE 20
// #define NOM_MAX 64

// typedef struct {
//     char nom_echantillon[NOM_MAX];
//     int  cycles_cible;
//     int  cycles_actuels;
//     char temps[12];
// } TestResult;

// static TestResult historique[MAX_HISTORIQUE];
// static int        historique_count = 0;
// static int        detail_index     = -1;

// void sauvegarder_historique() {
//     //Preferences prefs;
//     //prefs.begin("historique", false); // Ouvre l'espace "historique" en mode écriture
    
//     //prefs.putInt("count", historique_count);
//     //prefs.putBytes("data", historique, sizeof(historique));
    
//     //prefs.end(); // Ferme proprement
// }

// void charger_historique() {
//     //Preferences prefs;
//     //prefs.begin("historique", true); // Ouvre en mode lecture seule
    
//     // Récupère le nombre de tests (0 par défaut si la mémoire est vide)
//     //historique_count = prefs.getInt("count", 0); 
    
//     //if (historique_count > 0) {
//     //    prefs.getBytes("data", historique, sizeof(historique));
//     //}
    
//     //prefs.end();
// }

// ============================================================
// CHRONOMETRE
// ============================================================

// static uint32_t chrono_start_ms  = 0;
// static bool     chrono_running   = false;
// static uint32_t chrono_elapsed_s = 0;

// static void chrono_start() {
//     chrono_start_ms = lv_tick_get();
//     chrono_running  = true;
// }

// static void chrono_stop() {
//     if (chrono_running) {
//         chrono_elapsed_s = (lv_tick_get() - chrono_start_ms) / 1000;
//         chrono_running   = false;
//     }
// }

// static void chrono_reset() {
//     chrono_start_ms  = 0;
//     chrono_running   = false;
//     chrono_elapsed_s = 0;
// }

// static uint32_t chrono_get_seconds() {
//     if (chrono_running)
//         return (lv_tick_get() - chrono_start_ms) / 1000;
//     return chrono_elapsed_s;
// }

// static void format_temps(uint32_t total_s, char *buf, size_t len) {
//     uint32_t h = total_s / 3600;
//     uint32_t m = (total_s % 3600) / 60;
//     uint32_t s = total_s % 60;
//     snprintf(buf, len, "%02lu:%02lu:%02lu",
//              (unsigned long)h,
//              (unsigned long)m,
//              (unsigned long)s);
// }


// Navigation entre pages

void action_switch_to_maintenance(lv_event_t *e) { loadScreen(SCREEN_ID_MAINTENANCE); }
void action_switch_to_main(lv_event_t *e) { loadScreen(SCREEN_ID_D_MARRAGE); }
void action_switch_to_encours (lv_event_t *e) { loadScreen(SCREEN_ID_EN_COURS); }
void action_switch_to_nouveau_test(lv_event_t *e) { loadScreen(SCREEN_ID_NOUVEAU_TEST); }



// void action_en_cours(lv_event_t *e) {
//     // Lire cycles depuis textarea (index 2 de param_tre)
//  // @todo phifo   lv_obj_t *ta_cycles = lv_obj_get_child(objects.param_tre, 2);
//  // @todo phifo   if (ta_cycles) {
// // @todo phifo        const char *txt = lv_textarea_get_text(ta_cycles);
// // @todo phifo        if (txt && strlen(txt) > 0) {
// // @todo phifo            int valeur = atoi(txt);
// // @todo phifo            if (valeur > 0) set_var_cycles_cible(valeur);
// // @todo phifo        }
// // @todo phifo    }

// // @todo phifo    set_var_cycles_actuels(0);
// // @todo phifo    set_var_test_termine(false);
// // @todo phifo    lv_obj_add_flag(objects.btn_resultat, LV_OBJ_FLAG_HIDDEN);
// // @todo phifo    lv_obj_clear_flag(objects.btn_stop,       LV_OBJ_FLAG_HIDDEN);
// // @todo phifo    lv_obj_clear_flag(objects.btn_incementer, LV_OBJ_FLAG_HIDDEN);

// // @todo phifo    chrono_reset();
// // @todo phifo    chrono_start();
// // @todo phifo    tick_force_refresh();

// // @todo phifo    loadScreen(SCREEN_ID_EN_COURS);
// }

// void action_r_sultat(lv_event_t *e) {
//     // Stopper le chrono
//     chrono_stop();

//     // Remplir la page resultat
//     const char *nom = "";
// // @todo phifo    if (objects.nom_ech)
// // @todo phifo        nom = lv_textarea_get_text(objects.nom_ech);
// // @todo phifo    lv_label_set_text(objects.res_nom, nom ? nom : "");

//     char buf[64];
// // @todo phifo    snprintf(buf, sizeof(buf), "Cycles : %d / %d",
// // @todo phifo             (int)get_var_cycles_actuels(),
// // @todo phifo             (int)get_var_cycles_cible());
// // @todo phifo    lv_label_set_text(objects.res_cycles, buf);

//     char tbuf[12];
//     format_temps(chrono_get_seconds(), tbuf, sizeof(tbuf));
// // @todo phifo    lv_label_set_text(objects.res_temps, tbuf);

//     // Decocher la checkbox par defaut
// // @todo phifo    lv_obj_clear_state(objects.checkbox_enregistrer, LV_STATE_CHECKED);

// // @todo phifo    loadScreen(SCREEN_ID_R_SULTAT);
// }

// // Rafraichit la liste historique — appele UNE SEULE FOIS
// static void rafraichir_liste_historique() {
// // @todo phifo    lv_obj_clean(objects.list_historique);
//     for (int i = 0; i < historique_count; i++) {
//         char ligne[80];
//         snprintf(ligne, sizeof(ligne), "%d. %s  %s  (%d cycles)",
//                  i + 1,
//                  historique[i].nom_echantillon,
//                  historique[i].temps,
//                  historique[i].cycles_actuels);
// // @todo phifo        lv_obj_t *btn = lv_list_add_btn(objects.list_historique, NULL, ligne);
// // @todo phifo        lv_obj_set_user_data(btn, (void *)(intptr_t)i);
// // @todo phifo        lv_obj_add_event_cb(btn, action_detail_cb, LV_EVENT_CLICKED, NULL);
//     }
// }

// void action_historique(lv_event_t *e) {
//     rafraichir_liste_historique();
// // @todo phifo    loadScreen(SCREEN_ID_HISTORIQUE);
// }

// // ============================================================
// // CLAVIER — mode adapté au textarea actif
// // ============================================================

// void action_action_show_keyboard(lv_event_t *e) {
// // @todo phifo    lv_obj_t *kb = lv_obj_get_child(objects.param_tre, 3);
//     lv_obj_t *ta = lv_event_get_target(e);
// // @todo phifo    if (!kb || !ta) return;

//     // Nom_ech est stocke dans objects.nom_ech directement
//     // Si le textarea actif est nom_ech → clavier texte, sinon → numerique
// // @todo phifo    if (ta == objects.nom_ech) {
// // @todo phifo        lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_TEXT_LOWER);
// // @todo phifo    } else {
// // @todo phifo        lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
// // @todo phifo    }

// // @todo phifo    lv_keyboard_set_textarea(kb, ta);
// // @todo phifo    lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
// }

// void action_action_hide_keyboard(lv_event_t *e) {
// // @todo phifo    lv_obj_t *kb = lv_obj_get_child(objects.param_tre, 3);
// // @todo phifo    if (kb) lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
// }

// // ============================================================
// // PAGE EN COURS
// // ============================================================

// void action_action_incrementer(lv_event_t *e) {
// // @todo phifo    if (get_var_test_termine()) return;

// // @todo phifo    int actuel = get_var_cycles_actuels() + 1;
// // @todo phifo    set_var_cycles_actuels(actuel);

// // @todo phifo    int cible = get_var_cycles_cible();
// // @todo phifo    if (cible > 0 && actuel >= cible) {
// // @todo phifo        set_var_test_termine(true);
//         chrono_stop();
// // @todo phifo        lv_obj_clear_flag(objects.btn_resultat,  LV_OBJ_FLAG_HIDDEN);
// // @todo phifo        lv_obj_add_flag(objects.btn_stop,         LV_OBJ_FLAG_HIDDEN);
// // @todo phifo        lv_obj_add_flag(objects.btn_incementer,   LV_OBJ_FLAG_HIDDEN);
// // @todo phifo    }
//     // Forcer la mise a jour des labels/barre
// // @todo phifo    tick_force_refresh();
// }

// void action_action_stop(lv_event_t *e) {
//     chrono_stop();
//     chrono_reset();
// // @todo phifo    set_var_cycles_actuels(0);
// // @todo phifo    set_var_cycles_cible(0);
// // @todo phifo    set_var_test_termine(false);
// // @todo phifo    lv_obj_add_flag(objects.btn_resultat, LV_OBJ_FLAG_HIDDEN);
//     tick_force_refresh();
// // @todo phifo    loadScreen(SCREEN_ID_PARAM_TRE);
// }

// // ============================================================
// // TICK — appele chaque frame via tick_screen_en_cours()
// // ============================================================

// static int32_t dernier_actuel  = -1;
// static int32_t dernier_cible   = -1;
// static uint32_t dernier_chrono = 9999; // force 1er affichage

// void tick_force_refresh() {
//     dernier_actuel  = -1;
//     dernier_cible   = -1;
//     dernier_chrono  = 9999;
// }

// void tick_en_cours_logic() {
// // @todo phifo    int32_t  cible  = get_var_cycles_cible();
// // @todo phifo    int32_t  actuel = get_var_cycles_actuels();
//     uint32_t secs   = chrono_get_seconds();

//     // --- Chrono : mis a jour chaque seconde independamment ---
//     if (secs != dernier_chrono) {
//         dernier_chrono = secs;
//         char tbuf[12];
//         format_temps(secs, tbuf, sizeof(tbuf));
// // @todo phifo        lv_label_set_text(objects.chrono_label, tbuf);
//     }

//     // --- Labels et barre : mis a jour si changement ---
// // @todo phifo    if (actuel == dernier_actuel && cible == dernier_cible) return;
// // @todo phifo    dernier_actuel = actuel;
// // @todo phifo    dernier_cible  = cible;

//     char buf[32];
// // @todo phifo    snprintf(buf, sizeof(buf), "Objectif : %d", (int)cible);
// // @todo phifo    lv_label_set_text(objects.label_cible, buf);

// // @todo phifo    snprintf(buf, sizeof(buf), "En cours : %d", (int)actuel);
// // @todo phifo    lv_label_set_text(objects.label_actuel, buf);

// // @todo phifo    if (cible > 0) {
// // @todo phifo        int pct = (int)((actuel * 100) / cible);
// // @todo phifo        if (pct > 100) pct = 100;
// // @todo phifo        snprintf(buf, sizeof(buf), "%d%%", pct);
// // @todo phifo        lv_label_set_text(objects.pourcentage, buf);
// // @todo phifo        lv_bar_set_range(objects.bar_progression, 0, (int)cible);
// // @todo phifo        lv_bar_set_value(objects.bar_progression, (int)actuel, LV_ANIM_ON);
// // @todo phifo    } else {
// // @todo phifo        lv_label_set_text(objects.pourcentage, "0%");
// // @todo phifo        lv_bar_set_range(objects.bar_progression, 0, 100);
// // @todo phifo        lv_bar_set_value(objects.bar_progression, 0, LV_ANIM_OFF);
// // @todo phifo    }
// }

// // ============================================================
// // RESULTAT — VALIDER
// // ============================================================

// void action_action_valider(lv_event_t *e) {
//     // === 1. BLOC DE SÉCURITÉ À RAJOUTER ===
//     static uint32_t dernier_enregistrement = 0;
    
//     // Si le bouton est activé deux fois en moins d'une seconde (1000 ms),
//     // on bloque immédiatement en quittant la fonction avec un "return".
//     if (lv_tick_get() - dernier_enregistrement < 1000) {
//         return; 
//     }
//     dernier_enregistrement = lv_tick_get(); // On mémorise l'heure du clic valide
//     // =======================================


//     // === 2. TON CODE ACTUEL (RESTE IDENTIQUE) ===
// // @todo phifo// @todo phifo    bool enregistrer = (lv_obj_get_state(objects.checkbox_enregistrer) & LV_STATE_CHECKED);

// // @todo phifo    if (enregistrer && historique_count < MAX_HISTORIQUE) {
//         TestResult *r = &historique[historique_count];

//         const char *nom = "";
// // @todo phifo        if (objects.nom_ech) nom = lv_textarea_get_text(objects.nom_ech);
// // @todo phifo        strncpy(r->nom_echantillon, nom ? nom : "",
// // @todo phifo                sizeof(r->nom_echantillon) - 1);
// // @todo phifo        r->nom_echantillon[sizeof(r->nom_echantillon) - 1] = '\0';

// // @todo phifo        r->cycles_cible   = get_var_cycles_cible();
// // @todo phifo        r->cycles_actuels = get_var_cycles_actuels();
// // @todo phifo        format_temps(chrono_get_seconds(), r->temps, sizeof(r->temps));

//         historique_count++;
//         sauvegarder_historique();
//     }

// // @todo phifo    loadScreen(SCREEN_ID_PRINCIPALE);
// // @todo phifo}

// // ============================================================
// // DETAIL
// // ============================================================

// void action_detail_cb(lv_event_t *e) {
//     lv_obj_t *btn = lv_event_get_target(e);
//     int idx = (int)(intptr_t)lv_obj_get_user_data(btn);
//     if (idx < 0 || idx >= historique_count) return;

//     detail_index     = idx;
//     TestResult *r    = &historique[idx];

// // @todo phifo    lv_label_set_text(objects.detail_nom, r->nom_echantillon);

//     char buf[64];
//     snprintf(buf, sizeof(buf), "Cycles : %d / %d",
//              r->cycles_actuels, r->cycles_cible);
// // @todo phifo    lv_label_set_text(objects.detail_cycles, buf);
// // @todo phifo    lv_label_set_text(objects.detail_temps,  r->temps);

// // @todo phifo    loadScreen(SCREEN_ID_DETAIL);
// }

// // ============================================================
// // ACTIONS VIDES generees par EEZ
// // ============================================================

// // void action_principale(lv_event_t *e) {
// // //    loadScreen(SCREEN_ID_MAINTENANCE);
// // }

// // void action_param_tre(lv_event_t *e) {
// // // @todo phifo    loadScreen(SCREEN_ID_PARAM_TRE);
// // }

// // void application_action_maintenance (void);
// // void action_change_object_state(lv_event_t *e) { }
// // void action_hidden(lv_event_t *e) { }
// // void action_set_var_cycles_actuels(lv_event_t *e) { }
// // void action_set_var_cycles_cible(lv_event_t *e) { }
// // void action_set_var_test_termine(lv_event_t *e) { }

 void action_historique_(lv_event_t *e) { }




