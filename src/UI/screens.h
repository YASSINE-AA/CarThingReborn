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
    lv_obj_t *weather_image;
    lv_obj_t *weather_label;
    lv_obj_t *speed_meter;
    lv_obj_t *speed_label;
    lv_obj_t *playing;
    lv_obj_t *song_title_label;
    lv_obj_t *album_title_label;
    lv_obj_t *music_progress_slider;
    lv_obj_t *music_back_btn;
    lv_obj_t *music_pause_btn;
    lv_obj_t *music_skip_button;
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