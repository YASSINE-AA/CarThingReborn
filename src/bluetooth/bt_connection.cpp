/*
 Copyright 2025 Yassine Ahmed Ali

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "bt_connection.hpp"

AnalogAudioStream out;
BluetoothA2DPSink a2dp_sink(out);

static BluetoothContext bt_ctx = {0};

static void data_received_callback()
{
    // Serial.println("Data packet received");
}

void read_data_stream(const uint8_t *data, uint32_t length)
{
    const int16_t *samples = reinterpret_cast<const int16_t *>(data);
    uint32_t sample_count = length / 2;
}



void avrc_metadata_callback(uint8_t id, const uint8_t *text)
{
    switch (id)
    {
    case ESP_AVRC_MD_ATTR_ARTIST:
        
        strlcpy(bt_ctx.current_metadata.artist, reinterpret_cast<const char *>(text), METADATA_STRING_LENGTH);
        break;

    case ESP_AVRC_MD_ATTR_ALBUM:
        strlcpy(bt_ctx.current_metadata.album, reinterpret_cast<const char *>(text), METADATA_STRING_LENGTH);
        break;

    case ESP_AVRC_MD_ATTR_TITLE:
        strlcpy(bt_ctx.current_metadata.title, reinterpret_cast<const char *>(text), METADATA_STRING_LENGTH);
        break;

    case ESP_AVRC_MD_ATTR_PLAYING_TIME:
        bt_ctx.current_metadata.playing_time = static_cast<uint32_t>(round(String(reinterpret_cast<const char *>(text)).toInt() / 1000.0));
        break;

    default:
        Serial.printf("unknown");
        break;
    }
}
void avrc_rn_play_pos_callback(uint32_t play_pos)
{
    bt_ctx.current_metadata.current_play_pos = (int)round(play_pos / 1000.0);
    Serial.println(bt_ctx.current_metadata.current_play_pos);
}

void avrc_rn_playstatus_callback(esp_avrc_playback_stat_t playback)
{
    switch (playback)
    {
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_STOPPED:
        Serial.println("Stopped.");
        break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_PLAYING:
        Serial.println("Playing.");
        break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_PAUSED:
        Serial.println("Paused.");
        break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_FWD_SEEK:
        Serial.println("Forward seek.");
        break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_REV_SEEK:
        Serial.println("Reverse seek.");
        break;
    case esp_avrc_playback_stat_t::ESP_AVRC_PLAYBACK_ERROR:
        Serial.println("Error.");
        break;
    default:
        Serial.printf("Got unknown playback status %d\n", playback);
    }
}

BluetoothContext *bt_get_context()
{
    return &bt_ctx;
}

bool bt_get_next_mc()
{

    return false;
}

bool bt_get_connection_status()

{
    return a2dp_sink.is_connected();
}

void avrc_rn_track_change_callback(uint8_t *id)
{
    Serial.println("Track Change bits:");
    for (uint8_t i = 0; i < 8; i++)
    {
        Serial.printf("\tByte %d : 0x%x \n", i, id[i]);
    }
    uint8_t track_change_flag = *id;
    Serial.printf("\tFlag value: %d\n", track_change_flag);
}

void avrc_rn_volumechange_callback(int value)
{
    const uint8_t max_value = 127;
    bt_ctx.current_volume = (uint8_t) (((float)value / max_value) * 100);
   
   bt_ctx.is_volume_change = true;
}

void bt_set_volume()
{
    a2dp_sink.set_volume(43);
    a2dp_sink.fast_forward();
}

void bt_connection_broadcast()
{
    bt_ctx.is_volume_change = false;
   // a2dp_sink.set_on_data_received(data_received_callback);
    //2dp_sink.set_stream_reader(read_data_stream);
    a2dp_sink.set_avrc_metadata_attribute_mask(ESP_AVRC_MD_ATTR_TITLE | ESP_AVRC_MD_ATTR_ARTIST | ESP_AVRC_MD_ATTR_ALBUM | ESP_AVRC_MD_ATTR_PLAYING_TIME);
    a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
    a2dp_sink.set_avrc_rn_playstatus_callback(avrc_rn_playstatus_callback);
    a2dp_sink.set_avrc_rn_volumechange(avrc_rn_volumechange_callback);
    a2dp_sink.set_avrc_rn_play_pos_callback(avrc_rn_play_pos_callback);
    a2dp_sink.set_avrc_rn_track_change_callback(avrc_rn_track_change_callback);
    a2dp_sink.start("Car Thingy");
}