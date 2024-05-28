import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import CONF_ID

CODEOWNERS = ["@vakkeli"]
DEPENDENCIES = ['uart']
CONF_TOSHIBAUART_ID = "toshiba_uart"

toshiba_uart_ns = cg.esphome_ns.namespace('toshiba_uart')
ToshibaUART = toshiba_uart_ns.class_('ToshibaUART', cg.PollingComponent, uart.UARTDevice)

CONFIG_SCHEMA = (cv.Schema(
    {
    cv.GenerateID(): cv.declare_id(ToshibaUART)
}
)
.extend(uart.UART_DEVICE_SCHEMA)
.extend(cv.polling_component_schema("30s"))
)
def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)