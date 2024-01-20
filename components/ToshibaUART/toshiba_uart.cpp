#include "esphome/core/log.h"
#include "toshiba_uart.h"

namespace esphome {
namespace toshiba_uart {

static const char *TAG = "toshiba";

int i = 1;
int msg_len = 0;
uint8_t prev_c = 0;
uint8_t c_now = 0;
uint8_t msg [20];
uint8_t msg_start [3];

uint8_t msg_from;
uint8_t msg_to;

bool status_msg = false;

int zone1_water_temp_prev = 0;
int hotwater_temp_prev = 0;
int zone1_water_temp = 0;
int hotwater_temp = 0;

int wanted_zone1_water_temp = 0;
int wanted_hotwater_water_temp = 0;

int some_temp_1_prev = 0;
int some_temp_1 = 0;
int some_temp_2_prev = 0;
int some_temp_2 = 0;
int some_temp_3_prev = 0;
int some_temp_3 = 0;

bool pump_onoff;
bool pump_state_known = false;
bool auto_mode_onoff;

bool zone1_pumpin;
bool heat_resistor_heating;
bool zone1_active;
bool zone1_active_prev;

bool hotwater_pumpin;
bool hotwater_resistor_heating;
bool hotwater_active;
bool hotwater_active_prev;

bool cooling_mode;
bool heating_mode;

void ToshibaUART::setup() {

}



void ToshibaUART::set_zone1_state(bool state) {
  if (pump_state_known && zone1_active != state){
    if(state){
      this->write_array(INST_ZONE1_ON,sizeof(INST_ZONE1_ON));
    }
    else{
      this->write_array(INST_ZONE1_OFF,sizeof(INST_ZONE1_OFF));
    }
    this->flush();
    pump_state_known = false;
  }
  else if ( zone1_active == state ){
    this->zone1_switch_switch_->publish_state(zone1_active);
  }
}

void ToshibaUART::set_hotwater_state(bool state) {
  if (pump_state_known && hotwater_active != state){
    if(state){
      this->write_array(INST_HOTWATER_ON,sizeof(INST_HOTWATER_ON));
    }
    else{
      this->write_array(INST_HOTWATER_OFF,sizeof(INST_HOTWATER_OFF));
    }
    this->flush();
    pump_state_known = false;
  }
  else if ( hotwater_active == state ){
    this->hotwater_switch_switch_->publish_state(hotwater_active);
  }

}

void ToshibaUART::set_zone1_target_temp(float value) {
  if (zone1_active) {
    uint8_t temp_target_value = (22 + 16) * 2;
    if (value >= 22){
      temp_target_value = (value + 16) * 2;
    }    
    INST_SET_ZONE1_TEMP[9] = temp_target_value;
    INST_SET_ZONE1_TEMP[11] = (hotwater_temp + 16) * 2;
    INST_SET_ZONE1_TEMP[12] = temp_target_value;
    INST_SET_ZONE1_TEMP[13] = return_checksum(INST_SET_ZONE1_TEMP,sizeof(INST_SET_ZONE1_TEMP)); // second last, checksum
    
    this->write_array(INST_SET_ZONE1_TEMP,sizeof(INST_SET_ZONE1_TEMP));
    this->flush();
    pump_state_known = false;
    wanted_zone1_water_temp = 0;
  }
  else{
    wanted_zone1_water_temp = value;
  }
  
}

void ToshibaUART::set_hotwater_target_temp(float value) {
  if (hotwater_active) {
    INST_SET_HOTWATER_TEMP[11] = (value + 16) * 2;
    INST_SET_HOTWATER_TEMP[13] = return_checksum(INST_SET_HOTWATER_TEMP,sizeof(INST_SET_HOTWATER_TEMP)); // second last, checksum
    
    this->write_array(INST_SET_HOTWATER_TEMP,sizeof(INST_SET_HOTWATER_TEMP));
    this->flush();
    pump_state_known = false;
    wanted_hotwater_water_temp = 0;
  }
  else{ // Handle if hotwater was not active, the pump would go berserk if values were written without it running
    wanted_hotwater_water_temp = value;
  }
}

uint8_t ToshibaUART::return_checksum(uint8_t msg[], int len) {
  uint8_t Checksum = 0;
  for (int i = 2; i < (len-2); i++ ){
    Checksum = Checksum + (msg[i] % 265);
  }
  return Checksum;
}

void ToshibaUART::set_cooling_mode(uint8_t value) {
  
}

void ToshibaUART::publish_states() {
#ifdef USE_SWITCH
  if (this->zone1_switch_switch_) {
    this->zone1_switch_switch_->publish_state(zone1_active);
  }
  if (this->hotwater_switch_switch_) {
    this->hotwater_switch_switch_->publish_state(hotwater_active);
  }
#endif

#ifdef USE_BINARY_SENSOR
  if (this->pump_onoff_binary_sensor_) {
    this->pump_onoff_binary_sensor_->publish_state(pump_onoff);
  }
  if (this->heat_pump_heating_binary_sensor_) {
    this->heat_pump_heating_binary_sensor_->publish_state(zone1_pumpin);
  }
  if (this->heat_resistor_heating_binary_sensor_) {
    this->heat_resistor_heating_binary_sensor_->publish_state(heat_resistor_heating);
  }
  if (this->heat_pump_onoff_binary_sensor_) {
    this->heat_pump_onoff_binary_sensor_->publish_state(zone1_active);
  }
  if (this->hotwater_pump_heating_binary_sensor_) {
    this->hotwater_pump_heating_binary_sensor_->publish_state(hotwater_pumpin);
  }
  if (this->hotwater_resistor_heating_binary_sensor_) {
    this->hotwater_resistor_heating_binary_sensor_->publish_state(hotwater_resistor_heating);
  }
  if (this->hotwater_pump_onoff_binary_sensor_) {
    this->hotwater_pump_onoff_binary_sensor_->publish_state(hotwater_active);
  }
#endif

#ifdef USE_SENSOR
  if (this->heating_target_temp_sensor_ && (zone1_water_temp != zone1_water_temp_prev)) {
    this->heating_target_temp_sensor_->publish_state(zone1_water_temp);
  }
  if (this->hotwater_target_temp_sensor_ && (hotwater_temp != hotwater_temp_prev)) {
    this->hotwater_target_temp_sensor_->publish_state(hotwater_temp);
  }
#endif

#ifdef USE_NUMBER
  if ((this->zone1_target_temp_number_ && zone1_water_temp != zone1_water_temp_prev)) {
    this->zone1_target_temp_number_->publish_state(zone1_water_temp);
  }
  if ((this->hotwater_target_temp_number_ && hotwater_temp != hotwater_temp_prev)) {
    this->hotwater_target_temp_number_->publish_state(hotwater_temp);
  }
#endif
}

void ToshibaUART::loop() {
  status_msg = false;
  while (available()) {
    read_array(msg_start,3);
    if (msg_start[0] == 0xF0 && msg_start[1] == 0xF0){
      msg_len = msg_start[2];
      read_array(msg,msg_len-3);
      msg_from = msg[0];
      msg_to = msg[1];
      // ESP_LOGD(TAG,"%02x %02x %02x",msg_start[0],msg_start[1],msg_start[2]);
      // ESP_LOGD(TAG,"msg len: %d msg from: %02x" ,msg_len,msg_from);
      if ((msg_from == MSG_ID_PUMP) && (msg[4] == 0x31) ) { // This is status message from pump
        pump_onoff                = msg[5] & (1 << 0);
        pump_state_known    = true;
        hotwater_active_prev      = hotwater_active;
        hotwater_active           = msg[5] & (1 << 1);
        auto_mode_onoff           = msg[6] & (1 << 2);
        heat_resistor_heating     = msg[7] & (1 << 0);
        zone1_pumpin              = msg[7] & (1 << 1);
        hotwater_resistor_heating = msg[7] & (1 << 2);
        hotwater_pumpin           = msg[7] & (1 << 3);
        zone1_active_prev         = zone1_active;
        zone1_active              = msg[7] & (1 << 4);
        
        cooling_mode              = msg[5] & (1 << 5);
        heating_mode              = msg[5] & (1 << 6);

        hotwater_temp_prev = hotwater_temp;
        hotwater_temp = ((msg[8])/2-16);

        zone1_water_temp_prev = zone1_water_temp;
        zone1_water_temp = ((msg[9])/2-16);

        // ESP_LOGD(TAG,"msg 4: %02x" ,msg[4]);
        // ESP_LOGD(TAG,"pump %d Hot %d pumpin %d res %d auto %d", pump_onoff, hotwater_active,hotwater_pumpin,hotwater_resistor_heating,auto_mode_onoff);

        // ESP_LOGD(TAG,"Heat %d pumpin %d res %d",zone1_active,zone1_pumpin,heat_resistor_heating);

        publish_states();
      }
    }

  // status_msg = false;
  // while (available()) {
  //   prev_c = c_now;
  //   read_array(&c_now);
  //   if (c_now == 0xF0 && prev_c == 0xF0){
  //     i=2;
  //     status_msg = false;
  //   }

//     if( i == 3 ){
//       msg_len = c_now;
//     }
//     else if ( (i == 7 && c_now == 0xA0) || (i == 8 && c_now == 0x31 && (prev_c & 0b1111) == 0) ) {
//       status_msg = true;
//     }
//     else if ( i == 9 && status_msg && (c_now & 1) ) {
//       pump_onoff = (c_now & 1);
//       pump_state_known = true;
// #ifdef USE_SWITCH
//       if (this->zone1_switch_switch_) {
//         this->zone1_switch_switch_->publish_state(pump_onoff);
//       }
// #endif
//       hotwater_active = (c_now & (1 << 1));
//     }
//     else if ( i == 10 && status_msg ) {
//       auto_mode_onoff = (c_now & (1 << 2));

//       ESP_LOGD(TAG,"pump %d Hot %d pumpin %d res %d auto %d", pump_onoff, hotwater_active,hotwater_pumpin,hotwater_resistor_heating,auto_mode_onoff);
//     }
//     else if ( i == 11 && status_msg ) {
//       heat_resistor_heating = (c_now & (1));
//       zone1_pumpin = (c_now & (1 << 1));
//       hotwater_resistor_heating = (c_now & (1 << 2));
//       hotwater_pumpin = (c_now & (1 << 3));
      
//       zone1_active = (c_now & (1 << 4));
//       ESP_LOGD(TAG,"Heat %d pumpin %d res %d",zone1_active,zone1_pumpin,heat_resistor_heating);
// #ifdef USE_BINARY_SENSOR
//       if (this->pump_onoff_binary_sensor_) {
//         this->pump_onoff_binary_sensor_->publish_state(pump_onoff);
//       }
//       if (this->zone1_pumpin_binary_sensor_) {
//         this->zone1_pumpin_binary_sensor_->publish_state(zone1_pumpin);
//       }
//       if (this->heat_resistor_heating_binary_sensor_) {
//         this->heat_resistor_heating_binary_sensor_->publish_state(heat_resistor_heating);
//       }
//       if (this->heat_pump_onoff_binary_sensor_) {
//         this->heat_pump_onoff_binary_sensor_->publish_state(zone1_active);
//       }
//       if (this->hotwater_pump_heating_binary_sensor_) {
//         this->hotwater_pump_heating_binary_sensor_->publish_state(hotwater_pumpin);
//       }
//       if (this->hotwater_resistor_heating_binary_sensor_) {
//         this->hotwater_resistor_heating_binary_sensor_->publish_state(hotwater_resistor_heating);
//       }
//       if (this->hotwater_pump_onoff_binary_sensor_) {
//         this->hotwater_pump_onoff_binary_sensor_->publish_state(hotwater_active);
//       }
// #endif
//     }
//     else if ( i == 12 && status_msg ) {
//       hotwater_temp_prev = hotwater_temp;
//       hotwater_temp = ((c_now)/2-16);
//     }
//     else if ( i == 13 && status_msg ) {
//       zone1_water_temp_prev = zone1_water_temp;
//       zone1_water_temp = ((c_now)/2-16);
// #ifdef USE_SENSOR
//     if (this->heating_target_temp_sensor_ && (zone1_water_temp != zone1_water_temp_prev)) {
//       this->heating_target_temp_sensor_->publish_state(zone1_water_temp);
//     }
//     if (this->hotwater_target_temp_sensor_ && (hotwater_temp != hotwater_temp_prev)) {
//       this->hotwater_target_temp_sensor_->publish_state(hotwater_temp);
//     }
// #endif
//     }
    // else if  ( i == 14 && status_msg ) {
    //   some_temp_1_prev = some_temp_1;
    //   some_temp_1 = ((c_now)/2-16);
    // }
    // }else if  ( i == 15 && status_msg ) {
    //   some_temp_2_prev = some_temp_2;
    //   some_temp_2 = ((c_now)/2-16);
    // }
    // }else if  ( i == 16 && status_msg ) {
    //   some_temp_3_prev = some_temp_3;
    //   some_temp_3 = ((c_now)/2-16);
    // }
    
    // i++;
    
  }
  if (!zone1_active_prev && zone1_active && wanted_zone1_water_temp){
    zone1_active_prev = true;
    set_zone1_target_temp(wanted_zone1_water_temp);
  }
  if (!hotwater_active_prev && hotwater_active && wanted_hotwater_water_temp){
    hotwater_active_prev = true;
    set_hotwater_target_temp(wanted_hotwater_water_temp);
  }

}

void ToshibaUART::dump_config(){
    ESP_LOGCONFIG(TAG, "Toshiba UART component");
    this->check_uart_settings(2400,1,esphome::uart::UART_CONFIG_PARITY_NONE,8);
}

}  // namespace toshiba_uart
}  // namespace esphome