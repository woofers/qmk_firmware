/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include "config.h"
#include "raw_hid.h"
#include "vim.h"

#define _BASE 0
#define _LOWER 1

#define has_ctrl() get_mods() & MOD_MASK_CTRL

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FUNC: {
      static uint16_t key_timer;
      if (record->event.pressed) {
        key_timer = timer_read();
        layer_on(_LOWER);
      }
      else {
        if (timer_elapsed(key_timer) < LAYER_TIMEOUT) {
          tap_code(KC_ESC);
        }
        layer_off(_LOWER);
      }
      break;
    }
    case VIM_D: {
      if (record->event.pressed) {
        vim_leader_timeout();
        switch (LEADER) {
          case KC_D:
            vim_delete_all();
            break;
          default:
            if (has_shift()) {
              vim_delete_line();
            }
            else {
              vim_leader(KC_D);
            }
            break;
        }
      }
      break;
    }
    case VIM_C: {
      if (record->event.pressed) vim_leader(KC_C);
      break;
    }
    case VIM_W: {
      if (record->event.pressed) vim_leader_timeout();
      switch (LEADER) {
        case KC_C:
          if (record->event.pressed) vim_change_word();
          break;
        default:
          if (record->event.pressed) {
            vim_forward_press();
          }
          else {
            vim_forward_release();
          }
          break;
      }
      break;
    }
    case VIM_G: {
      if (record->event.pressed) {
        vim_leader_timeout();
        switch (LEADER) {
          case KC_G:
            vim_to_top();
            break;
          default:
            if (has_shift()) {
              vim_to_bottom();
            }
            else {
              vim_leader(KC_G);
            }
            break;
        }
      }
    }
    break;
  }
  return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_60_tsangan_hhkb(
    KC_GRV,  KC_1,    KC_2,    KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
    FUNC,    KC_A,    KC_S,    KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_LOWER),
    KC_LCTL, _______, KC_LALT,                         KC_SPC,                 KC_RALT, _______, KC_RCTL
  ),
  [_LOWER] = LAYOUT_60_tsangan_hhkb(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  _______, _______,
    _______, _______, KC_FORWARD, _______,   _______, _______, KC_YANK, KC_UNDO, KC_HOME, KC_END,   KC_PASTE, _______, _______, _______,
    _______, _______, _______,    KC_CUT,    _______, KC_TOP,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______, _______,
    _______, _______, KC_DEL,     KC_CHANGE, _______, KC_BACK, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______,                        _______,                             _______, _______, RESET
  )
};
