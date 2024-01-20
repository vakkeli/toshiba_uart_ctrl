import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from . import ToshibaUART, CONF_TOSHIBAUART_ID
from esphome.const import (
    CONF_TARGET_TEMPERATURE,
    DEVICE_CLASS_TEMPERATURE,
    UNIT_CELSIUS,
)

ICON_HEAT_PUMP_O = "mdi:heat-pump-outline"
ICON_HEAT_PUMP = "mdi:heat-pump"
ICON_HVAC = "mdi:hvac"
ICON_BOILER = "mdi:water-boiler"
ICON_RADIATOR = "mdi:radiator"

ICON_THERMOMETER_WATER = "mdi:thermometer-water"
ICON_HOME_THERMOMETER = "mdi:home-thermometer"

CONF_HEATING_TARGET_TEMP = "heating_target_temp"
CONF_HOTWATER_TARGET_TEMP = "hotwater_target_temp"

TYPES = [
    CONF_HEATING_TARGET_TEMP,
    CONF_HOTWATER_TARGET_TEMP,
]

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_TOSHIBAUART_ID): cv.use_id(ToshibaUART),
            cv.Optional(CONF_HEATING_TARGET_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_HOME_THERMOMETER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_HOTWATER_TARGET_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
        }
    ).extend(cv.COMPONENT_SCHEMA)
)


async def setup_conf(config, key, hub):
    if sensor_config := config.get(key):
        sens = await sensor.new_sensor(sensor_config)
        cg.add(getattr(hub, f"set_{key}_sensor")(sens))


async def to_code(config):
    hub = await cg.get_variable(config[CONF_TOSHIBAUART_ID])
    for key in TYPES:
        await setup_conf(config, key, hub)