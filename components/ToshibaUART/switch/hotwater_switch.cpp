
#include "esphome/core/log.h"
#include "./hotwater_switch.h"

namespace esphome {
namespace toshiba_uart {

void HotwaterSwitch::write_state(bool state) {
  this->parent_->set_hotwater_state(state);
}

}  // namespace toshiba_uart
}  // namespace esphome