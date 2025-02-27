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

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 320);
    {
        lv_obj_t *parent_obj = obj;
        {
            // tabview
            lv_obj_t *obj = lv_tabview_create(parent_obj, LV_DIR_TOP, 30);
            objects.tabview = obj;
            lv_obj_set_pos(obj, 0, 26);
            lv_obj_set_size(obj, 480, 294);
            lv_obj_add_state(obj, LV_STATE_FOCUSED);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // dashboard
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Dashboard");
                    objects.dashboard = obj;
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff121212), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            objects.obj0 = obj;
                            lv_obj_set_pos(obj, 201, 57);
                            lv_obj_set_size(obj, 247, 171);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff212121), LV_PART_MAIN | LV_STATE_DEFAULT);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // starting_pos_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.starting_pos_label = obj;
                                    lv_obj_set_pos(obj, 0, 111);
                                    lv_obj_set_size(obj, 75, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "start");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff898989), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // end_pos_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.end_pos_label = obj;
                                    lv_obj_set_pos(obj, 170, 111);
                                    lv_obj_set_size(obj, 62, 16);
                                    lv_label_set_text(obj, "end");
                                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff898989), LV_PART_MAIN | LV_STATE_DEFAULT);
                                }
                                {
                                    // song_title_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.song_title_label = obj;
                                    lv_obj_set_pos(obj, -1, 33);
                                    lv_obj_set_size(obj, 198, 16);
                                    lv_label_set_text(obj, "Song: Darude Sandstorm");
                                }
                                {
                                    // album_title_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.album_title_label = obj;
                                    lv_obj_set_pos(obj, -1, 9);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Album: John Doe");
                                }
                                {
                                    // music_progress_slider
                                    lv_obj_t *obj = lv_slider_create(parent_obj);
                                    objects.music_progress_slider = obj;
                                    lv_obj_set_pos(obj, 7, 90);
                                    lv_obj_set_size(obj, 190, 11);
                                }
                                {
                                    // artist_name_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.artist_name_label = obj;
                                    lv_obj_set_pos(obj, -1, 58);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Artist: John Doe");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 1, 57);
                            lv_obj_set_size(obj, 197, 171);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // weather_image
                                    lv_obj_t *obj = lv_img_create(parent_obj);
                                    objects.weather_image = obj;
                                    lv_obj_set_pos(obj, 40, 9);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_img_set_src(obj, &img_weather);
                                }
                                {
                                    // weather_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.weather_label = obj;
                                    lv_obj_set_pos(obj, 18, 103);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Weather is Sunny!");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_obj_create(parent_obj);
                            lv_obj_set_pos(obj, 1, -2);
                            lv_obj_set_size(obj, 447, 54);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    lv_obj_set_pos(obj, -1, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Current time: 00:00:00s");
                                }
                                {
                                    // volume_label
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.volume_label = obj;
                                    lv_obj_set_pos(obj, 304, 1);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_label_set_text(obj, "Volume:");
                                }
                            }
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 480, 26);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1976d2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // bt_connected_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.bt_connected_label = obj;
                    lv_obj_set_pos(obj, -13, -13);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Disconnected. Please connect your phone.");
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                {
                    // bluetooth_image
                    lv_obj_t *obj = lv_img_create(parent_obj);
                    objects.bluetooth_image = obj;
                    lv_obj_set_pos(obj, 438, -13);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_img_set_src(obj, &img_bluetooth);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                }
            }
        }
        {
            // volume_slider_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.volume_slider_panel = obj;
            lv_obj_set_pos(obj, 101, 129);
            lv_obj_set_size(obj, 279, 63);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // volume_slider
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.volume_slider = obj;
                    lv_obj_set_pos(obj, -6, 8);
                    lv_obj_set_size(obj, 255, 10);
                    lv_slider_set_value(obj, 25, LV_ANIM_OFF);
                }
            }
        }
        {
            // bt_connection_msgbox
            lv_obj_t *obj = lv_msgbox_create(parent_obj, "", "", 0, true);
            objects.bt_connection_msgbox = obj;
            lv_obj_set_pos(obj, 146, 108);
            lv_obj_set_size(obj, 200, 130);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 92, -4);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Bluetooth Connected");
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
