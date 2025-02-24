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
#include <AudioTools.h>
#include <BluetoothA2DP.h>




static void data_received_callback() {
  Serial.println("Data packet received");
}

void bt_connection_broadcast()
{
    BluetoothA2DPSink a2dp_sink; 
    a2dp_sink.set_on_data_received(data_received_callback);

    a2dp_sink.start("Car Thingy.");
}
