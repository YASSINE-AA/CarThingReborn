#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static lv_meter_scale_t * scale0;
static lv_meter_indicator_t * indicator1;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // tabview
            lv_obj_t *obj = lv_tabview_create(parent_obj, LV_DIR_TOP, 60);
            objects.tabview = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 320);
            lv_obj_add_state(obj, LV_STATE_FOCUSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dashboard
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Dashboard");
                    objects.dashboard = obj;
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff121212), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 61);
                            lv_obj_set_size(obj, 208, 167);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // weather_image
                                    lv_obj_t *obj = lv_img_create(parent_obj);
                                    objects.weather_image = obj;
                                    lv_obj_set_pos(obj, 42, 8);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_img_set_src(obj, &img_weather);
                                }
                                {
                                    // weather_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.weather_label = obj;
                                    lv_obj_set_pos(obj, 18, 99);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Weather is Sunny!");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 235, -2);
                            lv_obj_set_size(obj, 212, 229);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // speed_meter
                                    lv_obj_t *obj = lv_meter_create(parent_obj);
                                    objects.speed_meter = obj;
                                    lv_obj_set_pos(obj, 11, -1);
                                    lv_obj_set_size(obj, 155, 152);
                                    {
                                        lv_meter_scale_t *scale = lv_meter_add_scale(obj);
                                        scale0 = scale;
                                        lv_meter_set_scale_ticks(obj, scale, 41, 1, 5, lv_color_hex(0xffa0a0a0));
                                        lv_meter_set_scale_major_ticks(obj, scale, 8, 3, 10, lv_color_hex(0xff000000), 10);
                                        lv_meter_set_scale_range(obj, scale, 0, 200, 300, 120);
                                        {
                                            lv_meter_indicator_t *indicator = lv_meter_add_needle_line(obj, scale, 3, lv_color_hex(0xff0000ff), -28);
                                            indicator1 = indicator;
                                            lv_meter_set_indicator_value(obj, indicator, 30);
                                        }
                                    }
                                }
                            }
                        }
                        {
                            // speed_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.speed_label = obj;
                            lv_obj_set_pos(obj, 288, 186);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Speed: 0 km/h");
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 1, -2);
                            lv_obj_set_size(obj, 208, 54);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, -1, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Current time: 00:00:00s");
                                }
                            }
                        }
                    }
                }
                {
                    // playing
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Playing");
                    objects.playing = obj;
                    lv_obj_add_state(obj, LV_STATE_FOCUSED|LV_STATE_PRESSED|LV_STATE_CHECKED);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 1, -2);
                            lv_obj_set_size(obj, 446, 230);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // song_title_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.song_title_label = obj;
                                    lv_obj_set_pos(obj, 225, 63);
                                    lv_obj_set_size(obj, 184, 16);
                                    lv_label_set_text(obj, "Song: Darude Sandstorm");
                                }
                                {
                                    // album_title_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.album_title_label = obj;
                                    lv_obj_set_pos(obj, 245, 29);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Album: John Doe");
                                }
                                {
                                    // music_progress_slider
                                    lv_obj_t *obj = lv_slider_create(parent_obj);
                                    objects.music_progress_slider = obj;
                                    lv_obj_set_pos(obj, 225, 101);
                                    lv_obj_set_size(obj, 184, 11);
                                    lv_slider_set_value(obj, 25, LV_ANIM_OFF);
                                }
                                {
                                    // music_back_btn
                                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                                    objects.music_back_btn = obj;
                                    lv_obj_set_pos(obj, 245, 146);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 32);
                                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_back, NULL);
                                }
                                {
                                    // music_pause_btn
                                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                                    objects.music_pause_btn = obj;
                                    lv_obj_set_pos(obj, 301, 146);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 32);
                                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_pause, NULL);
                                }
                                {
                                    // music_skip_button
                                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                                    objects.music_skip_button = obj;
                                    lv_obj_set_pos(obj, 355, 146);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 32);
                                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_next, NULL);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_bootup() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.bootup = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_spinner_create(parent_obj, 1000, 60);
            lv_obj_set_pos(obj, 192, 115);
            lv_obj_set_size(obj, 97, 91);
        }
        {
            // bootup_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.bootup_label = obj;
            lv_obj_set_pos(obj, 118, 216);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "A prototype by Yassine Ahmed Ali");
        }
    }
    
    tick_screen_bootup();
}

void tick_screen_bootup() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_bootup,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_bootup();
}
