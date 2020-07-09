#include QMK_KEYBOARD_H
#include "raw_hid.h"

#define _BASE 0
#define _LOWER 1
#define _NUM 2

#define SHIFT_KEY KC_LSFT
#define shift_init() static bool is_shifted; static bool is_shift_force_released
#define has_shift() get_mods() & MOD_MASK_SHIFT
#define unshift() del_mods(MOD_MASK_SHIFT); is_shift_force_released = true
#define reshift() if (is_shifted && is_shift_force_released) register_code(SHIFT_KEY); is_shift_force_released = false
#define enable_shift() is_shifted = true; if (!is_shift_force_released) register_code(SHIFT_KEY)
#define disable_shift() is_shifted = false; if (!is_shift_force_released) unregister_code(SHIFT_KEY)

#define has_ctrl() get_mods() & MOD_MASK_CTRL
#define unctrl() del_mods(MOD_MASK_CTRL)

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
  SHIFT,
  BACKSPACE,
  FUNC,
  EXIT,
  ESCAPE,
  CANCEL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  shift_init();
  static bool func_was_down;
  switch (keycode) {
    case SHIFT: {
      if (record->event.pressed) {
        enable_shift();
      }
      else {
        disable_shift();
      }
      break;
    }
    case BACKSPACE: {
      static uint8_t del_mod;
      if (record->event.pressed) {
        if (has_shift()) {
          unshift();
          del_mod = KC_DEL;
        }
        else {
          del_mod = KC_BSPC;
        }
        register_code(del_mod);
      }
      else {
        unregister_code(del_mod);
        reshift();
      }
      break;
    }
    case FUNC: {
      if (record->event.pressed) {
        if (has_shift()) {
          layer_on(_NUM);
        }
        else {
          layer_on(_LOWER);
        }
      }
      break;
    }
    case EXIT: {
      if (record->event.pressed && !func_was_down) {
        layer_off(_NUM);
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
    case CANCEL: {
      if (record->event.pressed) SEND_STRING(SS_LCTL("g"));
      break;
    }
  }

  func_was_down = keycode == FUNC && !record->event.pressed;

#ifdef KEY_COMBOS
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
#endif

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
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5, KC_6,      KC_7,      KC_8,     KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_HOME, KC_END, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T, KC_Y,      KC_U,      KC_I,     KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,         \
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,     KC_G, KC_H,      KC_J,      KC_K,     KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                   \
    SHIFT,   KC_Z,    KC_X,    KC_C,    KC_V,     KC_B, KC_N,      KC_M,      KC_COMM,  KC_DOT,  KC_SLSH, KC_UP,   FUNC,                     \
    KC_LCTL, KC_LGUI, KC_LALT, KC_APP,  KC_SPACE,       BACKSPACE, BACKSPACE, CANCEL,   KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_LOWER] = LAYOUT(
    KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  _______, _______, \
    KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,   KC_EQL,  _______,          \
    TO(_BASE), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,                   \
    _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP,   EXIT,                      \
    _______,   _______, _______, _______, _______,          _______, _______, _______, _______, _______, KC_PGDOWN, _______
  ),
  [_NUM] = LAYOUT(
    ESCAPE,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_F1,   KC_F3, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        \
    KC_BSPC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 \
    KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, EXIT,                    \
    _______, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,           KC_SPC,  KC_SPC,  KC_SPC,  _______, _______, _______, _______
  )
};
