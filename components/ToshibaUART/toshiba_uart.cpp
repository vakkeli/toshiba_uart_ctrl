#include "esphome/core/log.h"
#include "toshiba_uart.h"
#include <vector>

namespace esphome {
namespace toshiba_uart {

std::vector< int > sensor_arr;
int current_sensor = 0;
int sensor_count = 0;

int current_slow_sensor = 0;
int slow_sensor_count = 0;

int update_slow_sensors_counter = 0;

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

int zone1_target_temp_prev = 0;
int zone1_target_temp = 0;

int zone1_water_temp_prev = 0;
int zone1_water_temp = 0;

int hotwater_temp_prev = 0;
int hotwater_temp = 0;

int wanted_zone1_target_temp = 0;
int wanted_hotwater_water_temp = 0;

int some_temp_1_prev = 0;
int some_temp_1 = 0;
int some_temp_2_prev = 0;
int some_temp_2 = 0;
int some_temp_3_prev = 0;
int some_temp_3 = 0;

bool pump_state_known = false;
bool auto_mode_active;

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


bool query_data = false;

void ToshibaUART::setup() {
  if (this->header_ambient_temp_sensor_){
    sensor_arr.push_back(0);
    sensor_count++;
  }
  if (this->condensed_temp_sensor_){
    sensor_arr.push_back(1);
    sensor_count++;
  }
  if (this->inlet_temp_sensor_){
    sensor_arr.push_back(2);
    sensor_count++;
  }
  if (this->outlet_temp_sensor_){
    sensor_arr.push_back(3);
    sensor_count++;
  }
  if (this->heater_outlet_temp_sensor_){
    sensor_arr.push_back(4);
    sensor_count++;
  }
  if (this->hw_cylinder_temp_sensor_){
    sensor_arr.push_back(5);
    sensor_count++;
  }
  if (this->mixing_valve_sensor_){
    sensor_arr.push_back(6);
    sensor_count++;
  }
  if (this->low_pressure_sensor_){
    sensor_arr.push_back(7);
    sensor_count++;
  }
  if (this->heat_exchange_temp_sensor_){
    sensor_arr.push_back(8);
    sensor_count++;
  }
  if (this->outside_air_temp_sensor_){
    sensor_arr.push_back(9);
    sensor_count++;
  }
  if (this->discharge_temp_sensor_){
    sensor_arr.push_back(10);
    sensor_count++;
  }
  if (this->suction_temp_sensor_){
    sensor_arr.push_back(11);
    sensor_count++;
  }
  if (this->heat_sink_temp_sensor_){
    sensor_arr.push_back(12);
    sensor_count++;
  }
  if (this->oudoor_unit_current_sensor_){
    sensor_arr.push_back(13);
    sensor_count++;
  }
  if (this->heat_exchanger_oil_temp_sensor_){
    sensor_arr.push_back(14);
    sensor_count++;
  }
  if (this->compressor_freq_sensor_){
    sensor_arr.push_back(15);
    sensor_count++;
  }
  if (this->fan_rpm_sensor_){
    sensor_arr.push_back(16);
    sensor_count++;
  }
  if (this->outdoor_pmv_sensor_){
    sensor_arr.push_back(17);
    sensor_count++;
  }
  if (this->discharge_pressure_sensor_){
    sensor_arr.push_back(18);
    sensor_count++;
  }
  if (this->micro_computer_energized_uptime_sensor_){
    sensor_arr.push_back(19);
    slow_sensor_count++;
  }
  if (this->hw_compressor_uptime_sensor_){
    sensor_arr.push_back(20);
    slow_sensor_count++;
  }
  if (this->cooling_compressor_uptime_sensor_){
    sensor_arr.push_back(21);
    slow_sensor_count++;
  }
  if (this->heating_compressor_uptime_sensor_){
    sensor_arr.push_back(22);
    slow_sensor_count++;
  }
  if (this->ac_pump_uptime_sensor_){
    sensor_arr.push_back(23);
    slow_sensor_count++;
  }
  if (this->hw_cylinder_heater_operation_uptime_sensor_){
    sensor_arr.push_back(24);
    slow_sensor_count++;
  }
  if (this->backup_heater_operation_uptime_sensor_){
    sensor_arr.push_back(25);
    slow_sensor_count++;
  }
  if (this->booster_heater_operation_uptime_sensor_){
    sensor_arr.push_back(26);
    slow_sensor_count++;
  }
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


void ToshibaUART::update() {
  current_sensor ++;
  if ( update_slow_sensors_counter == 10 ){    
    if (current_sensor == slow_sensor_count + sensor_count){
      current_sensor = 0;
      update_slow_sensors_counter = 0;
    }
  } 
  else {
    update_slow_sensors_counter++;
    if (current_sensor == sensor_count){
      current_sensor = 0;
    }
  }
  request_data(CODE_REQUEST_DATA[sensor_arr[current_sensor]]);
  query_data = true;
  ESP_LOGD(TAG,"Requesting data");

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
    wanted_zone1_target_temp = 0;
  }
  else{
    wanted_zone1_target_temp = value;
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

void ToshibaUART::set_cooling_mode(bool state) {
  
}

void ToshibaUART::set_auto_mode(bool state) {
  if (pump_state_known && auto_mode_active != state){
    if(state){
      this->write_array(INST_AUTO_ON,sizeof(INST_AUTO_ON));
    }
    else{
      this->write_array(INST_AUTO_OFF,sizeof(INST_AUTO_OFF));
    }
    this->flush();
    pump_state_known = false;
  }
  else if ( auto_mode_active == state ){
    this->auto_mode_switch_switch_->publish_state(auto_mode_active);
  }
}


void ToshibaUART::request_data(uint8_t request_code) {
  INST_REQUEST_DATA[9] = request_code;
  INST_REQUEST_DATA[10] = return_checksum(INST_REQUEST_DATA,sizeof(INST_REQUEST_DATA));
  this->write_array(INST_REQUEST_DATA,sizeof(INST_REQUEST_DATA));
  this->flush();
  //ESP_LOGD(TAG,"Request = 0x%02x, current sensor = %d, chcksum = 0x%02x", INST_REQUEST_DATA[7],sensor_arr[current_sensor],temp);
}


void ToshibaUART::publish_sensor(int sensor_index, int16_t value) {
  float temp;
  switch (sensor_index)  {
    case 9:
      if (this->outside_air_temp_sensor_){
        this->outside_air_temp_sensor_->publish_state(value);
      }
      break;

    case 13:
      if (this->oudoor_unit_current_sensor_){
        temp = value / 10;
        this->oudoor_unit_current_sensor_->publish_state(temp);
      }
      break;
    case 22:
      if (this->heating_compressor_uptime_sensor_){
        this->heating_compressor_uptime_sensor_->publish_state(value * 100);
      }
      break;
    default:
      ESP_LOGD(TAG,"current sensor = %d not found",current_sensor);
        
}
}

void ToshibaUART::publish_states() {
#ifdef USE_SWITCH
  if (this->zone1_switch_switch_) {
    this->zone1_switch_switch_->publish_state(zone1_active);
  }
  if (this->hotwater_switch_switch_) {
    this->hotwater_switch_switch_->publish_state(hotwater_active);
  }
  if (this->auto_mode_switch_switch_) {
    this->auto_mode_switch_switch_->publish_state(auto_mode_active);
  }
#endif

#ifdef USE_BINARY_SENSOR
  if (this->pump_onoff_binary_sensor_) {
    this->pump_onoff_binary_sensor_->publish_state(hotwater_active | zone1_active);
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
  if (this->zone1_water_temp_sensor_ && (zone1_water_temp != zone1_water_temp_prev)) {
    this->zone1_water_temp_sensor_->publish_state(zone1_water_temp);
  }
  // if (this->hotwater_target_temp_sensor_ && (hotwater_temp != hotwater_temp_prev)) {
  //   this->hotwater_target_temp_sensor_->publish_state(hotwater_temp);
  // }
#endif

#ifdef USE_NUMBER
  if ((this->zone1_target_temp_number_ && zone1_target_temp != zone1_target_temp_prev)) {
    this->zone1_target_temp_number_->publish_state(zone1_target_temp);
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
      if ((msg_from == MSG_ID_PUMP) && (msg[4] == 0x31) ) { // This is status message from pump
        zone1_active              = msg[5] & (1);
        hotwater_active_prev      = hotwater_active;
        hotwater_active           = msg[5] & (1 << 1);
        auto_mode_active          = msg[6] & (1 << 2);
        heat_resistor_heating     = msg[7] & (1 << 0);
        zone1_pumpin              = msg[7] & (1 << 1);
        hotwater_resistor_heating = msg[7] & (1 << 2);
        hotwater_pumpin           = msg[7] & (1 << 3);
        zone1_active_prev         = zone1_active;
        zone1_active              = msg[5] & (1);
        
        cooling_mode              = msg[5] & (1 << 5);
        heating_mode              = msg[5] & (1 << 6);

        hotwater_temp_prev = hotwater_temp;
        hotwater_temp = ((msg[8])/2-16);

        zone1_target_temp_prev = zone1_target_temp;
        zone1_target_temp = ((msg[9])/2-16);

        if (msg_len > 18){ // only in longer messages
          zone1_water_temp_prev = zone1_water_temp;
          zone1_water_temp = ((msg[13])/2-16);
        }

        pump_state_known          = true;
        publish_states();
      } else if ((msg[3] == 0x80) && (msg[4] == 0x5C)) {
        publish_sensor(sensor_arr[current_sensor],encode_uint16(msg[5],msg[6]));
        ESP_LOGD(TAG,"current sensor = %d value = %d",current_sensor,encode_uint16(msg[5],msg[6]));
      }
    }
  
  }
  if (!zone1_active_prev && zone1_active && wanted_zone1_target_temp){
    zone1_active_prev = true;
    set_zone1_target_temp(wanted_zone1_target_temp);
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