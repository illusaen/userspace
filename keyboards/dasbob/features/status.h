// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

typedef enum {
    LINUX = 0,
    MAC,
} operating_system;

enum layers { DEF, COL, NAV, SYM, NUM };

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = QK_KB_0,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN, // Switch to next window         (cmd-tab)
    CAPS_WD,
    NUM_WD,

    OS_MAC,

    CUT,
    COPY,
    PASTE,
    UNDO,
    REDO,
    SAVE,
    RUN,
    SELWORD,
    SELBWD,
    X_WORD,
    LWORD,
    RWORD,

    ARROWFT,
    ARROWTN,
    DBLCOLN,
    COMMENT,
};

bool is_operating_system_mac(void);
void toggle_operating_system(void);
