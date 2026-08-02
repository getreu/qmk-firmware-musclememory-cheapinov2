// Copyright 2024 (@getreu)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef VIAL_COMBO_ENABLE
#include "vial.h"
#include "dynamic_keymap.h"
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
#include "vial.h"
#include "dynamic_keymap.h"
#endif

/**
 * VIAL-OPTIMIZED KEYMAP FOR TOTEM
 *
 * Muscle memory friendly layout v1.4.2, ported from the Cheapino vial target.
 * The TOTEM has 38 keys (no center encoder key, two extra outer bottom keys)
 * and no RGB, so the center key is dropped, the outer keys carry
 * LSFT_T(KC_TAB) / RSFT_T(KC_ENTER) on the base layer, and the RGB keys are
 * replaced by KC_NO.
 *
 * Tap dance and combos are configured via Vial's dynamic system and loaded on
 * EEPROM reset via eeconfig_init_user().
 */

/**
 * LAYER DEFINITIONS
 */
enum layers { _BASE = 0, _L1, _L2, _L3, _L4, _L5, _L6, _L7 };

/**
 * EEPROM INITIALIZATION - Set Default Combos and Tap Dances
 * This runs when EEPROM is reset (first flash or reset command).
 * Combos and tap dances are stored in EEPROM and can be reconfigured via Vial.
 */
#if defined(VIAL_COMBO_ENABLE) || defined(VIAL_TAP_DANCE_ENABLE)
void eeconfig_init_user(void) {

#ifdef VIAL_COMBO_ENABLE
    // Load Dynamic Combos (these write to EEPROM)
    vial_combo_entry_t combo = {0};

    // Combo 0: Space + Enter -> Layer 7
    combo.input[0] = LGUI_T(KC_SPC);
    combo.input[1] = LGUI_T(KC_ENT);
    combo.output = MO(_L7);
    dynamic_keymap_set_combo(0, &combo);

    // Combo 1: V + Space -> Layer 7
    combo.input[0] = RGUI_T(KC_V);
    combo.input[1] = LGUI_T(KC_SPC);
    combo.output = MO(_L7);
    dynamic_keymap_set_combo(1, &combo);

    // Combo 2: M + Enter -> Layer 7
    combo.input[0] = RGUI_T(KC_M);
    combo.input[1] = LGUI_T(KC_ENT);
    combo.output = MO(_L7);
    dynamic_keymap_set_combo(2, &combo);

    // Combo 3: ESC + Backspace -> Go to Layer 3
    combo.input[0] = LT(_L6, KC_ESC);
    combo.input[1] = LT(_L5, KC_BSPC);
    combo.output = TO(_L3);
    dynamic_keymap_set_combo(3, &combo);

    // Combo 6: TD(2) + Backspace -> Go to Layer 3 (stay in symbol layer from L3)
    combo.input[0] = TD(2);
    combo.input[1] = LT(_L5, KC_BSPC);
    combo.output = TO(_L3);
    dynamic_keymap_set_combo(6, &combo);

    // Combo 4 & 5: Outer thumbs -> Caps Lock
    combo.input[0] = OSL(_L4); combo.input[1] = TD(0);
    combo.output = KC_CAPS_LOCK;
    dynamic_keymap_set_combo(4, &combo);

    combo.input[0] = OSL(_L4); combo.input[1] = TD(1);
    combo.output = KC_CAPS_LOCK;
    dynamic_keymap_set_combo(5, &combo);
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
    // Load Dynamic Tap Dances
    vial_tap_dance_entry_t td = {0};

    // TD 0: APP / MO(_L2) momentary / TO(_L2) double-tap
    td.on_tap = KC_APP;
    td.on_hold = MO(_L2);
    td.on_double_tap = TO(_L2);
    td.custom_tapping_term = 350;
    dynamic_keymap_set_tap_dance(0, &td);

    // TD 1: TO(0) / MO(_L2) momentary / TO(_L2) double-tap
    td.on_tap = TO(0);
    td.on_hold = MO(_L2);
    td.on_double_tap = TO(_L2);
    td.custom_tapping_term = 350;
    dynamic_keymap_set_tap_dance(1, &td);

    // TD 2: TO(0) / MO(_L6)
    td.on_tap = TO(0); td.on_hold = MO(_L6); td.on_double_tap = KC_NO;
    td.custom_tapping_term = 350;
    dynamic_keymap_set_tap_dance(2, &td);

    // TD 3: KC_KP_PLUS (tap) / KC_PAST (hold) / KC_KP_PLUS (tap-hold, repeating)
    td.on_tap = KC_KP_PLUS; td.on_hold = KC_PAST; td.on_double_tap = KC_NO; td.on_tap_hold = KC_KP_PLUS;
    td.custom_tapping_term = 200;
    dynamic_keymap_set_tap_dance(3, &td);

    // TD 4: KC_KP_MINUS (tap) / KC_PSLS (hold) / KC_KP_MINUS (tap-hold, repeating)
    td.on_tap = KC_KP_MINUS; td.on_hold = KC_PSLS; td.on_double_tap = KC_NO; td.on_tap_hold = KC_KP_MINUS;
    td.custom_tapping_term = 200;
    dynamic_keymap_set_tap_dance(4, &td);

    // TD 5: KC_KP_DOT (tap) / KC_PCMM (hold) / KC_KP_DOT (tap-hold, repeating)
    td.on_tap = KC_KP_DOT; td.on_hold = KC_PCMM; td.on_double_tap = KC_NO; td.on_tap_hold = KC_KP_DOT;
    td.custom_tapping_term = 200;
    dynamic_keymap_set_tap_dance(5, &td);

    // TD 6: KC_KP_0 (tap) / KC_PEQL (hold) / KC_KP_0 (tap-hold, repeating)
    td.on_tap = KC_KP_0; td.on_hold = KC_PEQL; td.on_double_tap = KC_NO; td.on_tap_hold = KC_KP_0;
    td.custom_tapping_term = 200;
    dynamic_keymap_set_tap_dance(6, &td);
#endif

    // Finalize the sync
    vial_init();
}
#endif

/**
 * KEYMAP DATA
 * Layout for each layer (TOTEM 38-key LAYOUT).
 * Outer bottom keys: LSFT_T(KC_TAB) (left) / RSFT_T(KC_ENTER) (right) on base,
 * KC_TRNS elsewhere. Right outer thumb uses TD(0).
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    KC_Q,           KC_W,          KC_E,          KC_R,          KC_T,             KC_Y,           KC_U,          KC_I,          KC_O,          KC_P,
    LSFT_T(KC_A),   RALT_T(KC_S),  LT(_L3,KC_D),  LCTL_T(KC_F),  LALT_T(KC_G),     LALT_T(KC_H),   RCTL_T(KC_J),  LT(_L3,KC_K),  RALT_T(KC_L),  RSFT_T(KC_SCLN),
    LSFT_T(KC_TAB), KC_Z,          KC_X,          KC_C,          RGUI_T(KC_V), KC_B,   KC_N, RGUI_T(KC_M), KC_COMM,   KC_DOT,        KC_SLSH,       RSFT_T(KC_ENTER),
    OSL(_L4),       LT(_L6,KC_ESC), LGUI_T(KC_SPC),                                LGUI_T(KC_ENT), LT(_L5,KC_BSPC), TD(0)
),

[_L1] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS
),

[_L2] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   TD(3),               KC_KP_7,         KC_KP_8,          KC_KP_9,         TD(6),
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   LALT_T(KC_NUM_LOCK), RCTL_T(KC_KP_4), LT(_L3, KC_KP_5), RALT_T(KC_KP_6), RSFT_T(KC_PENT),
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   TD(4), RGUI_T(KC_KP_1), KC_KP_2, KC_KP_3, TD(5), KC_TRNS,
    KC_TRNS, TD(2), KC_TRNS,                       KC_TRNS, KC_TRNS, TD(1)
),

[_L3] = LAYOUT(
    KC_1,           KC_2,           KC_3,             KC_4,           KC_5,             KC_6,            KC_7,            KC_8,          KC_9,            KC_0,
    LSFT_T(KC_ESC), RALT_T(KC_INS), LT(_L3,KC_DEL),   LCTL_T(KC_TAB), LALT_T(KC_BSPC),  LALT_T(KC_LEFT), RCTL_T(KC_DOWN), LT(_L3,KC_UP), RALT_T(KC_RGHT), RSFT_T(KC_ENT),
    KC_TRNS, KC_GRV, KC_MINS, KC_EQL, RGUI_T(KC_LBRC), KC_RBRC,   KC_BSLS, RGUI_T(KC_QUOT), KC_COMM, KC_DOT, KC_SLSH, KC_TRNS,
    KC_TRNS, TD(2), KC_TRNS,                          KC_TRNS, KC_TRNS, TD(1)
),

[_L4] = LAYOUT(
    KC_F1,          KC_F2,          KC_F3,   KC_F4,           KC_F5,            KC_F6,          KC_F7,          KC_F8,   KC_F9,          KC_F10,
    LSFT_T(KC_F11), RALT_T(KC_F12), KC_F13,  LCTL_T(KC_F14),  LALT_T(KC_F15),   LALT_T(KC_F16), RCTL_T(KC_F17), KC_F18,  RALT_T(KC_F19), RSFT_T(KC_F20),
    KC_TRNS, KC_F21, KC_F22, KC_F23, RGUI_T(KC_F24), KC_NO,   KC_NO, RGUI_T(KC_NO), KC_NO, KC_NO, MO(_L7), KC_TRNS,
    KC_TRNS, TD(2), KC_TRNS,                          KC_TRNS, KC_TRNS, TD(1)
),

[_L5] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_HOME, KC_DEL,  KC_INS,  KC_END,  KC_BSPC,
    KC_ESC,  KC_INS,  KC_DEL,  KC_TAB,  KC_BSPC,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_PGDN, KC_PGUP, KC_NO, KC_NO, KC_TRNS,
    KC_TRNS, TD(2), KC_TRNS,                       KC_TRNS, KC_TRNS, TD(1)
),

[_L6] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    MS_BTN5, MS_BTN1, MS_BTN3, MS_BTN2, MS_BTN4,    MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, MS_BTN1,
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO, KC_TRNS,
    KC_TRNS, TD(2), KC_TRNS,                       KC_TRNS, KC_TRNS, TD(1)
),

[_L7] = LAYOUT(
    QK_BOOT,   QK_CLEAR_EEPROM, KC_NO, KC_NO, KC_NO,   KC_NO,   KC_BRID, KC_BRIU, KC_NO, KC_NO,
    QK_REBOOT, KC_NO,           KC_NO, KC_NO, KC_NO,   KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO,
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_MPLY, KC_MPRV, KC_MNXT, KC_NO, KC_NO, KC_TRNS,
    KC_TRNS, TD(2), KC_TRNS,                      KC_TRNS, KC_TRNS, TD(1)
)
};
