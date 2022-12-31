/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 150
#endif

// Settings for Home Row Mods: https://precondition.github.io/home-row-mods
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define RETRO_TAPPING_PER_KEY

// Set proper resolution for industrial encoder.
#define ENCODER_RESOLUTION 2
// Flip encoder direction for rev1 Kyria.
#if defined(KEYBOARD_splitkb_kyria_rev1)
#define ENCODER_DIRECTION_FLIP
#endif

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
#define COMBO_TERM 30
#define COMBO_VARIABLE_LEN 2

// Number of taps to toggle layer with TT().
#define TAPPING_TOGGLE 2

#define LEADER_TIMEOUT 400
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define UNICODE_SELECTED_MODES UNICODE_MODE_LINUX
