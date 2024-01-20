import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from . import ToshibaUART, CONF_TOSHIBAUART_ID

from esphome.const import (
    ICON_HEATING_COIL
)

ICON_HEAT_PUMP_O = "mdi:heat-pump-outline"
ICON_HEAT_PUMP = "mdi:heat-pump"
ICON_HVAC = "mdi:hvac"
ICON_BOILER = "mdi:water-boiler"
ICON_RADIATOR = "mdi:radiator"

CONF_PUMP_ONOFF = "pump_onoff"
CONF_HEAT_PUMP_HEATING =     "heat_pump_heating"
CONF_HEAT_RESISTOR_HEATING =     "heat_resistor_heating"
CONF_HEAT_PUMP_ONOFF =     "heat_pump_onoff"
CONF_HOTWATER_PUMP_HEATING =     "hotwater_pump_heating"
CONF_HOTWATER_RESISTOR_HEATING =     "hotwater_resistor_heating"
CONF_HOTWATER_PUMP_ONOFF =     "hotwater_pump_onoff"

TYPES = [
    CONF_PUMP_ONOFF,
    CONF_HEAT_PUMP_HEATING,
    CONF_HEAT_RESISTOR_HEATING,
    CONF_HEAT_PUMP_ONOFF,
    CONF_HOTWATER_PUMP_HEATING,
    CONF_HOTWATER_RESISTOR_HEATING,
    CONF_HOTWATER_PUMP_ONOFF
]

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_TOSHIBAUART_ID): cv.use_id(ToshibaUART),
            cv.Optional(CONF_PUMP_ONOFF): binary_sensor.binary_sensor_schema(
                icon=ICON_HEAT_PUMP_O
                
            ),
            cv.Optional(CONF_HEAT_PUMP_HEATING): binary_sensor.binary_sensor_schema(
                icon=ICON_HVAC

            ),
            cv.Optional(CONF_HEAT_RESISTOR_HEATING): binary_sensor.binary_sensor_schema(
                icon=ICON_HEATING_COIL

            ),
            cv.Optional(CONF_HEAT_PUMP_ONOFF): binary_sensor.binary_sensor_schema(
                icon=ICON_RADIATOR

            ),
            cv.Optional(CONF_HOTWATER_PUMP_HEATING): binary_sensor.binary_sensor_schema(
                icon=ICON_HEAT_PUMP

            ),
            cv.Optional(CONF_HOTWATER_RESISTOR_HEATING): binary_sensor.binary_sensor_schema(
                icon=ICON_HEATING_COIL

            ),
            cv.Optional(CONF_HOTWATER_PUMP_ONOFF): binary_sensor.binary_sensor_schema(
                icon=ICON_BOILER

            ),
        }
    ).extend(cv.COMPONENT_SCHEMA)
)


async def setup_conf(config, key, hub):
    if sensor_config := config.get(key):
        var = await binary_sensor.new_binary_sensor(sensor_config)
        cg.add(getattr(hub, f"set_{key}_binary_sensor")(var))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TOSHIBAUART_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)