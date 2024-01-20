#pragma once

#include "esphome/components/number/number.h"
#include "../toshiba_uart.h"

namespace esphome {
namespace toshiba_uart {

class HotwaterTargetTemp : public number::Number, public Parented<ToshibaUART> {
 public:
  HotwaterTargetTemp() = default;

 protected:
  void control(float value);
};

}  // namespace toshiba_uart
}  // namespace esphome