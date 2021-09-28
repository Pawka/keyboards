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

enum layers {
    _QWERTY = 0,
    _NAV,
    _SYM,
    _NUM,
    _FUNCTION,
    _MOUSE,
    _LOCALE,
    _MEDIA,
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)

#define NAV      MO(_NAV)
#define LOCALE   MO(_LOCALE)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

// Layers
#define LT_ENT   LT(_SYM, KC_ENT)
#define LT_BSPC  LT(_NUM, KC_BSPC)
#define LT_DEL   LT(_FUNCTION, KC_DEL)
#define LT_TAB   LT(_MOUSE, KC_TAB)

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

#define REDO LCTL(LSFT(KC_Z))

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
     KC_TAB , KC_Q  , KC_W  , KC_E   , KC_R   , KC_T  ,                                         KC_Y,   KC_U ,  KC_I ,   KC_O ,  KC_P ,    KC_BSLASH,
     CTL_ESC, HOME_A, HOME_S, HOME_D , HOME_F , KC_G  ,                                         KC_H,   HOME_J, HOME_K,  HOME_L, HOME_SCLN,CTL_QUOT,
     KC_LSFT, KC_Z  , KC_X  , KC_C   , KC_V   , KC_B  , KC_LBRC, _______,     _______, KC_RBRC, KC_N,   KC_M ,  KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
                              KC_MUTE, _______, NAV   , KC_SPC,  LT_TAB,      LT_ENT,  LT_BSPC, LT_DEL, LOCALE, _______),

    [_NAV] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     REDO,    KC_PASTE,KC_COPY, KC_CUT,  KC_UNDO, _______,
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS,  _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SYM] = LAYOUT(
     _______ , KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                       _______,   _______,   _______,   _______,   _______, _______,
     _______ , KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRAVE,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
     _______ , KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_NUM] = LAYOUT(
     _______, KC_ASTR , KC_7 , KC_8 , KC_9 , KC_UNDS ,                                          _______,   _______,   _______,   _______,   _______, _______,
     _______, KC_PLUS , KC_4,  KC_5 , KC_6 , KC_EQL  ,                                      _______, _______, _______, _______, _______, _______,
     _______, KC_SLSH , KC_1,  KC_2 , KC_3 , KC_AMPR , _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
                                 _______, _______, KC_DOT, KC_0, KC_MINS, _______, _______, _______, _______, _______
    ),

    [_FUNCTION] = LAYOUT(
      _______,  KC_F12,  KC_F7 ,  KC_F8,   KC_F9 , _______,                                     _______, _______, _______, _______, _______, _______,
      _______,  KC_F11,  KC_F4 ,  KC_F5 ,  KC_F6 , _______,                                     _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
      _______,  KC_F10,  KC_F1 ,  KC_F2 ,  KC_F3 , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     REDO, KC_PASTE, KC_MS_U, KC_CUT, KC_UNDO, _______,
      _______, _______, _______, _______, _______, _______,                                     _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______, _______,
                                 _______, _______, _______, _______, _______, KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, _______, _______
    ),

    [_LOCALE] = LAYOUT(
      _______, RALT_T(KC_1), RALT_T(KC_2), RALT_T(KC_3), RALT_T(KC_4), RALT_T(KC_5),  RALT_T(KC_6), RALT_T(KC_7), RALT_T(KC_8), RALT_T(KC_9), RALT_T(KC_0), RALT_T(KC_EQL),
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
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
    return true;
}
#endif
