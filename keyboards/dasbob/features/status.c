// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "status.h"

operating_system active_operating_system = MAC;

bool is_operating_system_mac(void) {
    return active_operating_system == MAC;
}

void toggle_operating_system(void) {
    active_operating_system = is_operating_system_mac() ? LINUX : MAC;
}
