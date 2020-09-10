#include QMK_KEYBOARD_H

void keyboard_post_init_user() {
  register_code(KC_NLCK);
  unregister_code(KC_NLCK);
}

enum custom_keycodes {
  DBL_ZRO = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DBL_ZRO:
      if (record->event.pressed) {
        SEND_STRING("00");
      } else {
      }
      break;

  }
  return true;
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BL,
    _FL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ,-------------------.
     * |Esc |TAB | =  | BS |
     * |----|----|----|----|
     * | FN | /  | *  | -  |
     * |----|----|----|----|
     * | 7  | 8  | 9  |    |
     * |----|----|----| +  |
     * | 4  | 5  | 6  |    |
     * |----|----|----|----|
     * | 1  | 2  | 3  |    |
     * |----|----|----| En |
     * | 0  | 00 | .  |    |
     * `-------------------'
     */
    [_BL] = LAYOUT_numpad_6x4_split_zero(
        KC_ESC,  KC_TAB,  KC_PEQL, KC_BSPC,
        MO(_FL), KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,   DBL_ZRO, KC_PDOT, KC_PENT
    ),

    /*
     * ,-------------------.
     * |    |    |    |    |
     * |----|----|----|----|
     * |    |    |    |    |
     * |----|----|----|----|
     * |    |    |    |    |
     * |----|----|----|    |
     * |    |    |    |    |
     * |----|----|----|----|
     * |    |    |    |    |
     * |----|----|----|    |
     * |    |    |RST |    |
     * `-------------------'
    */
    [_FL] = LAYOUT_numpad_6x4_split_zero(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, RESET,   _______
    )
};
