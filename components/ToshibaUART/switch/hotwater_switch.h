#pragma once

#include "esphome/components/switch/switch.h"
#include "../toshiba_uart.h"

namespace esphome {
namespace toshiba_uart {

class HotwaterSwitch : public switch_::Switch, public Parented<ToshibaUART> {

    protected:
        void write_state(bool state) override;

};

}  // namespace toshiba_uart
}  // namespace esphome