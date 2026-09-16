/* Copyright 2024
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

enum planck_layers {
    _BASE,
    _NUM,
    _FUNC,
    _SYM,
    _NUMSYM,
    _L5,
    _L6,
};

enum planck_keycodes {
    MACWIN_TOGG = SAFE_RANGE, // MO(_FUNC) + M: toggle Windows/Mac mode (persisted in EEPROM)
    CT_UNDO,                  // tap: Z / hold: Ctrl+Z (Win) or Cmd+Z (Mac)
    CT_CUT,                   // tap: X / hold: Ctrl+X (Win) or Cmd+X (Mac)
    CT_COPY,                  // tap: C / hold: Ctrl+C (Win) or Cmd+C (Mac)
    CT_PASTE,                 // tap: V / hold: Ctrl+V (Win) or Cmd+V (Mac)
};

enum combo_events {
    COMBO_HANGUL,     // J + L -> Ctrl+Space (Korean/English input toggle)
    COMBO_SCREENSHOT, // Q + W -> region screenshot
};

// how long CT_UNDO/CT_CUT/CT_COPY/CT_PASTE must be held before they count as "hold"
#define ZXCV_HOLD_TERM 200

typedef union {
    uint32_t raw;
    struct {
        bool mac_mode : 1; // false = Windows mode, true = Mac mode
    };
} user_config_t;

user_config_t user_config;

void eeconfig_init_user(void) {
    user_config.raw      = 0;
    user_config.mac_mode = false; // default: Windows mode
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

typedef struct {
    uint16_t keycode;
    uint8_t  base_kc;
    bool     pending;   // physically held, tap-vs-hold not decided yet
    bool     triggered; // decided as hold: mod+base_kc are currently registered
    uint16_t timer;
} zxcv_key_t;

static zxcv_key_t zxcv_keys[] = {
    {CT_UNDO, KC_Z, false, false, 0},
    {CT_CUT, KC_X, false, false, 0},
    {CT_COPY, KC_C, false, false, 0},
    {CT_PASTE, KC_V, false, false, 0},
};

// If another key is pressed while a zxcv key is still undecided, resolve it as
// a tap right now (before the interrupting key is sent) so output order is
// preserved during fast rolls, e.g. Z then K for the Korean "ㅋㅏ" sequence.
static void zxcv_resolve_pending_as_tap(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(zxcv_keys); i++) {
        if (zxcv_keys[i].pending && !zxcv_keys[i].triggered) {
            zxcv_keys[i].pending = false;
            tap_code(zxcv_keys[i].base_kc);
        }
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| Z/^Z | X/^X | C/^C | V/^V |   B  |   N  |   M  |   ,  |   .  |   /  |RShift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |Func  | GUI  |Alt/Num|Sym  | Bksp |Space |NumSym| Caps | Vol- | Vol+ |Num Tg|
 * `-----------------------------------------------------------------------------------'
 *   Hold Func + M to toggle Windows/Mac mode.
 *   J+L combo -> Ctrl+Space (input source switch).  Q+W combo -> region screenshot.
 */
[_BASE] = LAYOUT_ortho_4x12(
    KC_ESC , KC_Q   , KC_W   , KC_E         , KC_R    , KC_T   , KC_Y  , KC_U , KC_I   , KC_O   , KC_P   , KC_BSPC,
    KC_TAB , KC_A   , KC_S   , KC_D         , KC_F    , KC_G   , KC_H  , KC_J , KC_K   , KC_L   , KC_SCLN, KC_ENT ,
    KC_LSFT, CT_UNDO, CT_CUT , CT_COPY      , CT_PASTE, KC_B   , KC_N  , KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
    KC_LCTL, MO(2)  , KC_LGUI, LT(1,KC_LALT), MO(4)   , KC_BSPC, KC_SPC, MO(3), KC_CAPS, KC_VOLD, KC_VOLU, TG(1)
),

/* Num */
[_NUM] = LAYOUT_ortho_4x12(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7  , KC_P8, KC_P9  , KC_PPLS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4  , KC_P5, KC_P6  , KC_PMNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_V   , KC_TRNS, KC_TRNS, KC_P1  , KC_P2, KC_P3  , KC_PEQL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PDOT, KC_TRNS, KC_TRNS
),

/* Func (hold Func + M to toggle Windows/Mac mode) */
[_FUNC] = LAYOUT_ortho_4x12(
    KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MACWIN_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Sym */
[_SYM] = LAYOUT_ortho_4x12(
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_PIPE, KC_DQUO, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_PPLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(6)  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* NumSym */
[_NUMSYM] = LAYOUT_ortho_4x12(
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_EQL , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(6)  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* L5 (unused, all transparent) */
[_L5] = LAYOUT_ortho_4x12(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* L6 (unused, all transparent) */
[_L6] = LAYOUT_ortho_4x12(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)

};

const uint16_t PROGMEM hangul_combo[]     = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM screenshot_combo[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[] = {
    [COMBO_HANGUL]     = COMBO_ACTION(hangul_combo),
    [COMBO_SCREENSHOT] = COMBO_ACTION(screenshot_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (!pressed) return;

    switch (combo_index) {
        case COMBO_HANGUL:
            // Always Ctrl+Space, regardless of Windows/Mac mode.
            // macOS default shortcut for "Select next input source" is Ctrl+Space.
            // On Windows, bind Ctrl+Space to the IME toggle if it isn't already.
            register_code(KC_LCTL);
            tap_code(KC_SPC);
            unregister_code(KC_LCTL);
            break;
        case COMBO_SCREENSHOT:
            if (user_config.mac_mode) {
                // Cmd+Shift+4: macOS region screenshot
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_4);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            } else {
                // Win+Shift+S: Windows Snip & Sketch region screenshot
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_S);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        zxcv_resolve_pending_as_tap();
    }

    if (keycode == MACWIN_TOGG) {
        if (record->event.pressed) {
            user_config.mac_mode = !user_config.mac_mode;
            eeconfig_update_user(user_config.raw);
        }
        return false;
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(zxcv_keys); i++) {
        if (keycode == zxcv_keys[i].keycode) {
            if (record->event.pressed) {
                zxcv_keys[i].pending   = true;
                zxcv_keys[i].triggered = false;
                zxcv_keys[i].timer     = timer_read();
            } else {
                if (zxcv_keys[i].triggered) {
                    // already fired as a one-shot tap when the hold triggered; nothing left to release
                    zxcv_keys[i].triggered = false;
                } else if (zxcv_keys[i].pending) {
                    zxcv_keys[i].pending = false;
                    tap_code(zxcv_keys[i].base_kc);
                }
            }
            return false;
        }
    }

    return true;
}

void matrix_scan_user(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(zxcv_keys); i++) {
        if (zxcv_keys[i].pending && !zxcv_keys[i].triggered && timer_elapsed(zxcv_keys[i].timer) > ZXCV_HOLD_TERM) {
            zxcv_keys[i].pending   = false;
            zxcv_keys[i].triggered = true;
            // fire once as a complete tap (mod down, key tap, mod up) instead of
            // holding the modifier for as long as the physical key stays down --
            // otherwise a lingering Ctrl/Cmd would corrupt any mouse click that
            // happens before the key is released.
            uint8_t mod = user_config.mac_mode ? KC_LGUI : KC_LCTL;
            register_code(mod);
            tap_code(zxcv_keys[i].base_kc);
            unregister_code(mod);
        }
    }
}
