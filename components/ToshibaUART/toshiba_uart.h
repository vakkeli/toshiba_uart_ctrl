#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/defines.h"
#ifdef USE_BINARY_SENSOR
#include "esphome/components/binary_sensor/binary_sensor.h"
#endif
#ifdef USE_SENSOR
#include "esphome/components/sensor/sensor.h"
#endif
#ifdef USE_SWITCH
#include "esphome/components/switch/switch.h"
#endif
#ifdef USE_NUMBER
#include "esphome/components/number/number.h"
#endif


namespace esphome {
namespace toshiba_uart {

const uint8_t  MSG_STRUCT_START[2] = {0xF0, 0xF0};
const uint8_t  MSG_STRUCT_END      = 0xA0;

const uint8_t  MSG_ID_HEADER_REMOTE = 0x60;
const uint8_t  MSG_ID_SECONDARY_REMOTE = 0x61;
const uint8_t  MSG_ID_PUMP = 0x70;
const uint8_t  MSG_ID_BROADCAST = 0xFF;

const uint8_t  INST_ZONE1_ON[11]   = {0xF0, 0xF0, 0x0B, 0x60, 0x70, 0xE0, 0x01, 0x21, 0x03, 0xE0, 0xA0};
const uint8_t  INST_ZONE1_OFF[11]  = {0xF0, 0xF0, 0x0B, 0x60, 0x70, 0xE0, 0x01, 0x21, 0x0A, 0xE7, 0xA0}; 
const uint8_t  INST_HOTWATER_ON[11]   = {0xF0, 0xF0, 0x0B, 0x60, 0x70, 0xE0, 0x01, 0x21, 0x0C, 0xE9, 0xA0};
const uint8_t  INST_HOTWATER_OFF[11]  = {0xF0, 0xF0, 0x0B, 0x60, 0x70, 0xE0, 0x01, 0x21, 0x08, 0xE5, 0xA0}; 

#define MSG_ID_ME = MSG_ID_HEADER_REMOTE

class ToshibaUART : public uart::UARTDevice, public Component {
  public:

  #ifdef USE_BINARY_SENSOR
    SUB_BINARY_SENSOR(pump_onoff)
    SUB_BINARY_SENSOR(heat_pump_heating)
    SUB_BINARY_SENSOR(heat_resistor_heating)
    SUB_BINARY_SENSOR(heat_pump_onoff)
    SUB_BINARY_SENSOR(hotwater_pump_heating)
    SUB_BINARY_SENSOR(hotwater_resistor_heating)
    SUB_BINARY_SENSOR(hotwater_pump_onoff)
  #endif

  #ifdef USE_SENSOR
    SUB_SENSOR(heating_target_temp)
    SUB_SENSOR(hotwater_target_temp)
  #endif
  
  #ifdef USE_SWITCH
    SUB_SWITCH(zone1_switch)
    SUB_SWITCH(hotwater_switch)
  #endif
  
  #ifdef USE_NUMBER
    SUB_NUMBER(zone1_target_temp)
    SUB_NUMBER(hotwater_target_temp)
  #endif

    void setup() override;
    void loop() override;
    void dump_config() override;

    void publish_states() ;
    void set_zone1_target_temp(float value);
    void set_hotwater_target_temp(float value);
    uint8_t return_checksum(uint8_t msg[], int len);
    void set_cooling_mode(uint8_t value);
    void set_zone1_state(bool state);
    void set_hotwater_state(bool state);


    uint8_t  INST_SET_ZONE1_TEMP[15]    = {0xF0, 0xF0, 0x0F, 0x60, 0x70, 0xE0, 0x01, 0x23, 0x02, 0x6E, 0x66, 0xA2, 0x6E, 0xC9, 0xA0};
    uint8_t  INST_SET_HOTWATER_TEMP[15] = {0xF0, 0xF0, 0x0F, 0x60, 0x70, 0xE0, 0x01, 0x23, 0x08, 0x00, 0x00, 0xA0, 0x00, 0x8B, 0xA0};
};


}  // namespace toshiba_uart
}  // namespace esphome