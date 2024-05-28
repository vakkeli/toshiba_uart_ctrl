
#include "esphome/core/log.h"
#include "./auto_mode_switch.h"

namespace esphome {
namespace toshiba_uart {

void AutoModeSwitch::write_state(bool state) {
  this->parent_->set_auto_mode(state);
}

}  // namespace toshiba_uart
}  // namespace esphome