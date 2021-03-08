/* Copyright 2020 Alexander Dergachev (alexander.dergachev@gmail.com)
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

enum torn_layers { _QWERTY, _LOWER, _RAISE, _NUMPAD };

#define G_DEL LGUI_T(KC_DEL)
#define G_ENT RGUI_T(KC_ENT)

#define C_BSPC LCTL_T(KC_BSPC)
#define C_SPC RCTL_T(KC_SPC)

#define S_EQL LSFT_T(KC_EQL)
#define S_MINS RSFT_T(KC_MINS)

#define R_TAB LT(_RAISE, KC_TAB)
#define R_BSLS LT(_RAISE, KC_BSLS)

#define L_GRV LT(_LOWER, KC_GRV)
#define L_QUOT LT(_LOWER, KC_QUOT)

/*
 * Tap Dance definitions
 */
enum {
    TER,  // TabEscRais - Single tap: Tab, Single hold: Esc, Double tap: _RAISE layer
    NOFG, // NumpadOnOffGrave - Single Tap: KC_GRV, Single hold: momentary _NUMPAD layer, Double tap: toggle _NUMPAD layer
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * | Esc  |      |      |      |      |      |    |      |      |      |      |      | Raise|
 * | Raise|      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | `    |   A  |   S  |   D  |   F  |   G  |    |   H  |   J  |   K  |   L  |   ;  |  '   |
 * | Lower|      |      |      |      |      |    |      |      |      |      |      | Lower|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |  =+  |   Z  |   X  |   C  |   V  |   B  |    |   N  |   M  |   ,  |   .  |   /  |  -_  |
 * | Shift|      |      |      |      |      |    |      |      |      |      |      | Shift|
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               | NumP | Alt  | Bksp | Del  |    |Enter |Space | Alt  | ____ |
 *               |      |      | Ctrl | Gui  |    | Gui  | Ctrl |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_QWERTY] = LAYOUT_split_3x6_4(
    TD(TER),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    R_BSLS,
    L_GRV,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, L_QUOT,
    S_EQL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, S_MINS ,
                TG(_NUMPAD),    KC_LALT, C_BSPC,  G_DEL,     G_ENT,   C_SPC,   KC_RALT, _______
),

/* Lower
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |  [   |   !  |   @  |   #  |   $  |   %  |    |   ^  |   &  |   *  |   (  |   )  |  ]   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               | NumP | Alt  | Bksp | Del  |    |Enter |Space | Alt  | ____ |
 *               |      |      | Ctrl | Gui  |    | Gui  | Ctrl |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_LOWER] = LAYOUT_split_3x6_4(
    KC_LBRC, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_RBRC,
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_TRNS, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Raise
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |    | S+H  | S+A+L|  UP  | S+A+R| S+E  |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |    | Home | Left | Down | Right| End  | PgUp |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |  F11 |  F12 |      |      |      |    | A+L  | S+L  | S+D  | S+R  | A+R  | PgDn |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               | NumP | Alt  | Bksp | Del  |    |Enter |Space | Alt  | ____ |
 *               |      |      | Ctrl | Gui  |    | Gui  | Ctrl |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_RAISE] = LAYOUT_split_3x6_4(
    KC_TRNS, KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,     S(KC_HOME), S(A(KC_LEFT)), KC_UP,      S(A(KC_RGHT)), S(KC_END),  KC_TRNS,
    KC_TRNS, KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_HOME,    KC_LEFT,       KC_DOWN,    KC_RGHT,       KC_END,     KC_PGUP,
    KC_TRNS, KC_F11, KC_F12,  _______, _______, _______,   A(KC_LEFT), S(KC_LEFT),    S(KC_DOWN), S(KC_RGHT),    A(KC_RGHT), KC_PGDN ,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Numpad
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |      |      |      |      |      |      |    |  .   |  7   |  8   |  9   |  -   |  /   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |  ,   |  4   |  5   |  6   |  +   |  *   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |  0   |  1   |  2   |  3   | Enter|      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 *               | NumP | Alt  | Bksp | Del  |    |Enter |Space | Alt  | ____ |
 *               |      |      | Ctrl | Gui  |    | Gui  | Ctrl |      |      |
 *               `---------------------------'    `---------------------------'
 */
[_NUMPAD] = LAYOUT_split_3x6_4(
    _______, _______, _______, _______, _______, _______,   KC_KP_DOT, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS, KC_KP_SLASH,
    _______, _______, _______, _______, _______, _______,   KC_COMM,   KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS,  KC_KP_ASTERISK,
    _______, _______, _______, _______, _______, _______,   KC_KP_0,   KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, _______,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
)

};

const uint16_t PROGMEM encoder_keymaps[][2][2] = {
    [_QWERTY] =  { { C(S(KC_TAB)), C(KC_TAB) },     { G(A(KC_LEFT)), G(A(KC_RIGHT)) } },
    [_LOWER]  =  { { C(KC_LEFT),   C(KC_RGHT) },    { KC__VOLDOWN,   KC__VOLUP } },
    [_RAISE]  =  { { G(KC_LEFT),   G(KC_RGHT) },    { G(KC_TAB),     G(S(KC_TAB)) } },
    [_NUMPAD] =  { { KC_LEFT,      KC_RIGHT },      { KC_UP,         KC_DOWN } },
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    torn_set_led(0, IS_LAYER_ON_STATE(state, _RAISE));
    torn_set_led(1, IS_LAYER_ON_STATE(state, _LOWER));
    torn_set_led(2, IS_LAYER_ON_STATE(state, _NUMPAD));
    return state;
}

/*
 * Enable `IGNORE_MOD_TAP_INTERRUPT` for all modifiers except `Shift`.
 * For more info see `IGNORE_MOD_TAP_INTERRUPT_PER_KEY` in `docs/tap_hold.md`.
 */

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case S_EQL:
            return false;
        case S_MINS:
            return false;
        default:
            return true;
    }
}

/*
 * Enable `PERMISSIVE_HOLD` for `Shift` modifers.
 * For more info see `PERMISSIVE_HOLD_PER_KEY` in `docs/tap_hold.md`.
 */

bool get_permissive_hold(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case S_EQL:
            return true;
        case S_MINS:
            return true;
        default:
            return false;
    }
}

/*
 * Tap Dance related code
 */
enum {
    DEFAULT,
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP
};

typedef uint8_t State;

static State ter_state = DEFAULT;
static State nofg_state = DEFAULT;

// Determine the current tap dance state
uint8_t current_dance(qk_tap_dance_state_t* state) {
    switch(state->count) {
        case 1:
            if (state->pressed) {
                return SINGLE_HOLD;
            }
            else {
                return SINGLE_TAP;
            }
        case 2:
            return DOUBLE_TAP;

        default:
            return DEFAULT;
    }
}

void ter_finished(qk_tap_dance_state_t* state, void* user_data) {
    ter_state = current_dance(state);
    switch (ter_state) {
        case SINGLE_TAP:
            tap_code(KC_TAB);
            break;
        case SINGLE_HOLD:
            layer_on(_RAISE);
            break;
        case DOUBLE_TAP:
            tap_code(KC_ESC);
            break;

        default:
            return;
    }
}

void ter_reset(qk_tap_dance_state_t* state, void* user_data) {
    if (ter_state == SINGLE_HOLD) {
        layer_off(_RAISE);
    }
    ter_state = DEFAULT;
}

void nofg_finished(qk_tap_dance_state_t* state, void* user_data) {
    nofg_state = current_dance(state);
    switch (nofg_state) {
        case SINGLE_TAP:
            tap_code(KC_GRV);
            break;
        case SINGLE_HOLD:
            layer_on(_LOWER);
            break;
        case DOUBLE_TAP:
            if (layer_state_is(_NUMPAD)) {
                layer_off(_NUMPAD);
            } else {
                layer_on(_NUMPAD);
            }
            break;

        default:
            return;
    }
}

void nofg_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (nofg_state == SINGLE_HOLD) {
        layer_off(_LOWER);
    }
    nofg_state = DEFAULT;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TER]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ter_finished, ter_reset),
    [NOFG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nofg_finished, nofg_reset)
};