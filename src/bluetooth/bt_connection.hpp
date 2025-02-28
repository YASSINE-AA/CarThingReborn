#ifndef BT_CONNECTION_HPP
#define BT_CONNECTION_HPP

#include <AudioTools.h>
#include <BluetoothA2DPSink.h>
#include <cstddef>

constexpr size_t METADATA_STRING_LENGTH = 64;
constexpr size_t CONNECTED_DEVICE_NAME_LENGTH = 64;

struct BluetoothSongMetadata {
    char title[METADATA_STRING_LENGTH];
    char album[METADATA_STRING_LENGTH];
    char artist[METADATA_STRING_LENGTH];
    uint32_t playing_time;
    uint32_t current_play_pos;
};

struct BluetoothContext {
    BluetoothSongMetadata current_metadata;
    char connected_device_name[CONNECTED_DEVICE_NAME_LENGTH];
    uint8_t current_volume;
    bool is_volume_change;
};

class BluetoothConnection {
public:
    BluetoothConnection();
    void init();
    BluetoothContext* getContext();
    bool isConnected();
    void setVolume(uint8_t volume);

private:
    AnalogAudioStream out;
    BluetoothA2DPSink a2dp_sink;
    static BluetoothContext bt_ctx;

    static void avrc_metadata_callback(uint8_t id, const uint8_t *text);
    static void avrc_rn_play_pos_callback(uint32_t play_pos);
    static void avrc_rn_playstatus_callback(esp_avrc_playback_stat_t playback);
    static void avrc_rn_track_change_callback(uint8_t *id);
    static void avrc_rn_volumechange_callback(int value);
};

#endif // BT_CONNECTION_HPP