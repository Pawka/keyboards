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

#ifdef CONSOLE_ENABLE
// Used for keylogging.
#include "print.h"
#endif

enum layers {
    _QWERTY = 0,
    _MAC,
    _NAV,
    _MACNAV,
    _SYM,
    _NUM,
    _FUN,
    _MOUSE,
    _LOCALE,
};

// Aliases for readability
#define MOUSE    TT(_MOUSE)
#define MOUSE_1  KC_MS_BTN1
#define MOUSE_2  KC_MS_BTN2
#define MOUSE_3  KC_MS_BTN3
#define TO_BASE  TO(_QWERTY)
#define CTL_TAB  MT(MOD_LCTL, KC_TAB)
#define GUI_TAB  MT(MOD_LGUI, KC_TAB)

// Layers
#define LOCALE   MO(_LOCALE)
#define LT_BSPC  LT(_SYM, KC_BSPC)
#define LT_ENT   LT(_NUM, KC_ENT)
#define NAV      LT(_NAV, KC_SPC)
#define LT_TAB   LT(_MOUSE, KC_TAB)
#define MAC_SPC  LT(_MACNAV, KC_SPC)

// Left-hand home row mods
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)

#define CUT     LCTL(KC_X)
#define COPY    LCTL(KC_C)
#define PASTE   LCTL(KC_V)
#define SEL_ALL LCTL(KC_A)

// Navigation shortcuts
#define PREV_TAB LCTL(KC_PGUP)
#define NEXT_TAB LCTL(KC_PGDN)
#define NEW_TAB LCTL(KC_T)
#define CLS_TAB LCTL(KC_W)
#define BCK_TAB LALT(KC_LEFT)
#define FWD_TAB LALT(KC_RIGHT)
#define BCK_MAC LGUI(KC_LEFT)
#define FWD_MAC LGUI(KC_RIGHT)

#define TO_MAC DF(_MAC)
#define TO_QWERTY DF(_QWERTY)


extern layer_state_t default_layer_state;
// Check if current base layout is set to _MAC.
#define IS_MAC get_highest_layer(default_layer_state) == _MAC

// By default it is ALT+Tab. For MAC it is META+Tab. It is set as variable so
// it could be changed on OS switch.
int TS_MOD = KC_LALT;
bool is_taskswitcher_active = false;

// keyboard_post_init_user is executed at the end of QMK initialization.
void keyboard_post_init_user(void) {
#if defined(KEYBOARD_splitkb_kyria_rev2)
    // For rev2 Kyria set to Mac layer by default because it is being used with
    // Macbook all the time.
    set_single_persistent_default_layer(_MAC);
#endif
    if (IS_MAC) {
        // Set "task switcher" key to Mac on keyboard boot if the default layer
        // is set to _MAC.
        TS_MOD = KC_LGUI;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
     KC_ESC , KC_Q  , KC_W  , KC_E   , KC_R   , KC_T   ,                                    KC_Y   , KC_U   , KC_I   , KC_O  , KC_P ,    KC_BSLS,
     KC_LSFT, KC_A  , HOME_S, HOME_D , HOME_F , KC_G   ,                                    KC_H   , HOME_J , HOME_K , HOME_L, KC_SCLN , KC_QUOTE,
     KC_LCTL, KC_Z  , KC_X  , KC_C   , KC_V   , KC_B   , TO_MAC, _______, _______, QK_LEAD, KC_N   , KC_M   , KC_COMM, KC_DOT, KC_SLSH,  KC_RSFT,
                              KC_MUTE, MOUSE  , KC_LGUI, NAV,    CTL_TAB, LT_ENT , LT_BSPC, LOCALE , MOUSE  , _______
    ),

    [_MAC] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,                                      _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, TO_QWERTY,_______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, MAC_SPC , GUI_TAB, _______, _______, _______, _______, _______
    ),

    [_NAV] = LAYOUT(
      _______, BCK_TAB, PREV_TAB,NEW_TAB, NEXT_TAB,FWD_TAB,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, KC_LALT, KC_LCTL, KC_LSFT, _______,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
      _______, _______, _______, CLS_TAB, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
                                 _______, _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______
    ),

    // Mac navigation layer should be used to override keys on navigation (_NAV)
    // layer. If key on navigation layer does not need to be changed on Mac - it
    // is not required to add it to the Mac navigation layer since the key will
    // be inherited from _NAV.
    [_MACNAV] = LAYOUT(
      _______, BCK_MAC, _______,LGUI(KC_T),_______,FWD_MAC,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______,  _______,_______,                                     _______, _______, _______, _______, _______, _______,
      _______, _______, _______,LGUI(KC_W),_______,_______, _______, _______, _______, _______, LGUI(KC_LEFT),_______,_______,LGUI(KC_RIGHT),_______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_SYM] = LAYOUT(
     KC_GRAVE, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PERC,                                     KC_PIPE, KC_UNDS, KC_PLUS, KC_SLSH, XXXXXXX, _______,
     _______ , KC_HASH, KC_CIRC, KC_DLR,  KC_DQT,  KC_GRAVE,                                    KC_AMPR, KC_EQL , KC_MINS, KC_ASTR, KC_COLN, KC_DQT ,
     _______ , XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT, KC_TILD, _______, _______, _______, _______, KC_QUOT, KC_DQT , KC_LT  , KC_GT  , _______, _______,
                                 KC_MPLY, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),


    [_NUM] = LAYOUT(
      _______,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                      KC_6  ,  KC_7  ,  KC_8  ,  KC_9  , KC_0   , KC_MINS,
      _______,  KC_1  ,  KC_2  ,  KC_3  ,  KC_4  ,  KC_5  ,                                      KC_6  ,  KC_7  ,  KC_8  ,  KC_9  , KC_0   , KC_MINS,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FUN] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
      KC_F12 , KC_F1  , KC_F2  ,  KC_F3 , KC_F4  , KC_F5  ,                                     KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
      _______, _______, _______, _______, _______, KC_F11 , _______, _______, _______, _______, KC_F12 , _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
      _______, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, _______,
      _______, SEL_ALL, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX,                                     XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, _______,
      _______, XXXXXXX, CUT    , COPY   , PASTE  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                 _______, TO_BASE, MOUSE_3, MOUSE_2, MOUSE_1, MOUSE_1, MOUSE_2, _______, TO_BASE, _______
    ),

    [_LOCALE] = LAYOUT(
      _______, RALT(KC_1),RALT(KC_2),RALT(KC_3),RALT(KC_4),RALT(KC_5),                          RALT(KC_6),RALT(KC_7),RALT(KC_8),RALT(KC_9),RALT(KC_0),RALT(KC_EQL),
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
        } else if (IS_LAYER_ON(_LOCALE)) {
            // Next/Prev keyboard layout.
            if (clockwise) {
                register_code(KC_LGUI);
                tap_code(KC_SPACE);
                unregister_code(KC_LGUI);
            } else {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_SPACE);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
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
            // Task switch on encoder (Alt+Tab)
            is_taskswitcher_active = true;
            register_code(TS_MOD);
            if (clockwise) {
                unregister_code(KC_LSFT);
            } else {
                register_code(KC_LSFT);
            }
            tap_code(KC_TAB);
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Common keycodes.
    switch (keycode) {
        case MAC_SPC:
            // When Mac navigation layer is activated also activate original
            // navigation layer so keys would be inherited from former.
            if (record->event.pressed) {
                layer_on(_NAV);
            } else {
                layer_off(_NAV);
            }
            break;
    }

    // Task switcher.
    switch (keycode) {
        case NAV:
        case MAC_SPC:
            if (!record->event.pressed && is_taskswitcher_active) {
                unregister_code(TS_MOD);
                unregister_code(KC_LSFT);
                is_taskswitcher_active = false;
            }
            break;
        case TO_MAC:
            TS_MOD = KC_LGUI;
            break;
        case TO_QWERTY:
            TS_MOD = KC_LALT;
            break;
    }

#ifdef CONSOLE_ENABLE
    // Logger for heatmap.
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

/* LEADER_EXTERNS(); */

void leader_end_user(void) {
    /* leader_end(); */

    // Reopen last tab.
    if (leader_sequence_one_key(KC_T)) {
        if (IS_MAC) {
            SEND_STRING(SS_LGUI(SS_LSFT("t")));
        } else {
            SEND_STRING(SS_LCTL(SS_LSFT("t")));
        }
        return;
    }
    // Lock screen.
    if (leader_sequence_one_key(KC_L)) {
        if (IS_MAC) {
            SEND_STRING(SS_LGUI(SS_LCTL("q")));
        } else {
            SEND_STRING(SS_LGUI("l"));
        }
        return;
    }
    // Print debug information.
    if (leader_sequence_two_keys(KC_D, KC_D)) {
        if (IS_MAC) {
            SEND_STRING("Default layer: _MAC");
        } else {
            SEND_STRING("Default layer: _QWERTY");
        }
        return;
    }
    if (leader_sequence_two_keys(KC_E, KC_W)) {
        SEND_STRING("povilas.");
        SEND_STRING("balzara");
        SEND_STRING("vicius");
        SEND_STRING("@");
        SEND_STRING("chronos");
        SEND_STRING("phere.io");
        return;
    }
    if (leader_sequence_two_keys(KC_E, KC_E)) {
        SEND_STRING("povilas");
        SEND_STRING("@");
        SEND_STRING("balzara");
        SEND_STRING("vicius");
        SEND_STRING(".lt");
        return;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Configure tri-layer. This enables the layer when other two layer keys are
    // pressed.
    return update_tri_layer_state(state, _SYM, _NAV, _FUN);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
#if defined(KEYBOARD_splitkb_kyria_rev1)
    // Kyria Rev1. Kailh Jade switches.
    switch (keycode) {
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
            return TAPPING_TERM - 70;
        case LT_BSPC:
        case LT_ENT:
            return TAPPING_TERM - 70;
        default:
            return TAPPING_TERM;
    }
#else
    // Kyria Rev2. Kailh Choc White switches.
    switch (keycode) {
        // Alt
        case HOME_S:
        case HOME_L:
            return TAPPING_TERM + 50;
        // Ctrl
        case HOME_D:
        case CTL_TAB:
            return TAPPING_TERM - 30;
        // Ctrl (right)
        case HOME_K:
            return TAPPING_TERM - 40;
        // Shift
        case HOME_F:
        case HOME_J:
            return TAPPING_TERM - 40;
        case LT_BSPC:
            return TAPPING_TERM - 70;
        case LT_ENT:
            return TAPPING_TERM - 40;
        case NAV:
            return TAPPING_TERM - 40;
        default:
            return TAPPING_TERM;
    }
#endif
}
