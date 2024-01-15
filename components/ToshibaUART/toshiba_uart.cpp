#include "esphome/core/log.h"
#include "toshiba_uart.h"

namespace esphome {
namespace toshiba_uart {

static const char *TAG = "toshiba_uart.component";

int i = 1;
int msg_len = 0;
uint8_t prev_c = 0;
uint8_t c_now = 0;

bool status_msg = false;
bool pump_onoff;

bool heat_pump_heating;
bool heat_resistor_heating;
bool heat_pump_onoff;

bool hotwater_pump_heating;
bool hotwater_resistor_heating;
bool hotwater_pump_onoff;

int heating_water_temp = 0;

void ToshibaUART::setup() {

}

void ToshibaUART::loop() {
  status_msg = false;
  while (available()) {
    prev_c = c_now;
    read_byte(&c_now);

    if( i == 3 ){
      msg_len = c_now;
    }
    else if ( i == 7 && c_now == 0xA0 ) {
      status_msg = true;
    }
    else if ( i == 9 && status_msg && (c_now & 1) ) {
      pump_onoff = (c_now & 1);
    }
    else if ( i == 10 && status_msg ) {
      heat_pump_heating = (c_now & (1 << 1));
      heat_resistor_heating = (c_now & (1));
      heat_pump_onoff = (c_now & (1 << 4));
       
      ESP_LOGD(TAG,"The pump is: %d. Hotwater heating onoff: %d. Hotwater Pump pumpin: %d. Hotwater pump heater resistor %d.", pump_onoff, hotwater_pump_onoff,hotwater_pump_heating,hotwater_resistor_heating);
    }
    else if ( i == 11 && status_msg ) {
      hotwater_pump_heating = (c_now & (1 << 1));
      hotwater_resistor_heating = (c_now & (1));
      hotwater_pump_onoff = (c_now & (1 << 4));
       
      ESP_LOGD(TAG,"Heating onoff: %d. Heating pumpin: %d. Heating resistor %d.",heat_pump_onoff,heat_pump_heating,heat_resistor_heating);
    }
    else if ( i == 13 && status_msg ) {
      heating_water_temp = ((c_now)/2-16);
      ESP_LOGD(TAG,"Heating water temp: %d.", heating_water_temp);
    }
    
    if (c_now == 0xF0 && prev_c == 0xA0){
      i=2;
      status_msg = false;
    }
    else{
      i++;
    }
  }

  #ifdef USE_BINARY_SENSOR
    if (this->pump_onoff_binary_sensor_) {
      this->pump_onoff_binary_sensor_->publish_state(pump_onoff);
    }
    if (this->heat_pump_heating_binary_sensor_) {
      this->heat_pump_heating_binary_sensor_->publish_state(heat_pump_heating);
    }
    if (this->heat_resistor_heating_binary_sensor_) {
      this->heat_resistor_heating_binary_sensor_->publish_state(heat_resistor_heating);
    }
    if (this->heat_pump_onoff_binary_sensor_) {
      this->heat_pump_onoff_binary_sensor_->publish_state(heat_pump_onoff);
    }
    if (this->hotwater_pump_heating_binary_sensor_) {
      this->hotwater_pump_heating_binary_sensor_->publish_state(hotwater_pump_heating);
    }
    if (this->hotwater_resistor_heating_binary_sensor_) {
      this->hotwater_resistor_heating_binary_sensor_->publish_state(hotwater_resistor_heating);
    }
    if (this->hotwater_pump_onoff_binary_sensor_) {
      this->hotwater_pump_onoff_binary_sensor_->publish_state(hotwater_pump_onoff);
    }
  #endif

}

void ToshibaUART::dump_config(){
    ESP_LOGCONFIG(TAG, "Toshiba UART component");
}

}  // namespace toshiba_uart
}  // namespace esphome