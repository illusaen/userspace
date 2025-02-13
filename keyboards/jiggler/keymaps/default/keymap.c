// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "print.h"
enum custom_keycodes { MOUSEJIGGLERMACRO };

bool mouse_jiggle_mode = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐
     * │ A │
     * └───┘
     */
    [0] = LAYOUT_ortho_1x1(MOUSEJIGGLERMACRO)};

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
    debug_mouse    = true;
}

uint16_t idle_timer = 0;
int      random_idle(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
void matrix_scan_user(void) {
    int      random_idle_timer = random_idle(1000, 3000);
    uint16_t elapsed_time      = timer_elapsed(idle_timer);
    if (mouse_jiggle_mode && elapsed_time > random_idle_timer) {
        tap_code(KC_MS_UP);
        tap_code(KC_MS_DOWN);
        tap_code(KC_MS_LEFT);
        tap_code(KC_MS_RIGHT);
        tap_code(KC_MS_WH_UP);
        tap_code(KC_MS_WH_DOWN);
        idle_timer = timer_read();
        dprintf("scanning %i %d %d!\n", random_idle_timer, elapsed_time, idle_timer);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MOUSEJIGGLERMACRO:
            if (record->event.pressed) {
                if (mouse_jiggle_mode) {
                    mouse_jiggle_mode = false;
                    dprint("mouse off\n");
                } else {
                    mouse_jiggle_mode = true;
                    dprint("mouse on\n");
                }
                // SEND_STRING(SS_DELAY(100)); //uncomment if it switches too fast before the button debounces
            } else {
            }
            break;
    }
    return true;
}
