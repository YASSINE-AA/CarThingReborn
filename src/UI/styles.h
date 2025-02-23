#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: dark
lv_style_t *get_style_dark_MAIN_DEFAULT();
void add_style_dark(lv_obj_t *obj);
void remove_style_dark(lv_obj_t *obj);

// Style: solid_container
lv_style_t *get_style_solid_container_MAIN_DEFAULT();
void add_style_solid_container(lv_obj_t *obj);
void remove_style_solid_container(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/