#include "display.h"
#include "quantum.h"
// #include "keyboards/mabroum/mab_pointing.h"
#include <ctype.h>

lv_obj_t * mbox1;
lv_obj_t * mbox1_title;
lv_obj_t * mbox1_text;
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Screen1_Label_CPI;
lv_obj_t * ui_Screen1_deflayer;
lv_obj_t * ui_Screen1_Label_ACC;
lv_obj_t * ui_Screen1_Label_RGB;
lv_obj_t * ui_Layer_Indicator;
lv_obj_t * ui_Screen1_deflayer_list;

uint8_t USER_EVENT_CPI_UPDATE = 0;
uint8_t USER_EVENT_ACTIVE_LAYER_CHANGE = 1;
uint8_t USER_EVENT_CAPS_WORD_UPDATE = 2;
uint8_t USER_EVENT_DRAGSCROLL_UPDATE = 3;
uint8_t USER_EVENT_SNIPING_UPDATE = 4;
uint8_t USER_EVENT_ACC_UPDATE = 5;
uint8_t USER_EVENT_RGBMODE_UPDATE = 6;

void lv_msgbox_1(const char *myString) {
    mbox1 = lv_msgbox_create(ui_Screen1, myString, "ACTIVE", NULL, false);// Do something when Caps Word activates.
    mbox1_title = lv_msgbox_get_title(mbox1);
    mbox1_text = lv_msgbox_get_text(mbox1);
    lv_obj_set_style_text_font(mbox1_title, &rb_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(mbox1_text, &rb_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_x(mbox1_title, 0);
    lv_obj_set_style_text_align(mbox1_title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_x(mbox1_text, 0);
    lv_obj_set_style_text_align(mbox1_text, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(mbox1_text, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align(mbox1, LV_ALIGN_CENTER, 0, -20);
    lv_obj_center(mbox1_title);
    lv_obj_center(mbox1_text);
}

void caps_word_set_user(bool active) {
    if (active) {
        lv_msgbox_1("CAPS WORD");
    } else {
        lv_msgbox_close(mbox1);
    }
}

void dragscroll_set_user(bool active) {
    if (active) {
        lv_msgbox_1("DRAG SCROLL");
    } else {
        lv_msgbox_close(mbox1);
    }
}

void sniping_set_user(bool active) {
    if (active) {
        lv_msgbox_1("SNIPING MODE");
    } else {
        lv_msgbox_close(mbox1);
    }
}

void ui_active_layer_change(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_ACTIVE_LAYER_CHANGE) {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case 0:
                lv_img_set_src(ui_Layer_Indicator, &apple);
                break;
            case 3:
                lv_img_set_src(ui_Layer_Indicator, &window);
                break;
            case 1:
            case 4:
                lv_img_set_src(ui_Layer_Indicator, &tools);
                break;
            case 2:
            case 5:
                lv_img_set_src(ui_Layer_Indicator, &hash);
                 break;
        }
  }
}

uint8_t qmk_lv_active_layer(void) {
    uint8_t active_layer = 0;
    active_layer = get_highest_layer(layer_state);
    return active_layer;
}

void set_cpi_text_value(lv_obj_t* lbl) {
    if (lv_obj_is_valid(lbl)) {
        char buf[11];
        snprintf(buf, sizeof(buf), "CPI: %d", (int)pointing_device_get_cpi());
        lv_label_set_text(lbl, buf);
    }
}

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;

//----------------------------------------------------------
// RGB Matrix naming
#    include <rgb_matrix.h>

#    if defined(RGB_MATRIX_EFFECT)
#        undef RGB_MATRIX_EFFECT
#    endif // defined(RGB_MATRIX_EFFECT)

#    define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#    include "rgb_matrix_effects.inc"
#    undef RGB_MATRIX_EFFECT
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
};

#    define RGB_MATRIX_EFFECT(x)    \
        case RGB_MATRIX_EFFECT_##x: \
            return #x;
const char *rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#    include "rgb_matrix_effects.inc"
#    undef RGB_MATRIX_EFFECT
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
        default:
            return "UNKNOWN";
    }
}

void set_rgbmode_text_value(lv_obj_t* lbl) {
    char buf[32];
    if (!rgb_matrix_config.enable) {
        sprintf(buf, "RGB: OFF");
    }
    else {
        uint8_t curr_effect = rgb_matrix_config.mode;
        if (lv_obj_is_valid(lbl)) {
            snprintf(buf, sizeof(buf), "RGB: %s", rgb_matrix_name(curr_effect));
            for (int i = 5; i < sizeof(buf); ++i) {
                if (buf[i] == 0)
                    break;
                else if (buf[i] == '_')
                    buf[i] = ' ';
                else if (buf[i - 1] == ' ')
                    buf[i] = toupper(buf[i]);
                else if (buf[i - 1] != ' ')
                    buf[i] = tolower(buf[i]);
            }
        }
    }
    lv_label_set_text(lbl, buf);
}

void ui_render_rgbmode(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_RGBMODE_UPDATE) {
         set_rgbmode_text_value(ui_Screen1_Label_RGB);
    }
}
#endif // RGB_MATRIX_ENABLE

// SADEK: Add this back later when I implement functions for acceleration
// #ifdef FP_POINTING_ACCELERATION_ENABLE
// void set_acc_text_value(lv_obj_t* lbl) {
//     if (lv_obj_is_valid(lbl)) {
//         char buf[11];
//       if(/* acceleration function call goes here */) {
//           snprintf(buf, sizeof(buf), "ACC: ON");
//       }
//       else {
//         snprintf(buf, sizeof(buf), "ACC: OFF");
//       }
//       lv_label_set_text(lbl, buf);
//     }
// }
//
// void ui_render_acc(lv_event_t * e) {
//     lv_event_code_t event_code = lv_event_get_code(e);
//     if(event_code == USER_EVENT_ACC_UPDATE) {
//          set_acc_text_value(ui_Screen1_Label_ACC);
//     }
// }
//
// #endif

void ui_render_cpi(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == USER_EVENT_CPI_UPDATE) {
         set_cpi_text_value(ui_Screen1_Label_CPI);
    }
}

// SADEK: Add this back later when I implement functions for acceleration
// #ifdef FP_POINTING_ACCELERATION_ENABLE
// bool qmk_lv_get_acc(void) {
//     return mab_get_pointer_acceleration_enabled();
// }
// #endif

void lvgl_event_triggers(void) {
    static uint16_t last_cpi   = 0xFFFF;
    uint16_t curr_cpi   = pointing_device_get_cpi();
    bool cpi_redraw = false;
    if (last_cpi != curr_cpi) {
        last_cpi   = curr_cpi;
        cpi_redraw = true;
    }
    if (cpi_redraw) {
        lv_event_send(ui_Screen1_Label_CPI, USER_EVENT_CPI_UPDATE, NULL);
    }

    // SADEK: Add this back later when I implement functions for acceleration
    // #ifdef FP_POINTING_ACCELERATION_ENABLE
    // static uint16_t last_acc   = 0xFFFF;
    // uint16_t curr_acc   = mab_get_pointer_acceleration_enabled();
    // bool acc_redraw = false;
    // if (last_acc != curr_acc) {
    //     last_acc   = curr_acc;
    //     acc_redraw = true;
    // }
    // if (acc_redraw) {
    //     lv_event_send(ui_Screen1_Label_ACC, USER_EVENT_ACC_UPDATE, NULL);
    // }
    // #endif

    bool layer_state_redraw = false;
    static uint32_t last_layer_state   = 0;
    if (last_layer_state != layer_state) {
        last_layer_state   = layer_state;
        layer_state_redraw = true;
    }
    if (layer_state_redraw) {
        lv_event_send(ui_Layer_Indicator, USER_EVENT_ACTIVE_LAYER_CHANGE, NULL);
    }
#ifdef RGB_MATRIX_ENABLE
    bool            rgb_effect_redraw = false;
    static uint16_t last_effect       = 0xFFFF;
    uint8_t         curr_effect       = rgb_matrix_config.mode;
    if (last_effect != curr_effect) {
        last_effect       = curr_effect;
        rgb_effect_redraw = true;
    }
    static uint16_t last_rgb_status   = 0xFFFF;
    uint8_t  curr_rgb_status  = rgb_matrix_config.enable;
    if (last_rgb_status  != curr_rgb_status) {
        last_rgb_status   = curr_rgb_status;
        rgb_effect_redraw = true;
    }
    if (rgb_effect_redraw) {
        lv_event_send(ui_Screen1_Label_RGB, USER_EVENT_RGBMODE_UPDATE, NULL);
    }
#endif
}

void display_init(void) {
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1 = lv_obj_create(NULL);

    ui_Layer_Indicator = lv_img_create(ui_Screen1);
    /* lv_img_set_src(ui_Image1, &mac); */ // set image on startup
    lv_obj_add_event_cb(ui_Layer_Indicator, ui_active_layer_change, USER_EVENT_ACTIVE_LAYER_CHANGE, NULL);
    lv_obj_set_width(ui_Layer_Indicator, LV_SIZE_CONTENT);   /// 81
    lv_obj_set_height(ui_Layer_Indicator, LV_SIZE_CONTENT);    /// 55
    lv_obj_set_x(ui_Layer_Indicator, 25);
    lv_obj_set_y(ui_Layer_Indicator, -10);
    lv_obj_set_align(ui_Layer_Indicator, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_Layer_Indicator, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Layer_Indicator, LV_OBJ_FLAG_SCROLLABLE);
    lv_event_send(ui_Layer_Indicator, USER_EVENT_ACTIVE_LAYER_CHANGE, NULL);

    ui_Screen1_Label_CPI = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label_CPI, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label_CPI, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label_CPI, 120);
    lv_obj_set_y(ui_Screen1_Label_CPI, 25);
    lv_obj_set_style_text_font(ui_Screen1_Label_CPI, &rb_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Screen1_Label_CPI, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(ui_Screen1_Label_CPI, ui_render_cpi, USER_EVENT_CPI_UPDATE, NULL);

// SADEK: Add this back later when I implement functions for acceleration
// #ifdef FP_POINTING_ACCELERATION_ENABLE
    // ui_Screen1_Label_ACC = lv_label_create(ui_Screen1);
    // lv_obj_set_width(ui_Screen1_Label_ACC, LV_SIZE_CONTENT);   /// 1
    // lv_obj_set_height(ui_Screen1_Label_ACC, LV_SIZE_CONTENT);    /// 1
    // lv_obj_set_x(ui_Screen1_Label_ACC, 120);
    // lv_obj_set_y(ui_Screen1_Label_ACC, 65);
    // lv_obj_set_style_text_font(ui_Screen1_Label_ACC, &rb_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_align(ui_Screen1_Label_ACC, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_add_event_cb(ui_Screen1_Label_ACC, ui_render_acc, USER_EVENT_ACC_UPDATE, NULL);
// #endif

#ifdef RGB_MATRIX_ENABLE
    ui_Screen1_Label_RGB = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label_RGB, 150);
    lv_obj_set_style_text_font(ui_Screen1_Label_RGB, &rb_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_x(ui_Screen1_Label_RGB, 120);
    lv_obj_set_y(ui_Screen1_Label_RGB, 105);
    lv_label_set_text(ui_Screen1_Label_RGB, "RGB");
    lv_obj_add_event_cb(ui_Screen1_Label_RGB, ui_render_rgbmode, USER_EVENT_RGBMODE_UPDATE, NULL);
#endif

    lv_disp_load_scr(ui_Screen1);
}
