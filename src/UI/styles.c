#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: dark
//

void init_style_dark_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_dark_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_dark_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_dark(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_dark(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: solid_container
//

void init_style_solid_container_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff121212));
};

lv_style_t *get_style_solid_container_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_solid_container_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_solid_container(lv_obj_t *obj) {
    lv_obj_add_style(obj, get_style_solid_container_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_solid_container(lv_obj_t *obj) {
    lv_obj_remove_style(obj, get_style_solid_container_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_dark,
        add_style_solid_container,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_dark,
        remove_style_solid_container,
    };
    remove_style_funcs[styleIndex](obj);
}

