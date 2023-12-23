#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* Qwerty
 *
 * ,-----------------------------------------.           ,-----------------------------------------.
 * |  Esc |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------|           |------+------+------+------+------+------|
 * |  Tab |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------|           |------+------+------+------+------+------|
 * | Shft |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  | Ctrl |
 * `-----------------------------------------'           `-----------------------------------------'
 *        ,------.         ,--------------------.    ,--------------------.          ,------.
 *        | MUTE |         | LOWER| Enter|  Del |    |BckSpc| Space| RAISE|          | MUTE |
 *        `------'         `--------------------'    `--------------------.          `------'
 *                         ,--------------------.    ,--------------------.
 *                         | Undo | Redo2| Redo |    | Vol- | Mute | Vol+ |    // 3 way thumb switch
 *                         `--------------------'    `--------------------.
 */

// Default config uses home row mods. So hold each of the keys on the home row to use ctrl, gui, alt, or shift
[_QWERTY] = LAYOUT_ximi(
      KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
                KC_MUTE,                    KC_LGUI, LOWER, KC_SPC,            KC_ENT, RAISE, KC_RALT,                      KC_MUTE,
                                            C(KC_Z), C(S(KC_Z)), C(KC_Y),      KC_VOLD, KC_MUTE, KC_VOLU
),

/* Raise
 *
 * ,-----------------------------------------.           ,-----------------------------------------.
 * | ____ |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  | ____ |
 * |------+------+------+------+------+------|           |------+------+------+------+------+------|
 * | ____ |  Left | Down |  Up  | Right| Tab |           |      |   -  |   =  |   [  |   ]  | ____ |
 * |------+------+------+------+------+------|           |------+------+------+------+------+------|
 * | ____ |  Ctrl|   `  |  GUI |  Alt |      |           |      |      |      |   \  |   '  | ____ |
 * `-----------------------------------------'           `-----------------------------------------'
 *        ,------.         ,--------------------.    ,--------------------.          ,------.
 *        | MUTE |         | LOWER|      |      |    |      |      | RAISE|          | MUTE |
 *        `------'         `--------------------'    `--------------------.          `------'
 *                         ,--------------------.    ,--------------------.
 *                         | Undo | Redo2| Redo |    | Vol- | Mute | Vol+ |    // 3 way thumb switch
 *                         `--------------------'    `--------------------.
 */
[_LOWER] = LAYOUT_ximi(
      KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                _______,          _______, _______, _______,      _______, ADJUST, _______,          _______,
                                  _______, _______, _______,      _______, _______, _______
),

/* Lower
 *
 * ,-----------------------------------------.           ,-----------------------------------------.
 * | ____ |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  | ____ |
 * |------+------+------+------+------+------|           |------+------+------+------+------+------|
 * | ____ |  Esc |      |      |      |      |           |      |   _  |   +  |   {  |   }  | ____ |
 * |------+------+------+------+------+------|           |------+------+------+------+------+------|
 * | ____ |  Caps|   ~  |      |      |      |           |      |      |      |   |  |   '  | ____ |
 * `-----------------------------------------'           `-----------------------------------------'
 *        ,------.         ,--------------------.    ,--------------------.          ,------.
 *        | MUTE |         | LOWER|      |      |    |  Del |      | RAISE|          | MUTE |
 *        `------'         `--------------------'    `--------------------.          `------'
 *                         ,--------------------.    ,--------------------.
 *                         | Undo | Redo2| Redo |    | Vol- | Mute | Vol+ |    // 3 way thumb switch
 *                         `--------------------'    `--------------------.
 */
[_RAISE] = LAYOUT_ximi(
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                _______,          _______, ADJUST, _______,      _______,  _______, _______,          _______,
                                  _______, _______, _______,      _______, _______, _______
),

/* Adjust (Lower + Raise)
 *
 * ,-----------------------------------------.           ,-----------------------------------------.
 * | ____ | RGB_T| RGB_R| RGB_F|      |QWERTY|           |   F1 |  F2  |  F3  |  F4  |  F5  | ____ |
 * |------+------+------+------+------+------|           |------+------+------+------+------+------|
 * | ____ | SPD_I| HUE_I| SAT_I| VAL_I|COLEMK|           |   F6 |  F7  |  F8  |  F9  |  F10 | ____ |
 * |------+------+------+------+------+------|           |------+------+------+------+------+------|
 * | ____ | SPD_D| HUE_D| SAT_D| VAL_D|      |           |  F11 |  F12 |      |      | Reset| ____ |
 * `-----------------------------------------'           `-----------------------------------------'
 *        ,------.         ,--------------------.    ,--------------------.          ,------.
 *        | MUTE |         | LOWER|      |      |    |      |      | RAISE|          | MUTE |
 *        `------'         `--------------------'    `--------------------.          `------'
 *                         ,--------------------.    ,--------------------.
 *                         | Undo | Redo2| Redo |    | Vol- | Mute | Vol+ |    // 3 way thumb switch
 *                         `--------------------'    `--------------------.
 */
[_ADJUST] =  LAYOUT_ximi(
      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                _______,           _______, _______, _______,           _______, _______, _______,          _______,
                                   _______, _______, _______,           _______, _______, _______
)
};
