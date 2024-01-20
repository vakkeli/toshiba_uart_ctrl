import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number
from .. import ToshibaUART, CONF_TOSHIBAUART_ID, toshiba_uart_ns

from esphome.const import (
    CONF_TARGET_TEMPERATURE,
    DEVICE_CLASS_TEMPERATURE,
    UNIT_CELSIUS,
)

ICON_THERMOMETER_WATER = "mdi:thermometer-water"
ICON_HOME_THERMOMETER = "mdi:home-thermometer"

Zone1TargetTemp = toshiba_uart_ns.class_("Zone1TargetTemp", number.Number, cg.Component)
HotwaterTargetTemp = toshiba_uart_ns.class_("HotwaterTargetTemp", number.Number, cg.Component)

CONF_ZONE1_TARGET_TEMP     = "zone1_target_temp"
CONF_HOTWATER_TARGET_TEMP     = "hotwater_target_temp"

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
        cv.GenerateID(CONF_TOSHIBAUART_ID): cv.use_id(ToshibaUART),
        cv.Optional(CONF_ZONE1_TARGET_TEMP): number.number_schema(
            Zone1TargetTemp,
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_HOME_THERMOMETER,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        cv.Optional(CONF_HOTWATER_TARGET_TEMP): number.number_schema(
            HotwaterTargetTemp,
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_THERMOMETER_WATER,
            device_class=DEVICE_CLASS_TEMPERATURE,
        ),
        }
    ).extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    ToshibaUART = await cg.get_variable(config[CONF_TOSHIBAUART_ID])
    if zone1_target_temp_config := config.get(CONF_ZONE1_TARGET_TEMP):
        n = await number.new_number(
            zone1_target_temp_config, min_value=15, max_value=55, step=1
        )
        await cg.register_parented(n, config[CONF_TOSHIBAUART_ID])
        cg.add(ToshibaUART.set_zone1_target_temp_number(n))
    if hotwater_target_temp_config := config.get(CONF_HOTWATER_TARGET_TEMP):
        n = await number.new_number(
            hotwater_target_temp_config, min_value=40, max_value=75, step=1
        )
        await cg.register_parented(n, config[CONF_TOSHIBAUART_ID])
        cg.add(ToshibaUART.set_hotwater_target_temp_number(n))