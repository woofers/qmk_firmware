#include QMK_KEYBOARD_H
#include "raw_hid.h"

#define _BASE 0
#define _LOWER 1
#define _RAISE 2

#define has_ctrl() get_mods() & MOD_MASK_CTRL

#define KC_BACK    LCTL(KC_LEFT)
#define KC_FORWARD LCTL(KC_RIGHT)

/*
  VENDOR_ID:      0xCB10: 51984
  PRODUCT_ID:     0x2257: 8791
  RAW_USAGE_PAGE: 0xFF60
  RAW_USAGE_ID:   0x61
*/


LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_ONE_KEY(KC_FORWARD) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT))));
      tap_code(KC_BSPC);
    }
  }
}

enum custom_keycodes {
  ESCAPE = SAFE_RANGE,
  FUNC
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FUNC: {
      static uint16_t key_timer;
      if (record->event.pressed) {
        key_timer = timer_read();
        layer_on(_LOWER);
      }
      else {
        if (timer_elapsed(key_timer) < 350) {
          tap_code(KC_ESC);
        }
        layer_off(_LOWER);
      }
      break;
    }
    case ESCAPE: {
      static bool was_ctrl;
      if (record->event.pressed) {
        was_ctrl = has_ctrl();
        if (!was_ctrl) register_code(KC_ESC);
      }
      else {
        if (!was_ctrl) unregister_code(KC_ESC);
      }
      break;
    }
  }
  return true;
};

#ifdef INDICATOR_LIGHT

enum status {
  None=1,
  Normal=10,
  Insert=11,
  Visual=12,
  Operator=13
};

void raw_hid_receive(uint8_t *data, uint8_t length) {
  uint8_t key;
  switch (*data) {
    case Normal:
      key = KC_N;
      break;
    case Insert:
      key = KC_I;
      break;
    case Visual:
      key = KC_V;
      break;
    case Operator:
      key = KC_O;
      break;
    default:
      key = KC_2;
      break;
  }
  register_code(key);
  unregister_code(key);
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    FUNC,    KC_A,    KC_S,    KC_D,    KC_F,     KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______, _______,
    KC_LCTL, KC_LALT, KC_LALT, _______, KC_SPC,           KC_SPC, KC_SPC,  _______, _______, _______, _______, _______
  ),
  [_LOWER] = LAYOUT(
    KC_ESC,  KC_F1,   KC_F2,      KC_F3,      KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_DEL, KC_DEL,
    _______, _______, KC_FORWARD, _______,    _______, _______, _______, _______, KC_HOME, KC_END,   _______, _______, _______, _______,
    _______, _______, _______,    _______,    _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______, _______,
    _______, _______, _______,    KC_LEAD,    _______, KC_BACK, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______,    _______,    _______,          _______, _______, _______, _______,  _______, _______, _______
  )
};
