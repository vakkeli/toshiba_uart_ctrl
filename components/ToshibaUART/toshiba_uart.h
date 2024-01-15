#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/defines.h"
#ifdef USE_BINARY_SENSOR
#include "esphome/components/binary_sensor/binary_sensor.h"
#endif

namespace esphome {
namespace toshiba_uart {

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

    void setup() override;
    void loop() override;
    void dump_config() override;
};


}  // namespace toshiba_uart
}  // namespace esphome