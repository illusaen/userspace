// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "swapper.h"
#include "status.h"

bool sw_win_active = false;

void update_swapper(bool *active, uint16_t cmdish, uint16_t tabish, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active) {
        unregister_code(cmdish);
        *active = false;
    }
}

void process_swapper(uint16_t keycode, keyrecord_t *record) {
    uint16_t cmdish = is_operating_system_mac() ? KC_LGUI : KC_LALT;
    update_swapper(&sw_win_active, cmdish, KC_TAB, SW_WIN, keycode, record);
}
