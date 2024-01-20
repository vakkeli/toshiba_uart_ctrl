
#include "esphome/core/log.h"
#include "./zone1_target_temp.h"

namespace esphome {
namespace toshiba_uart {

void Zone1TargetTemp::control(float value) {
  this->parent_->set_zone1_target_temp(value);
}

}  // namespace toshiba_uart
}  // namespace esphome