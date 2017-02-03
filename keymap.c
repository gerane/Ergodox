#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE                0
#define SYMB                1
#define MDIA                2

#define SC_UNDO             LCTL(KC_Z)
#define SC_REDO             LCTL(KC_Y)
#define SC_CUT              LCTL(KC_X)
#define SC_COPY             LCTL(KC_C)
#define SC_PSTE             LCTL(KC_V)
#define SC_SELA             LCTL(KC_A)
#define SC_SAVE             LCTL(KC_S)
#define SC_OPEN             LCTL(KC_O)
#define SC_CSHT             LCTL(KC_LSFT)

#define SC_LCLN             LT(MDIA, KC_SCLN)
#define SC_TMGR             LALT(LCTL(KC_DEL))
#define SC_QUOT             GUI_T(KC_QUOT)
#define SC_SLSH             CTL_T(KC_SLSH)
#define SC_TAB              SFT_T(KC_TAB)
#define SC_ENT              SFT_T(KC_ENT)
#define SC_ZCTL             CTL_T(KC_Z)
#define SC_ASCR             LALT(KC_PSCR)


#define TD_MINS             TD(TDMINS)
#define TD_HOME             TD(TDHOME)
#define TD_COPY             TD(TDCOPY)
#define TD_LBRC             TD(TDLBRC)
#define TD_ESC              TD(TDESC)
#define TD_SLSH             TD(TDSLSH)

#define _______             KC_TRNS




enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};


//Tap Dance Declarations
enum {
  TDHOME = 0,
  TDCOPY,
  TDLBRC,
  TDMINS,
  TDESC,
  TDSLSH
};

void dance_copy (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    register_code (KC_LCTL);
    register_code (KC_C);
    unregister_code (KC_LCTL);
    unregister_code (KC_C);
  }
  else if (state->count == 2) {
    register_code (KC_LCTL);
    register_code (KC_V);
    unregister_code (KC_LCTL);
    unregister_code (KC_V);
  }
  else {
    register_code (KC_LCTL);
    register_code (KC_X);
    unregister_code (KC_LCTL);
    unregister_code (KC_X);
    reset_tap_dance (state);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TDHOME] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
  [TDCOPY] = ACTION_TAP_DANCE_FN(dance_copy),
  [TDLBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TDMINS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_EQL),
  [TDESC]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV),
  [TDSLSH] = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_SLSH),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        TD_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     TG(1),
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     TD_COPY,
        SC_CSHT,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
        KC_LSFT,  SC_ZCTL,  KC_X,     KC_C,     KC_V,     KC_B,     OSL(1),
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LALT,
                                                          SC_CUT,   SC_TMGR,
                                                                    KC_HOME,
                                                KC_BSPC,  SC_ENT,   KC_END,
        // right hand
        TG(2),    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     TD_MINS,
        TD_LBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     TD_SLSH,
                  KC_H,     KC_J,     KC_K,     KC_L,     SC_LCLN,  SC_QUOT,
        TD_HOME,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_UP,    KC_RSFT,
                            KC_RCTL,  KC_RALT,  KC_LEFT,  KC_DOWN,  KC_RGHT,
        KC_LALT,  KC_PSCR,
        KC_PGUP,
        KC_PGDN,  SC_TAB,   KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,
       _______,  KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,  _______,
       _______,  KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV,
       _______,  KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,  _______,
       _______,  KC_ENT,   _______,  _______,  _______,
                                                         _______,  _______,
                                                                   _______,
                                               _______,  _______,  _______,
       // right hand
       _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
       _______,  KC_UP,    KC_7,     KC_8,     KC_9,     KC_ASTR,  KC_F12,
                 KC_DOWN,  KC_4,     KC_5,     KC_6,     KC_PLUS,  _______,
       _______,  KC_AMPR,  KC_1,     KC_2,     KC_3,     KC_BSLS,  _______,
                           _______,  KC_DOT,   KC_0,     KC_EQL,   _______,
       _______,  _______,
       _______,
       _______, _______,  _______
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       // left hand
        _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  KC_MS_U,  _______,  _______,  KC_WH_U,
        _______,  _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  KC_WH_D,
        _______,  _______,  _______,  KC_BTN1,  KC_BTN2,
                                                          _______,  _______,
                                                                    _______,
                                                KC_BTN1,  KC_BTN2,  _______,

        // right hand
        _______,  KC_PSCR,  SC_ASCR,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,
                  _______,  KC_VOLU,  KC_VOLD,  KC_MUTE,  _______,  KC_MPLY,
        _______,  _______,  _______,  KC_MPRV,  KC_MNXT,  _______,  _______,
                            KC_HOME,  KC_END,   _______,  _______,  _______,
        _______,  _______,
        _______,
        _______,  KC_WFWD,  KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
    // [HOME_END] = ACTION_MACRO_TAP(HOME_END)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // static uint16_t key_timer;
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
          }
          break;
        case 1:
          if (record->event.pressed) { // For resetting EEPROM
            eeconfig_init();
          }
          break;
        // case HOME_END:
        //   if (record->event.pressed) {
        //       key_timer = timer_read();
        //   }
        //   else {
        //       if (timer_elapsed(key_timer) < 250) {
        //           return MACRO(T(KC_END), END);
        //       }
        //       else {
        //           return MACRO(T(KC_HOME), END);
        //       }
        //   }
        //   break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case 3:
            ergodox_right_led_3_on();
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
