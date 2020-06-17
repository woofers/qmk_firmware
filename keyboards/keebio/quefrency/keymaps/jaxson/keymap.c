#include QMK_KEYBOARD_H
#include "raw_hid.h"

#define _BASE 0
#define _SHIFT 1
#define _WEB 2
#define _RAISE 3
#define _NUM 4

#define has_shift() get_mods() & MOD_MASK_SHIFT
#define unshift() del_mods(MOD_MASK_SHIFT)

/*
  VENDOR_ID:      0xCB10: 51984
  PRODUCT_ID:     0x2257: 8791
  RAW_USAGE_PAGE: 0xFF60
  RAW_USAGE_ID:   0x61
*/

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  REFRESH,
  SEARCH,
  BAR,
  INSPECT,
  BACKSPACE,
  SPACE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACKSPACE: {
      static uint8_t del_mod;
      static bool was_shifted;
      if (record->event.pressed) {
        was_shifted = has_shift();
        if (was_shifted) {
          unshift();
          del_mod = KC_DEL;
        }
        else {
          del_mod = KC_BSPC;
        }
        register_code(del_mod);
        if (was_shifted) register_code(KC_LSFT);
      }
      else {
        unregister_code(del_mod);
      }
      return true;
    }
    case SPACE: {
      static uint8_t space_mod;
      static bool was_shifted;
      if (record->event.pressed) {
        was_shifted = has_shift();
        if (was_shifted) {
          unshift();
          space_mod = KC_ENT;
        }
        else {
          space_mod = KC_SPC;
        }
        register_code(space_mod);
        if (was_shifted) register_code(KC_LSFT);
      }
      else {
        unregister_code(space_mod);
      }
      return true;
    }
  }
  if (!record->event.pressed) return true;
  switch (keycode) {
    case REFRESH:
      SEND_STRING(SS_LCTL(SS_LSFT("r")));
      break;
    case SEARCH:
      SEND_STRING(SS_LCTL("f"));
      break;
    case BAR:
      SEND_STRING(SS_LCTL("l"));
      break;
    case INSPECT:
      SEND_STRING(SS_LCTL(SS_LSFT("i")));
      break;
  }
  return true;
};

void raw_hid_receive(uint8_t *data, uint8_t length) {
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_GRV,    KC_1,    KC_2,    KC_3,       KC_4,    KC_5,    KC_6,      KC_7,      KC_8,       KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_DEL, KC_BSPC,
    KC_TAB,    KC_Q,    KC_W,    KC_E,       KC_R,    KC_T,    KC_Y,      KC_U,      KC_I,       KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    KC_ESC,    KC_A,    KC_S,    KC_D,       KC_F,    KC_G,    KC_H,      KC_J,      KC_K,       KC_L,   KC_SCLN, KC_QUOT, KC_ENT, \
    KC_LSFT,   KC_Z,    KC_X,    KC_C,       KC_V,    KC_B,    KC_N,      KC_M,      KC_COMM,    KC_DOT, KC_SLSH, KC_UP,   KC_APP, \
    KC_LCTL,   KC_LGUI, KC_LALT, TO(_RAISE), SPACE,            BACKSPACE, BACKSPACE, TO(_WEB),   KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_SHIFT] = LAYOUT(
    _______,  _______,  _______,  _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, TO(_BASE), \
    _______,  _______,  _______,  _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______, \
    _______,  _______,  _______,  _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, \
    _______,  _______,  _______,  _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, \
    _______,  _______,  _______,  _______,  KC_ENT,           KC_DEL,   KC_DEL,  _______, _______, _______, _______, _______
  ),
  [_WEB] = LAYOUT(
    KC_ESC,    _______,  _______, _______, _______,   KC_F5,    _______, _______, _______, _______, _______, _______, _______, KC_DEL, KC_INS, \
    _______,   _______,  KC_UP,   _______, REFRESH,   BAR,      _______, _______, INSPECT, _______, _______, _______, _______, _______, \
    TO(_BASE), KC_LEFT,  KC_DOWN, KC_RGHT, SEARCH,    _______,  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______, _______, \
    _______,   _______,  KC_DEL,  _______, _______,   _______,  _______, _______, _______, _______, _______, KC_PGUP, _______, \
    _______,   _______,  _______, XXXXXXX, _______,             _______, KC_DEL,  _______, _______, KC_HOME, KC_PGDOWN, KC_END
  ),
  [_RAISE] = LAYOUT(
    KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PGDN, KC_PGUP, \
    KC_GRV,    KC_1,    KC_2,    KC_3,     KC_4,   KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL, _______, \
    TO(_BASE), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______,   _______, _______, XXXXXXX, _______,          _______, KC_DEL,  _______, _______, _______, _______, _______
  ),
  [_NUM] = LAYOUT(
    KC_ESC,  _______,  _______,  _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PMNS, _______, _______, _______, _______, TO(_BASE), \
    _______, _______,  _______,  _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______, _______, _______, _______, \
    KC_BSPC, _______,  _______,  _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______, _______, _______, \
    KC_LSFT, _______,  _______,  _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______, _______, _______, \
    _______,  KC_SPC,   KC_SPC,   KC_SPC, _______,          KC_P0,   KC_P0,   KC_PDOT, KC_PENT, _______, _______, _______
  )
};
