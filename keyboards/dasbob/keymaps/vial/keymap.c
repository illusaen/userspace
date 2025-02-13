// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "features/oneshot.h"
#include "features/swapper.h"
#include "features/select_word.h"
#include "features/casemodes.h"
#include "features/num_word.h"
#include "features/status.h"

#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)
#define LA_NUM MO(NUM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x5_3(KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_QUOT, KC_LSFT, KC_SPC, LA_NAV, LA_SYM, KC_SPC, KC_BSPC),

    [COL] = LAYOUT_split_3x5_3(KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_QUOT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SCLN, KC_LSFT, KC_SPC, LA_NAV, LA_SYM, KC_SPC, KC_BSPC),

    [NAV] = LAYOUT_split_3x5_3(KC_ESC, X_WORD, SELWORD, NUM_WD, KC_TAB, S(KC_TAB), KC_HOME, KC_UP, KC_END, KC_DEL, CAPS_WD, OS_SHFT, OS_CTRL, OS_CMD, XXXXXXX, SW_WIN, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT, SAVE, CUT, COPY, PASTE, UNDO, REDO, LWORD, SELBWD, RWORD, COMMENT, _______, _______, _______, _______, _______, _______),

    [SYM] = LAYOUT_split_3x5_3(KC_TILD, KC_LBRC, KC_LCBR, KC_LPRN, KC_EXLM, KC_AMPR, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV, KC_MINS, KC_PIPE, KC_SLSH, KC_EQL, KC_DLR, KC_HASH, OS_CMD, OS_CTRL, OS_SHFT, KC_COLN, KC_BSLS, ARROWTN, ARROWFT, KC_UNDS, KC_QUES, XXXXXXX, XXXXXXX, KC_LT, KC_GT, DBLCOLN, _______, _______, _______, _______, _______, _______),

    [NUM] = LAYOUT_split_3x5_3(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, OS_ALT, OS_SHFT, OS_CTRL, OS_CMD, RUN, KC_DOT, KC_PLUS, KC_MINS, KC_PAST, KC_SLSH, KC_MUTE, KC_VOLD, KC_VOLU, KC_EQL, XXXXXXX, XXXXXXX, CG_TOGG, OS_MAC, XXXXXXX, KC_BSPC, _______, _______, _______, _______, _______, _______),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_NAV:
        case LA_NUM:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD:
            return true;
        default:
            return false;
    }
}

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
        case CAPS_WD:
            // If mod chording disable the mods
            if (record->event.pressed && (get_mods() != 0)) {
                return true;
            }
            break;
        default:
            if (record->event.pressed) {
                return true;
            }
            break;
    }
    return false;
}

bool process_ctrl_shortcuts(uint16_t keycode, keyrecord_t *record) {
    uint16_t is_mac = is_operating_system_mac();
    switch (keycode) {
        case CUT:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LGUI("x") : SS_LCTL("x"));
            }
            return false;
        case COPY:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LGUI("c") : SS_LCTL("c"));
            }
            return false;
        case PASTE:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LGUI("v") : SS_LCTL("v"));
            }
            return false;
        case UNDO:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LGUI("z") : SS_LCTL("z"));
            }
            return false;
        case REDO:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LGUI(SS_LSFT("z")) : SS_LCTL(SS_LSFT("z")));
            }
            return false;
        case SAVE:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LGUI("s") : SS_LCTL("s"));
            }
            return false;
        case RUN:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LGUI(" ") : SS_LCTL(" "));
            }
            return false;
        case COMMENT:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LGUI("/") : SS_LCTL("/"));
            }
            return false;
        case LWORD:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LALT(SS_TAP(X_LEFT)) : SS_LCTL(SS_TAP(X_LEFT)));
            }
            return false;
        case RWORD:
            if (record->event.pressed) {
                SEND_STRING(is_mac ? SS_LALT(SS_TAP(X_RIGHT)) : SS_LCTL(SS_TAP(X_RIGHT)));
            }
            return false;
    }
    return true;
}

bool process_expand_text_shortcuts(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROWFT:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            return false;
        case ARROWTN:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            return false;
        case DBLCOLN:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            return false;
    }
    return true;
}

bool process_set_operating_system(uint16_t keycode, keyrecord_t *record) {
    if (keycode == OS_MAC && record->event.pressed) {
        toggle_operating_system();
        return false;
    }

    return true;
}

bool process_enable_case_modes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CAPS_WD:
            if (record->event.pressed) {
                enable_caps_word();
                enable_xcase_with(KC_UNDS);
            }
            return false;
        case X_WORD:
            if (record->event.pressed) {
                const uint8_t mods = get_mods();
                if ((mods & MOD_MASK_SHIFT) != 0) {
                    enable_xcase_with(OSM(MOD_RSFT));
                } else if ((mods & MOD_MASK_CTRL) != 0) {
                    enable_xcase_with(KC_MINS);
                } else if ((mods & MOD_MASK_GUI) != 0) {
                    enable_xcase_with(KC_SLSH);
                } else {
                    enable_xcase_with(KC_UNDS);
                }
            }
            return false;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Activate/Deactivate oneshot keys and swap window hotkey - swapper.c, oneshot.c
    // https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum
    process_oneshots(keycode, record);
    process_swapper(keycode, record);

    // Select word or line - select_word.c
    // https://github.com/getreuer/qmk-keymap/blob/main/features
    if (!process_select_word(keycode, record, SELWORD)) {
        return false;
    }

    // Case modes, replacing space with various deliminators for paths/snake case/pascal case/etc - casemodes.c
    // https://github.com/andrewjrae/kyria-keymap
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    if (!process_enable_case_modes(keycode, record)) {
        return false;
    }

    // Num word - num_word.c, num_word.h
    // https://github.com/qmk/qmk_firmware/tree/906108fb486797ab2f3eb7c3a6f70e099c1199e6/users/replicaJunction
    if (!process_record_num_word(keycode, record)) {
        return false;
    }

    // Custom
    if (!process_set_operating_system(keycode, record)) {
        return false;
    }
    if (!process_ctrl_shortcuts(keycode, record)) {
        return false;
    }
    if (!process_expand_text_shortcuts(keycode, record)) {
        return false;
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (is_num_word_enabled()) return state;
    return update_tri_layer_state(state, SYM, NAV, NUM);
}
