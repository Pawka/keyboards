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
#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

// Used for keylogging.
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

enum layers {
    _QWERTY = 0,
    _MACOS,
    _SYM,
    _NAV,
    _NUM,
    _FUNCTION,
    _MOUSE,
    _LOCALE,
};

// Aliases for readability
#define LOCALE   MO(_LOCALE)
#define NUM      MO(_NUM)
#define MOUSE    TT(_MOUSE)
#define MOUSE_1  KC_MS_BTN1
#define MOUSE_2  KC_MS_BTN2
#define MOUSE_3  KC_MS_BTN3
#define TO_BASE  TO(_QWERTY)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_TAB  MT(MOD_LCTL, KC_TAB)
#define GUI_TAB  MT(MOD_LGUI, KC_TAB)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

// Layers
#define LT_ENT   LT(_NUM, KC_ENT)
#define LT_BSPC  LT(_SYM, KC_BSPC)
#define LT_DEL   LT(_LOCALE, KC_DEL)
#define LT_TAB   LT(_MOUSE, KC_TAB)
#define LT_SPC   LT(_NAV, KC_SPC)

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

#define UNDO    LCTL(KC_Z)
#define REDO    LCTL(LSFT(KC_Z))
#define CUT     LCTL(KC_X)
#define COPY    LCTL(KC_C)
#define PASTE   LCTL(KC_V)
#define SEL_ALL LCTL(KC_A)

// Navigation shortcuts
#define PREV_TAB LCTL(KC_PGUP)
#define NEXT_TAB LCTL(KC_PGDN)
#define NEW_TAB LCTL(KC_T)
#define CLOSE_TAB LCTL(KC_W)

// Alt-Tab window switch variables to preserve state.
#define ALT_TAB_ENCODER_TIMER 500
#define ALT_TAB_MODIFIER KC_LGUI // For Linux it is Alt, for MacOS it is Meta.
bool is_alt_tab_active = false;
bool is_alt_shift_tab_active = false;
uint16_t alt_tab_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
     KC_ESC , KC_Q  , KC_W  , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O  , KC_P ,    KC_BSLS,
     KC_LSFT, KC_A  , HOME_S, HOME_D , HOME_F , KC_G   ,                                     KC_H   , HOME_J , HOME_K , HOME_L, KC_SCLN , CTL_QUOT,
     KC_LCTL, KC_Z  , KC_X  , KC_C   , KC_V   , KC_B   , DF(_MACOS), _______, _______, KC_LEAD, KC_N   , KC_M   , KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
                              KC_MUTE, TO(_MOUSE),KC_LGUI,LT_SPC, CTL_TAB, LT_ENT , LT_BSPC, LOCALE,  MOUSE  , _______
    ),

    [_MACOS] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, DF(_QWERTY), _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, GUI_TAB, _______, _______, _______, _______, _______
    ),

    [_SYM] = LAYOUT(
     _______ , KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PERC,                                     KC_PIPE, KC_UNDS, KC_PLUS, KC_SLSH, _______, _______,
     _______ , KC_HASH, KC_CIRC, KC_DLR,  KC_DQT,  KC_GRAVE,                                    KC_AMPR, KC_EQL , KC_MINS, KC_ASTR, KC_COLN, KC_DQT ,
     _______ , _______, _______, _______, KC_QUOT, KC_TILD, _______, _______, _______, _______, KC_QUOT, KC_DQT , KC_LT  , KC_GT  , _______, _______,
                                 KC_MPLY, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NAV] = LAYOUT(
      _______, _______, PREV_TAB,NEW_TAB, NEXT_TAB,_______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
      _______, _______, _______, CLOSE_TAB,_______,_______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
                                 _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______
    ),

    [_NUM] = LAYOUT(
      _______,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                      KC_6  ,  KC_7  ,  KC_8  ,  KC_9  , KC_0   , KC_MINS,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_F11,  KC_F12, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
      KC_F12 , KC_F1  , KC_F2  ,  KC_F3 , KC_F4  , KC_F5  ,                                     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, KC_F12 ,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
      _______, XXXXXXX, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
      _______, SEL_ALL, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                                     XXXXXXX, KC_RSFT, KC_RCTL, KC_LALT, XXXXXXX, _______,
      _______, XXXXXXX, CUT    , COPY   , PASTE  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                 _______, TO_BASE, MOUSE_3, MOUSE_2, MOUSE_1, _______, _______, _______, TO_BASE, _______
    ),

    [_LOCALE] = LAYOUT(
      _______, RALT(KC_1), RALT(KC_2), RALT(KC_3), RALT(KC_4), RALT(KC_5),    RALT(KC_6), RALT(KC_7), RALT(KC_8), RALT(KC_9), RALT(KC_0), RALT(KC_EQL),
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_SYM)) {
            // Next/Prev song.
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        } else {
            // Volume control
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    }
    else if (index == 1) {
        if (IS_LAYER_ON(_NAV)) {
            // Alt-Tab window switch on encoder.
            if (clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
					unregister_code(KC_LSFT);
					register_code(ALT_TAB_MODIFIER);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            } else {
                if (!is_alt_shift_tab_active) {
                    is_alt_shift_tab_active = true;
					register_code(ALT_TAB_MODIFIER);
					register_code(KC_LSFT);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            }
        } else {
            // Scroll up/down
            if (clockwise) {
                tap_code(KC_WH_D);
                tap_code(KC_WH_D);
            } else {
                tap_code(KC_WH_U);
                tap_code(KC_WH_U);
            }
        }
    }
    return false;
}
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Win
        case HOME_A:
        case HOME_SCLN:
            return TAPPING_TERM + 250;
        // Alt
        case HOME_S:
        case HOME_L:
            return TAPPING_TERM + 50;
        // Ctrl
        case HOME_D:
        case HOME_K:
        case CTL_TAB:
            return TAPPING_TERM - 30;
        // Shift
        case HOME_F:
        case HOME_J:
            return TAPPING_TERM - 50;
        case LT_BSPC:
        case LT_ENT:
            return TAPPING_TERM - 70;
        default:
            return TAPPING_TERM;
    }
}

// Logger for heatmap.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    if (record->event.pressed) {
        uprintf("0x%04X,%u,%u,%u,%b,0x%02X,0x%02X,%u\n",
                keycode,
                record->event.key.row,
                record->event.key.col,
                get_highest_layer(layer_state),
                record->event.pressed,
                get_mods(),
                get_oneshot_mods(),
                record->tap.count
               );

    }
#endif
    return true;
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_T) {
            // Reopen last tab.
            // TODO: make compatible with Mac.
            SEND_STRING(SS_LCTL(SS_LSFT("t")));
        }
        SEQ_TWO_KEYS(KC_E, KC_W) {
            SEND_STRING("povilas.");
            SEND_STRING("balzara");
            SEND_STRING("vicius");
            SEND_STRING("@");
            SEND_STRING("chronos");
            SEND_STRING("phere.io");
        }
        SEQ_TWO_KEYS(KC_E, KC_E) {
            SEND_STRING("povilas");
            SEND_STRING("@");
            SEND_STRING("balzara");
            SEND_STRING("vicius");
            SEND_STRING(".lt");
        }
    }
	// Alt+Tab encoder timer
	if (is_alt_tab_active) {
		if (timer_elapsed(alt_tab_timer) > ALT_TAB_ENCODER_TIMER) {
			unregister_code(ALT_TAB_MODIFIER);
			unregister_code(KC_LSFT);
			is_alt_tab_active = false;
			is_alt_shift_tab_active = false;
		}
	}
}

// Configure tri-layer. This enables the layer when other two layer keys are
// pressed.
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUM, _NAV, _FUNCTION);
}
