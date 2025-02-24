#ifndef BT_CONNECTION_HPP
#define BT_CONNECTION_HPP
#include <AudioTools.h>
#include <BluetoothA2DPSink.h>
#include <cstddef>


constexpr size_t METADATA_STRING_LENGTH = 64;
constexpr size_t CONNECTED_DEVICE_NAME_LENGTH = 64;

struct BluetoothSongMetadata
{
    char title[METADATA_STRING_LENGTH];
    char album[METADATA_STRING_LENGTH];
    char artist[METADATA_STRING_LENGTH];
    uint32_t playing_time;
    uint32_t current_play_pos;
};

typedef struct
{
    BluetoothSongMetadata current_metadata;
    char connected_device_name[CONNECTED_DEVICE_NAME_LENGTH];
    uint8_t current_volume;
} BluetoothContext;

void bt_connection_broadcast();

BluetoothContext *bt_get_context();

bool bt_get_next_mc();

bool bt_get_connection_status();

#endif