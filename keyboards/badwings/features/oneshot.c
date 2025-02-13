// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "oneshot.h"
#include "status.h"

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_cmd_state  = os_up_unqueued;

void update_oneshot(oneshot_state *state, uint16_t mod, uint16_t trigger, uint16_t keycode, keyrecord_t *record) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                *state = os_down_unused;
                register_code(mod);
            } else if (*state == os_up_queued) {
                *state = os_up_unqueued;
                unregister_code(mod);
            } else {
                *state = os_down_unused;
            }
        } else {
            // Trigger keyup
            switch (*state) {
                case os_down_unused:
                    // If we didn't use the mod while trigger was held, queue it.
                    *state = os_up_queued;
                    break;
                case os_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                    case os_down_unused:
                        *state = os_down_used;
                        break;
                    case os_up_queued:
                        *state = os_up_unqueued;
                        unregister_code(mod);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void process_oneshots(uint16_t keycode, keyrecord_t *record) {
    uint16_t is_mac = is_operating_system_mac();
    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, (is_mac ? KC_LCMD : KC_LCTL), OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, (is_mac ? KC_LCTL : KC_LCMD), OS_CMD, keycode, record);
}
