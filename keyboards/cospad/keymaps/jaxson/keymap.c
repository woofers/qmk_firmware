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
        tap_code(KC_P0);
        tap_code(KC_P0);
      } else {
      }
      break;

  }
  return true;
};

enum layer_names {
  _BL,
  _FL,
  _GM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ,-------------------.
     * | Spc| Tab| =  |Back|
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
        KC_SPC,  KC_TAB,  KC_PEQL, KC_BSPC,
        MO(_FL), KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,
        KC_P0,   DBL_ZRO, KC_PDOT, KC_PENT
    ),

    /*
     * ,-------------------.
     * | Esc| Tab| =  |Back|
     * |----|----|----|----|
     * | FN | \  | !  | _  |
     * |----|----|----|----|
     * |Left| ↑  |PgUp|    |
     * |----|----|----| (  |
     * | ←  | $  | →  |    |
     * |----|----|----|----|
     * | End| ↓  |PgDn|    |
     * |----|----|----| )  |
     * | Ins| RST| Del|    |
     * `-------------------'
    */
    [_FL] = LAYOUT_numpad_6x4_split_zero(
        KC_ESC,  TG(_GM), KC_PEQL, KC_BSPC,
        _______, KC_BSLS, KC_EXLM, KC_UNDS,
        KC_HOME,   KC_UP, KC_PGUP,
        KC_LEFT,  KC_DLR, KC_RGHT, KC_LPRN,
         KC_END, KC_DOWN, KC_PGDN,
         KC_INS,   RESET,  KC_DEL, KC_RPRN
    ),
    /*
     * ,-------------------.
     * | Esc| FN | =  |Back|
     * |----|----|----|----|
     * | Tab| F  | G  | _  |
     * |----|----|----|----|
     * | Q  | W  | E  |    |
     * |----|----|----| R  |
     * | A  | S  | D  |    |
     * |----|----|----|----|
     * | Z  | X  | C  |    |
     * |----|----|----| Spc|
     * |Ctrl| Spc| Spc|    |
     * `-------------------'
    */
    [_GM] = LAYOUT_numpad_6x4_split_zero(
        KC_ESC,   TO(_BL),   KC_PEQL, KC_BSPC,
        KC_TAB,      KC_F,   KC_G,    KC_UNDS,
         KC_Q,       KC_W,   KC_E,
         KC_A,       KC_S,   KC_D,       KC_R,
         KC_Z,       KC_X,   KC_C,
         KC_LCTL,    KC_SPC, KC_SPC,   KC_SPC
    )

};
