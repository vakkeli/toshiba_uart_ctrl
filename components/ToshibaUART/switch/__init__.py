import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import switch
from .. import ToshibaUART, CONF_TOSHIBAUART_ID, toshiba_uart_ns

from esphome.const import (
    DEVICE_CLASS_SWITCH,
    ICON_BLUETOOTH,
    ENTITY_CATEGORY_CONFIG,
    ICON_PULSE,
)

ICON_BOILER = "mdi:water-boiler"
ICON_HOME_THERMOMETER = "mdi:home-thermometer"

Zone1Switch = toshiba_uart_ns.class_("Zone1Switch", switch.Switch, cg.Component)
# AutoModeSwitch = toshiba_uart_ns.class_("AutoModeSwitch", switch.Switch, cg.Component)
HotwaterSwitch = toshiba_uart_ns.class_("HotwaterSwitch", switch.Switch, cg.Component)
# CoolingSwitch = toshiba_uart_ns.class_("CoolingSwitch", switch.Switch, cg.Component)

CONF_ZONE1_SWITCH     = "zone1_switch"
# CONF_AUTOMODE_SWITCH   = "automode_switch"
CONF_HOTWATER_SWITCH   = "hotwater_switch"
# CONF_COOLING_SWITCH    = "cooling_switch"

# TYPES = [
#     CONF_HEATING_TARGET_TEMP,
#    CONF_HOTWATER_TARGET_TEMP,
# ]

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
        cv.GenerateID(CONF_TOSHIBAUART_ID): cv.use_id(ToshibaUART),
        cv.Optional(CONF_ZONE1_SWITCH): switch.switch_schema(
            Zone1Switch,
            device_class=DEVICE_CLASS_SWITCH,
            #entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_HOME_THERMOMETER,
        ),
        cv.Optional(CONF_HOTWATER_SWITCH): switch.switch_schema(
            HotwaterSwitch,
            device_class=DEVICE_CLASS_SWITCH,
            #entity_category=ENTITY_CATEGORY_CONFIG,
            icon=ICON_BOILER,
        ),
        }
    ).extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    ToshibaUART = await cg.get_variable(config[CONF_TOSHIBAUART_ID])
    if zone1_config := config.get(CONF_ZONE1_SWITCH):
        s = await switch.new_switch(zone1_config)
        await cg.register_parented(s, config[CONF_TOSHIBAUART_ID])
        cg.add(ToshibaUART.set_zone1_switch_switch(s))
    if hotwater_config := config.get(CONF_HOTWATER_SWITCH):
        s = await switch.new_switch(hotwater_config)
        await cg.register_parented(s, config[CONF_TOSHIBAUART_ID])
        cg.add(ToshibaUART.set_hotwater_switch_switch(s))