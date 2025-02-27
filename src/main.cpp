/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  */

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <UI/ui.h>


// ============= BLUETOOTH ============== //
#include <bluetooth/bt_connection.hpp>

// ============== HW CONTROLS ============ //
#include <controls/volume_control.hpp>

/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 as the examples and demos are now part of the main LVGL library. */

/*Change to your screen resolution*/
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;
const uint8_t PM_VCC_PIN = 18;
const uint8_t PM_OUT_PIN = 34;
const uint16_t PM_OUT_MAX_VALUE = 4095;

PMVolumeControl volumeControl(PM_VCC_PIN, PM_OUT_PIN, PM_OUT_MAX_VALUE);

bool is_volume_slider_shown = false;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * screenHeight / 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp_drv);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    uint16_t touchX, touchY;

    bool touched = tft.getTouch(&touchX, &touchY, 600);

    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;

        Serial.print("Data x ");
        Serial.println(touchX);

        Serial.print("Data y ");
        Serial.println(touchY);
    }
}


// ============= Scrolling Logic ============== //
#define SCROLL_DELAY 200
#define MAX_SCROLL_POS 25

typedef struct {
    int scroll_pos;
    unsigned long last_scroll_time;
} ScrollState;

ScrollState song_title_scroll = {0, 0};
ScrollState album_title_scroll = {0, 0};
ScrollState artist_name_scroll = {0, 0};

void scroll_label_text(lv_obj_t *label, const char *text, ScrollState *state)
{
    if (millis() - state->last_scroll_time > SCROLL_DELAY)
    {
        state->last_scroll_time = millis();

        char display_text[MAX_SCROLL_POS + 1];
        int text_length = strlen(text);

        if (text_length > MAX_SCROLL_POS)
        {
            for (int i = 0; i < MAX_SCROLL_POS; i++)
            {
                display_text[i] = text[(state->scroll_pos + i) % text_length];
            }
            display_text[MAX_SCROLL_POS] = '\0';

            lv_label_set_text(label, display_text);

            state->scroll_pos++;
            if (state->scroll_pos >= text_length)
            {
                state->scroll_pos = 0;
            }
        }
        else
        {
            lv_label_set_text(label, text);
        }
    }
}
const char *boot_msgs[] = {
    "Rolling boot dice... nat 1, retrying.     ",
    "Please wait... or restart, your choice.   ",
    "Optimizing... lying about progress.       ",
    "Generating random errors...    ",
    "Translating machine noises... beep boop.  ",
    "Warming up electrons... almost warm!      ",
    "Simulating hard work... looking busy.     ",
    "Installing fun... encountered a problem.  ",
    "Awaiting user patience... stuck at 0%.    ",
    "Pretending to load... looking important.  "};

static void switch_to_main(lv_timer_t *timer)
{
    lv_scr_load((lv_obj_t *)timer->user_data);
    lv_timer_del(timer);
}
void show_boot_message(lv_timer_t *timer)
{
    int msg_index = lv_rand(0, sizeof(boot_msgs) / sizeof(boot_msgs[0]) - 1);
    lv_label_set_text(objects.bootup_label, boot_msgs[msg_index]);
    lv_timer_del(timer);

}
void setup_screens(void)
{
    lv_scr_load(objects.bootup);
    lv_timer_create(show_boot_message, 1500, NULL);
    lv_timer_create(switch_to_main, 8000, objects.main);
}

void hide_bt_connect_msgbox(lv_timer_t *timer)
{
    lv_obj_add_flag(objects.bt_connection_msgbox, LV_OBJ_FLAG_HIDDEN);
    lv_timer_del(timer);

}

void show_bt_connect_msgbox()
{
    lv_obj_clear_flag(objects.bt_connection_msgbox, LV_OBJ_FLAG_HIDDEN);
}

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */
    Serial.print("Free Heap Before Bluetooth: ");
    Serial.println(ESP.getFreeHeap());


    
    bt_connection_broadcast(); // Initialize Bluetooth
    volumeControl.init(); // Initialize Volume Knob

    // lv_label_set_text(objects.song_title_label, );

    Serial.print("Free Heap After Bluetooth: ");
    Serial.println(ESP.getFreeHeap());
    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

    tft.begin();        /* TFT init */
    tft.setRotation(3); /* Landscape orientation, flipped */

    /*Set the touchscreen calibration data,
     the actual data for your display can be acquired using
     the Generic -> Touch_calibrate example from the TFT_eSPI library*/
    uint16_t calData[5] = {275, 3620, 264, 3532, 1};
    tft.setTouch(calData);

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight / 10);

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    ui_init();

    setup_screens();

    //lv_tabview_set_act(objects.tabview, 0, LV_ANIM_ON);

    /* Try an example. See all the examples
     * online: https://docs.lvgl.io/master/examples.html
     * source codes: https://github.com/lvgl/lvgl/tree/e7f88efa5853128bf871dde335c0ca8da9eb7731/examples */
    // lv_example_btn_1();

    /*Or try out a demo. Don't forget to enable the demos in lv_conf.h. E.g. LV_USE_DEMOS_WIDGETS*/
    // lv_demo_widgets();
    //  lv_demo_benchmark();
    //  lv_demo_keypad_encoder();
    //  lv_demo_music();
    //  lv_demo_printer();
    //  lv_demo_stress();
    lv_tabview_set_act(objects.tabview, 1, LV_ANIM_ON);

    // lv_label_set_text(objects.song_title_label, bluetooth_context->current_metadata.title);

    Serial.println("Setup done");
}
bool bt_is_init = false;

void format_time_display(char *buff, uint32_t time, size_t buff_size)
{
    uint32_t minutes = time / 60;
    uint32_t seconds = time % 60;
    if (time < 3600)
        snprintf(buff, buff_size, "%u:%02u", minutes, seconds);
    else
    {
        uint32_t hours = time / 3600;
        minutes = (time % 3600) / 60;
        snprintf(buff, buff_size, "%u:%02u:%02u", hours, minutes, seconds);

    }
}
BluetoothContext *bluetooth_context = bt_get_context();

void show_volume_slider() {
    lv_obj_clear_flag(objects.volume_slider_panel, LV_OBJ_FLAG_HIDDEN);
    is_volume_slider_shown = true;
}

void hide_volume_slider() 
{
    lv_obj_add_flag(objects.volume_slider_panel, LV_OBJ_FLAG_HIDDEN);
    is_volume_slider_shown = false;

}void update_metadata_display()
{
    BluetoothContext *bluetooth_context = bt_get_context();

    // Scroll song title
    scroll_label_text(objects.song_title_label, bluetooth_context->current_metadata.title, &song_title_scroll);

    // Scroll album title
    scroll_label_text(objects.album_title_label, bluetooth_context->current_metadata.album, &album_title_scroll);

    // Scroll artist name
    scroll_label_text(objects.artist_name_label, bluetooth_context->current_metadata.artist, &artist_name_scroll);

    // Update progress slider
    lv_slider_set_value(objects.music_progress_slider, ((float)bluetooth_context->current_metadata.current_play_pos / bluetooth_context->current_metadata.playing_time) * 100, LV_ANIM_ON);

    // Update time display
    char start_pos[20];
    char end_pos[20];

    format_time_display(start_pos, bluetooth_context->current_metadata.current_play_pos, 20);
    format_time_display(end_pos, bluetooth_context->current_metadata.playing_time, 20);

    lv_label_set_text(objects.starting_pos_label, start_pos);
    lv_label_set_text(objects.end_pos_label, end_pos);
}
void loop()
{
    if (bt_get_connection_status())
    {
        if (!bt_is_init)
        {
            show_bt_connect_msgbox();
            lv_timer_create(hide_bt_connect_msgbox, 8000, NULL);
            lv_label_set_text(objects.bt_connected_label, "Bluetooth device connected.");
            bt_is_init = true;
        }
    }
    else
    {
        lv_label_set_text(objects.bt_connected_label, "Bluetooth device disconnected. Please connect your phone.");
        bt_is_init = false;
    }

    uint16_t volume = volumeControl.getVolumePercentage();

    if (volumeControl.isVolumeChanged())
    {

        if(!is_volume_slider_shown) show_volume_slider();
       // Serial.println(volume);
        char volume_label_text[20];
        snprintf(volume_label_text, 20, "Volume: %u%%", volume);
        lv_label_set_text(objects.volume_label, volume_label_text);
        lv_slider_set_value(objects.volume_slider, volume, LV_ANIM_ON);
        bluetooth_context->is_volume_change = false;
    } else {
        hide_volume_slider();
    }

    update_metadata_display();

    // Handle LVGL tasks
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);
}