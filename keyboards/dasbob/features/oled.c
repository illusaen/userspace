// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "status.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return !is_keyboard_master() ? OLED_ROTATION_0 : OLED_ROTATION_270;
}

static void oled_write_os_logo(void) {
    static const char PROGMEM linux_logo[] = {153, 154, 10, 185, 186, 0};
    if (is_operating_system_mac()) {
        oled_write("MAC\n     ", false);
    } else {
        oled_write_P(linux_logo, false);
    }
}

static void oled_write_layer(void) {
    oled_write_P(PSTR("\n\n\nlayer"), false);
    switch (get_highest_layer(layer_state)) {
        case DEF:
            oled_write_ln_P(PSTR("DEF"), false);
            break;
        case COL:
            oled_write_ln_P(PSTR("COL"), false);
            break;
        case SYM:
            oled_write_ln_P(PSTR("SYM"), false);
            break;
        case NAV:
            oled_write_ln_P(PSTR("NAV"), false);
            break;
        case NUM:
            oled_write_ln_P(PSTR("NUM"), false);
            break;
        default:
            oled_write_ln_P(PSTR("??"), false);
            break;
    }
    oled_write_ln_P(PSTR(""), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_layer();

        led_t led_usb_state = host_keyboard_led_state();
        if (led_usb_state.num_lock || led_usb_state.caps_lock) {
            oled_write_P(led_usb_state.num_lock ? PSTR("NUM") : PSTR(""), false);
            oled_write_P(led_usb_state.caps_lock ? PSTR("CAP") : PSTR(""), false);
            oled_write_ln_P(PSTR(""), false);
        }

        oled_write_ln_P(PSTR("WPM"), false);
        oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);
        oled_write_ln_P(PSTR(""), false);

        oled_write_os_logo();
    } else {
        static const char PROGMEM dasbob_logo[] = {
            0,   0, 0,   0,   0,   128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 0,   0,   0,   0,   0,   128, 128, 128, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 128, 128, 0, 0, 0,  0,   0,   0,   0,   128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 0,   0,   0,   0,   0,   128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 0,   0,   0,   128, 128, 128, 128, 128, 192, 192, 192, 192, 192, 0,   0,   0,   128, 128, 128, 128, 128, 128, 128, 128, 128, 0, 0,  0,  0,   128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 0,   0,  0, 0, 126, 127, 255, 255, 255, 255, 255, 255, 255, 199, 247, 255, 255, 255, 255, 255, 255, 255, 255, 127, 252, 255, 255, 255, 255, 255, 255, 255, 255, 255, 15,  127, 255, 255, 255, 255, 255, 255, 255, 255, 254,
            248, 0, 126, 127, 255, 255, 255, 255, 255, 255, 255, 199, 247, 255, 255, 255, 255, 255, 255, 255, 255, 127, 126, 255, 255, 255, 255, 255, 255, 255, 255, 239, 239, 239, 239, 207, 223, 223, 223, 159, 63,  0, 7, 63, 255, 255, 255, 255, 255, 255, 255, 254, 14,  254, 255, 255, 255, 255, 255, 255, 255, 63,  241, 252, 254, 255, 255, 255, 255, 255, 255, 255, 31,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 128, 0,   0,   0,   126, 255, 255, 255, 255, 255, 255, 255, 255, 227, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 15, 63, 127, 255, 255, 255, 255, 255, 255, 255, 248, 255, 255, 255, 255, 255, 255, 255, 255, 127, 63, 7, 0, 126, 255, 255, 255, 255, 255, 255, 255, 255, 227, 255, 255, 255, 255, 255, 255, 255, 255, 255, 128, 252, 253, 249, 249, 251, 251, 251, 251, 251, 255, 255, 255, 255, 255, 255, 255, 255, 127, 30,  0,   0,
            0,   3, 31,  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 7,   0,   63,  255, 255, 255, 255, 255, 255, 255, 255, 255, 248, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0,  0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0, 0,  0,  1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,  0, 0, 0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   0,
        };
        oled_write_raw_P(dasbob_logo, sizeof(dasbob_logo));
    }
    return false;
}
#endif
