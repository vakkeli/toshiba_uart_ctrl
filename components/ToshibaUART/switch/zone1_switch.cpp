
#include "esphome/core/log.h"
#include "./zone1_switch.h"

namespace esphome {
namespace toshiba_uart {

void Zone1Switch::write_state(bool state) {
  this->parent_->set_zone1_state(state);
}

}  // namespace toshiba_uart
}  // namespace esphome