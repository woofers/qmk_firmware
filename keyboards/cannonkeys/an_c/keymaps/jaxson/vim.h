#include "config.h"
#include "keycode.h"

#define has_ctrl() get_mods() & MOD_MASK_CTRL
#define has_shift() get_mods() & MOD_MASK_SHIFT

uint16_t leader_timer;
uint16_t LEADER = KC_NO;

enum custom_keycodes {
  FUNC = SAFE_RANGE,
  VIM_C,
  VIM_D,
  VIM_W,
  VIM_G
};

#define KC_FOR     LCTL(KC_RIGHT)
#define KC_BACK    LCTL(KC_LEFT)
#define KC_FORWARD VIM_W
#define KC_UNDO    LCTL(KC_Z)
#define KC_YANK    LCTL(KC_C)
#define KC_PASTE   LCTL(LSFT(KC_V))
#define KC_CUT     VIM_D
#define KC_CHANGE  VIM_C
#define KC_TOP     VIM_G
#define KC_FUNC    FUNC

void vim_leader(uint16_t keycode) {
  LEADER = keycode;
  leader_timer = timer_read();
}

void vim_reset(void) {
  vim_leader(KC_NO);
}

void vim_leader_timeout(void) {
  bool timeout = timer_elapsed(leader_timer) >= LEADER_TIMEOUT;
  if (timeout) LEADER = KC_NO;
}

void vim_delete_line(void) {
  vim_reset();
  SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_END)) SS_TAP(X_X)));
}

void vim_delete_all(void) {
  vim_reset();
  SEND_STRING(SS_LCTL(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)) SS_TAP(X_X)));
}

void vim_change_word(void) {
  vim_reset();
  SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT) SS_TAP(X_BSPC))));
}

void vim_forward_press(void) {
  vim_reset();
  register_code(KC_LCTL);
  register_code(KC_RIGHT);
}

void vim_forward_release(void) {
  vim_reset();
  unregister_code(KC_LCTL);
  unregister_code(KC_RIGHT);
}

void vim_to_top(void) {
  vim_reset();
  SEND_STRING(SS_LCTL(SS_TAP(X_HOME)));
}

void vim_to_bottom(void) {
  vim_reset();
  bool had_shift = has_shift();
  if (had_shift) unregister_code(KC_LSFT);
  SEND_STRING(SS_LCTL(SS_TAP(X_END)));
  if (had_shift) register_code(KC_LSFT);
}
