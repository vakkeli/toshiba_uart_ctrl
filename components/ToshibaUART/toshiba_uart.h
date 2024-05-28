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

const uint8_t  INST_ZONE1_ON[11]      = {0xF0, 0xF0, 0x0B, 0x60, 0x70, 0xE0, 0x01, 0x21, 0x03, 0xE0, 0xA0};
const uint8_t  INST_ZONE1_OFF[11]     = {0xF0, 0xF0, 0x0B, 0x60, 0x70, 0xE0, 0x01, 0x21, 0x0A, 0xE7, 0xA0}; 
const uint8_t  INST_HOTWATER_ON[11]   = {0xF0, 0xF0, 0x0B, 0x60, 0x70, 0xE0, 0x01, 0x21, 0x0C, 0xE9, 0xA0};
const uint8_t  INST_HOTWATER_OFF[11]  = {0xF0, 0xF0, 0x0B, 0x60, 0x70, 0xE0, 0x01, 0x21, 0x08, 0xE5, 0xA0}; 
const uint8_t  INST_AUTO_ON[12]       = {0xF0, 0xF0, 0x0C, 0x60, 0x70, 0xE0, 0x01, 0x24, 0x01, 0x01, 0xE3, 0xA0};
const uint8_t  INST_AUTO_OFF[12]      = {0xF0, 0xF0, 0x0C, 0x60, 0x70, 0xE0, 0x01, 0x24, 0x01, 0x00, 0xE2, 0xA0};


// const uint8_t CODE_CTRL_TEMP_HW = 0x00;   //Control temperature (Hot water cylinder)  
// const uint8_t CODE_CTRL_TEMP_ZONE1 = 0x01;   //Control temperature (Zone1)  
// const uint8_t CODE_CTRL_TEMP_ZONE2 = 0x02;   //Control temperature (Zone2)  
const uint8_t CODE_HEADER_AMBIENT_TEMP = 0x03;   //Remote controller sensor temperature     ORDER NUMBER = 00
const uint8_t CODE_CONDENSED_TEMP = 0x04;   //Condensed temperature (TC)      ORDER NUMBER = 01
const uint8_t CODE_INLET_TEMP  = 0x06;   //Water inlet temperature (TWI)    ORDER NUMBER = 02
const uint8_t CODE_OUTLET_TEMP  = 0x07;   //Water outlet temperature (TWO)      ORDER NUMBER = 03
const uint8_t CODE_HEATER_OUTLET_TEMP  = 0x08;   //Water heater outlet temperature (THO)    ORDER NUMBER = 04
//const uint8_t CODE_FLOOR_INLET_TEMP = 0x09;   //Floor inlet temperature (TFI)  
const uint8_t CODE_HW_CYLINDER_TEMP = 0x0A;   //Hot water cylinder temperature (TTW)      ORDER NUMBER = 05
const uint8_t CODE_MIXING_VALVE = 0x0B;   //Mixing valve position     ORDER NUMBER = 06
const uint8_t CODE_LOW_PRESSURE = 0x0E;   //Low pressure (Ps) × 1/10      ORDER NUMBER = 07

const uint8_t CODE_HEAT_EXCHANGE_TEMPERATURE = 0x60;   //Heat exchange temperature (TE)     ORDER NUMBER = 08
const uint8_t CODE_OUTSIDE_AIR_TEMPERATURE = 0x61;   //Outside air temperature (TO)       ORDER NUMBER = 09
const uint8_t CODE_DISCHARGE_TEMPERATURE = 0x62;   //Discharge temperature (TD)     ORDER NUMBER =  10
const uint8_t CODE_SUCTION_TEMPERATURE = 0x63;   //Suction temperature (TS)       ORDER NUMBER =  11
const uint8_t CODE_HEAT_SINK_TEMPERATURE = 0x65;   //Heat sink temperature (THS)        ORDER NUMBER =  12
const uint8_t CODE_OUTDOOR_UNIT_CURRENT = 0x6A;   //Current × 10      ORDER NUMBER =  13
const uint8_t CODE_HEAT_EXCHANGER_OIL_TEMPERATURE = 0x6D;   //Heat exchanger coil temperature (TL)      ORDER NUMBER =  14
const uint8_t CODE_COMPRESSOR_FREQ = 0x70;   //Compressor operation Hz        ORDER NUMBER =  15
const uint8_t CODE_FAN_RPM = 0x72;   //Number of revolutions of outdoor fan       ORDER NUMBER =  16
const uint8_t CODE_OUTDOOR_PMV = 0x74;   //Outdoor PMV position × 1/10       ORDER NUMBER =  17
const uint8_t CODE_DISCHARGE_PRESSURE = 0x7A;   //Discharge pressure (PD) × 1/10      ORDER NUMBER =  18

const uint8_t CODE_MICRO_COMPUTER_ENERGIZED_UPTIME   = 0xF0;   //Micro computer energized accumulation   (time × 1/100)     ORDER NUMBER =  19
const uint8_t CODE_HW_COMPRESSOR_UPTIME   = 0xF1;   //Hot water compressor ON accumulation    (time × 1/100)      ORDER NUMBER =  20
const uint8_t CODE_COOLING_COMPRESSOR_UPTIME  = 0xF2;   //Cooling compressor ON accumulation  (time × 1/100)      ORDER NUMBER =  21
const uint8_t CODE_HEATING_COMPRESSOR_UPTIME  = 0xF3;   //Heating compressor ON accumulation  (time × 1/100)      ORDER NUMBER =  22
const uint8_t CODE_AC_PUMP_UPTIME = 0xF4;   //Built-in AC pump operation accumulation (time × 1/100)      ORDER NUMBER =  23
const uint8_t CODE_HW_CYLINDER_HEATER_OPERATION_UPTIME = 0xF5;   //Hot water cylinder heater operation accumulation (time × 1/100)    ORDER NUMBER =  24
const uint8_t CODE_BACKUP_HEATER_OPERATION_UPTIME = 0xF6;   //Backup heater operation accumulation (time × 1/100)     ORDER NUMBER =  25
const uint8_t CODE_BOOSTER_HEATER_OPERATION_UPTIME = 0xF7;   //Booster heater operation accumulation (time × 1/100)       ORDER NUMBER =  26

const uint8_t CODE_REQUEST_DATA[26] = {0x03,0x04,0x06,0x07,0x08,0x0A,0x0B,0x0E,0x60,0x61,0x62,0x63,0x65,0x6A,0x6D,0x70,0x72,0x7A,0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7};


#define MSG_ID_ME = MSG_ID_HEADER_REMOTE

class ToshibaUART : public uart::UARTDevice, public PollingComponent {
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
    SUB_SENSOR(zone1_water_temp)
    SUB_SENSOR(header_ambient_temp)
    SUB_SENSOR(condensed_temp)
    SUB_SENSOR(inlet_temp)
    SUB_SENSOR(outlet_temp)
    SUB_SENSOR(heater_outlet_temp)
    SUB_SENSOR(hw_cylinder_temp)
    SUB_SENSOR(mixing_valve)
    SUB_SENSOR(low_pressure)
    SUB_SENSOR(heat_exchange_temp)
    SUB_SENSOR(outside_air_temp)
    SUB_SENSOR(discharge_temp)
    SUB_SENSOR(suction_temp)
    SUB_SENSOR(heat_sink_temp)
    SUB_SENSOR(oudoor_unit_current)
    SUB_SENSOR(heat_exchanger_oil_temp)
    SUB_SENSOR(compressor_freq)
    SUB_SENSOR(fan_rpm)
    SUB_SENSOR(outdoor_pmv)
    SUB_SENSOR(discharge_pressure)
    SUB_SENSOR(micro_computer_energized_uptime)
    SUB_SENSOR(hw_compressor_uptime)
    SUB_SENSOR(cooling_compressor_uptime)
    SUB_SENSOR(heating_compressor_uptime)
    SUB_SENSOR(ac_pump_uptime)
    SUB_SENSOR(hw_cylinder_heater_operation_uptime)
    SUB_SENSOR(backup_heater_operation_uptime)
    SUB_SENSOR(booster_heater_operation_uptime)
    //SUB_SENSOR(hotwater_target_temp)
  #endif
  
  #ifdef USE_SWITCH
    SUB_SWITCH(zone1_switch)
    SUB_SWITCH(hotwater_switch)
    SUB_SWITCH(auto_mode_switch)
  #endif
  
  #ifdef USE_NUMBER
    SUB_NUMBER(zone1_target_temp)
    SUB_NUMBER(hotwater_target_temp)
  #endif

    void setup() override;
    void loop() override;
    void update() override;
    void dump_config() override;

    void publish_states() ;
    void set_zone1_target_temp(float value);
    void set_hotwater_target_temp(float value);
    uint8_t return_checksum(uint8_t msg[], int len);
    void set_cooling_mode(bool state); //WIP
    void set_auto_mode(bool state);
    void set_zone1_state(bool state);
    void set_hotwater_state(bool state);
    void request_data(uint8_t request_code);
    void publish_sensor(int sensor_index, int16_t value);

    uint8_t  INST_SET_ZONE1_TEMP[15]    = {0xF0, 0xF0, 0x0F, 0x60, 0x70, 0xE0, 0x01, 0x23, 0x02, 0x6E, 0x66, 0xA2, 0x6E, 0xC9, 0xA0};
    uint8_t  INST_SET_HOTWATER_TEMP[15] = {0xF0, 0xF0, 0x0F, 0x60, 0x70, 0xE0, 0x01, 0x23, 0x08, 0x00, 0x00, 0xA0, 0x00, 0x8B, 0xA0};
    uint8_t  INST_REQUEST_DATA[12]       = {0xF0, 0xF0, 0x0C, 0x60, 0x70, 0xE0, 0x41, 0x5C, 0x70, 0x00, 0x8B, 0xA0};
};


}  // namespace toshiba_uart
}  // namespace esphome