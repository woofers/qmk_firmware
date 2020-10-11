#include "config.h"
#include "keycode.h"

uint16_t leader_timer;
uint16_t LEADER = KC_NO;
#define LEADER_TIMEOUT 500

enum custom_keycodes {
  FUNC = SAFE_RANGE,
  VIM_C,
  VIM_D,
  VIM_W
};

#define KC_FOR     LCTL(KC_RIGHT)

#define KC_BACK    LCTL(KC_LEFT)
#define KC_FORWARD VIM_W
#define KC_UNDO    LCTL(KC_Z)
#define KC_YANK    LCTL(KC_C)
#define KC_PASTE   LCTL(LSFT(KC_V))
#define KC_CUT     VIM_D
#define KC_CHANGE  VIM_C
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
  SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_END)) SS_TAP(X_X)));
}

void vim_delete_all(void) {
  vim_reset();
  SEND_STRING(SS_TAP(X_HOME) SS_LCTL(SS_LSFT(SS_TAP(X_END)) SS_TAP(X_X)));
}

void vim_change_word(void) {
  vim_reset();
  SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RIGHT))) SS_TAP(X_BSPC));
}

void vim_forward_press(void) {
  register_code(KC_LCTL);
  register_code(KC_RIGHT);
}

void vim_forward_release(void) {
  unregister_code(KC_LCTL);
  unregister_code(KC_RIGHT);
}
