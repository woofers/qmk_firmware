#include QMK_KEYBOARD_H

#define _BASE 0
#define _WEB 1
#define _RAISE 2
#define _NUM 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  REFRESH,
  SEARCH,
  BAR,
  INSPECT
};

enum combos {
  SHIFT_DELETE,
  SHIFT_SPACE
};

const uint16_t PROGMEM shift_delete[] = { KC_LSFT, KC_BSPC, COMBO_END };
const uint16_t PROGMEM shift_space[] = { KC_LSFT, KC_SPC, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
  [SHIFT_DELETE] = COMBO(shift_delete, KC_DEL),
  [SHIFT_SPACE] = COMBO(shift_space, KC_ENT)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_GRV,        KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,       KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_DEL, TO(_NUM),
    KC_TAB,        KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,       KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
    KC_ESC,        KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,       KC_L,   KC_SCLN, KC_QUOT, KC_ENT, \
    OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,    KC_DOT, KC_SLSH, KC_UP,   KC_CAPS, \
    KC_LCTL,       KC_LGUI, KC_LALT, TO(_WEB), KC_SPC,           _______, KC_BSPC, TO(_RAISE), KC_APP, KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_WEB] = LAYOUT(
    KC_ESC,    _______,  _______, _______, _______,   KC_F5,    _______, _______, _______, _______, _______, _______, _______, KC_DEL, KC_INS, \
    _______,   _______,  KC_UP,   _______, REFRESH,   BAR,      _______, _______, _______, _______, _______, _______, _______, _______,  \
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
    _______, KC_SPACE, KC_SPACE, KC_SPC,  _______,          KC_P0,   KC_P0,   KC_PDOT, KC_PENT, _______, _______, _______
  )
};
