/*Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  */

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <UI/ui.h>

// ============= BLUETOOTH ============== //
#include <bluetooth/bt_connection.hpp>

/*To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 *You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 Note that the `lv_examples` library is for LVGL v7 and you shouldn't install it for this version (since LVGL v8)
 as the examples and demos are now part of the main LVGL library. */

/*Change to your screen resolution*/
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

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
}
void show_boot_message(lv_timer_t *timer)
{
    int msg_index = lv_rand(0, sizeof(boot_msgs) / sizeof(boot_msgs[0]) - 1);
    lv_label_set_text(objects.bootup_label, boot_msgs[msg_index]);
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

    lv_tabview_set_act(objects.tabview, 0, LV_ANIM_ON);

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
    // /if (bt_get_next_mc())
    // {
    lv_label_set_text(objects.song_title_label, bluetooth_context->current_metadata.title);
    lv_label_set_text(objects.album_title_label, bluetooth_context->current_metadata.album);
    lv_label_set_text(objects.artist_name_label, bluetooth_context->current_metadata.artist);
    lv_slider_set_value(objects.music_progress_slider, ((float)bluetooth_context->current_metadata.current_play_pos / bluetooth_context->current_metadata.playing_time) * 100, LV_ANIM_ON);

    char start_pos[20];
    char end_pos[20];

    format_time_display(start_pos, bluetooth_context->current_metadata.current_play_pos, 20);
    format_time_display(end_pos, bluetooth_context->current_metadata.playing_time, 20);

    lv_label_set_text(objects.starting_pos_label, start_pos);
    lv_label_set_text(objects.end_pos_label, end_pos);

    //  Serial.println((bluetooth_context->current_metadata.playing_time/bluetooth_context->current_metadata.playing_time) * 100);

    // }
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);
}
