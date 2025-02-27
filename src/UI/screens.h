#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *bootup;
    lv_obj_t *tabview;
    lv_obj_t *dashboard;
    lv_obj_t *obj0;
    lv_obj_t *starting_pos_label;
    lv_obj_t *end_pos_label;
    lv_obj_t *song_title_label;
    lv_obj_t *album_title_label;
    lv_obj_t *music_progress_slider;
    lv_obj_t *artist_name_label;
    lv_obj_t *weather_image;
    lv_obj_t *weather_label;
    lv_obj_t *volume_label;
    lv_obj_t *obj1;
    lv_obj_t *bt_connected_label;
    lv_obj_t *volume_slider_panel;
    lv_obj_t *volume_slider;
    lv_obj_t *bt_connection_msgbox;
    lv_obj_t *bootup_label;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_BOOTUP = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_bootup();
void tick_screen_bootup();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/