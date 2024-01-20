
#include "esphome/core/log.h"
#include "./hotwater_target_temp.h"

namespace esphome {
namespace toshiba_uart {

void HotwaterTargetTemp::control(float value) {
  this->parent_->set_hotwater_target_temp(value);
}

}  // namespace toshiba_uart
}  // namespace esphome