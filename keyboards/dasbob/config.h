// Copyright 2024 Wendy Chen (@Wendy Chen)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define DYNAMIC_KEYMAP_LAYER_COUNT 6

#define DIRECT_PINS                                                                                   \
    {                                                                                                 \
        {GP13, GP28, GP12, GP29, GP0}, {GP22, GP14, GP26, GP4, GP27}, {GP21, GP23, GP7, GP20, GP6}, { \
            GP16, GP9, GP8, NO_PIN, NO_PIN                                                            \
        }                                                                                             \
    }

#define DIRECT_PINS_RIGHT                                                                             \
    {                                                                                                 \
        {GP0, GP29, GP12, GP28, GP13}, {GP27, GP4, GP26, GP14, GP22}, {GP6, GP20, GP7, GP23, GP21}, { \
            GP8, GP9, GP16, NO_PIN, NO_PIN                                                            \
        }                                                                                             \
    }

/* Serial Config */
#define USE_SERIAL
#define SERIAL_USART_TX_PIN GP1
#define MASTER_LEFT

#define USB_VBUS_PIN 19
#define AUDIO_PWM_DRIVER PWMD2
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_STATE_TIMER GPTD4
#define AUDIO_PIN GP5
#ifdef AUDIO_ENABLE
#    define AUDIO_INIT_DELAY
#    define AUDIO_CLICKY
#    define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f
#    define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

#define STARTUP_SOUND E__NOTE(_E6), E__NOTE(_A6), ED_NOTE(_E7),

#define OLED_TIMEOUT 0
#define OLED_SCROLL_TIMEOUT 150000
