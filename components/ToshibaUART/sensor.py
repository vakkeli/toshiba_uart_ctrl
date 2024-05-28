import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from . import ToshibaUART, CONF_TOSHIBAUART_ID
from esphome.const import (
    CONF_TARGET_TEMPERATURE,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_CURRENT,
    UNIT_CELSIUS,
    UNIT_AMPERE,
    DEVICE_CLASS_DURATION,
    UNIT_SECOND,
    ICON_TIMER,
    STATE_CLASS_TOTAL_INCREASING,
    ENTITY_CATEGORY_DIAGNOSTIC,
)

ICON_HEAT_PUMP_O = "mdi:heat-pump-outline"
ICON_HEAT_PUMP = "mdi:heat-pump"
ICON_HVAC = "mdi:hvac"
ICON_BOILER = "mdi:water-boiler"
ICON_RADIATOR = "mdi:radiator"

ICON_THERMOMETER_WATER = "mdi:thermometer-water"
ICON_HOME_THERMOMETER = "mdi:home-thermometer"

CONF_ZONE1_WATER_TEMP = "zone1_water_temp"
CONF_HOTWATER_TEMP = "hotwater_temp"

CONF_HEADER_AMBIENT_TEMP    =   "header_ambient_temp"
CONF_CONDENSED_TEMP =   "condensed_temp"
CONF_INLET_TEMP =   "inlet_temp"
CONF_OUTLET_TEMP    =   "outlet_temp"
CONF_HEATER_OUTLET_TEMP =   "heater_outlet_temp"
CONF_HW_CYLINDER_TEMP   =   "hw_cylinder_temp"
CONF_MIXING_VALVE   =   "mixing_valve"
CONF_LOW_PRESSURE   =   "low_pressure"
CONF_HEAT_EXCHANGE_TEMP  =   "heat_exchange_temp"
CONF_OUTSIDE_AIR_TEMP    =   "outside_air_temp"
CONF_DISCHARGE_TEMP  =   "discharge_temp"
CONF_SUCTION_TEMP    =   "suction_temp"
CONF_HEAT_SINK_TEMP  =   "heat_sink_temp"
CONF_OUDOOR_UNIT_CURRENT    =   "oudoor_unit_current"
CONF_HEAT_EXCHANGER_OIL_TEMP =   "heat_exchanger_oil_temp"
CONF_COMPRESSOR_FREQ    =   "compressor_freq"
CONF_FAN_RPM    =   "fan_rpm"
CONF_OUTDOOR_PMV    =   "outdoor_pmv"
CONF_DISCHARGE_PRESSURE =   "discharge_pressure"
CONF_MICRO_COMPUTER_ENERGIZED_UPTIME    =   "micro_computer_energized_uptime"
CONF_HW_COMPRESSOR_UPTIME   =   "hw_compressor_uptime"
CONF_COOLING_COMPRESSOR_UPTIME  =   "cooling_compressor_uptime"
CONF_HEATING_COMPRESSOR_UPTIME  =   "heating_compressor_uptime"
CONF_AC_PUMP_UPTIME =   "ac_pump_uptime"
CONF_HW_CYLINDER_HEATER_OPERATION_UPTIME    =   "hw_cylinder_heater_operation_uptime"
CONF_BACKUP_HEATER_OPERATION_UPTIME =   "backup_heater_operation_uptime"
CONF_BOOSTER_HEATER_OPERATION_UPTIME    =   "booster_heater_operation_uptime"

TYPES = [
    CONF_ZONE1_WATER_TEMP,
    CONF_HOTWATER_TEMP,
    CONF_HEADER_AMBIENT_TEMP,
    CONF_CONDENSED_TEMP,
    CONF_INLET_TEMP,
    CONF_OUTLET_TEMP,
    CONF_HEATER_OUTLET_TEMP,
    CONF_HW_CYLINDER_TEMP,
    CONF_MIXING_VALVE,
    CONF_LOW_PRESSURE,
    CONF_HEAT_EXCHANGE_TEMP,
    CONF_OUTSIDE_AIR_TEMP,
    CONF_DISCHARGE_TEMP,
    CONF_SUCTION_TEMP,
    CONF_HEAT_SINK_TEMP,
    CONF_OUDOOR_UNIT_CURRENT,
    CONF_HEAT_EXCHANGER_OIL_TEMP,
    CONF_COMPRESSOR_FREQ,
    CONF_FAN_RPM,
    CONF_OUTDOOR_PMV,
    CONF_DISCHARGE_PRESSURE,
    CONF_MICRO_COMPUTER_ENERGIZED_UPTIME,
    CONF_HW_COMPRESSOR_UPTIME,
    CONF_COOLING_COMPRESSOR_UPTIME,
    CONF_HEATING_COMPRESSOR_UPTIME,
    CONF_AC_PUMP_UPTIME,
    CONF_HW_CYLINDER_HEATER_OPERATION_UPTIME,
    CONF_BACKUP_HEATER_OPERATION_UPTIME,
    CONF_BOOSTER_HEATER_OPERATION_UPTIME,
]

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(CONF_TOSHIBAUART_ID): cv.use_id(ToshibaUART),
            cv.Optional(CONF_ZONE1_WATER_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_HOME_THERMOMETER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_HOTWATER_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_HEADER_AMBIENT_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_CONDENSED_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_INLET_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_OUTLET_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_HEATER_OUTLET_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_HW_CYLINDER_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_MIXING_VALVE): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_LOW_PRESSURE): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_HEAT_EXCHANGE_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_OUTSIDE_AIR_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_DISCHARGE_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_SUCTION_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_HEAT_SINK_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_OUDOOR_UNIT_CURRENT): sensor.sensor_schema(
                unit_of_measurement=UNIT_AMPERE,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_CURRENT,
            ),
            cv.Optional(CONF_HEAT_EXCHANGER_OIL_TEMP): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                icon=ICON_THERMOMETER_WATER,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_TEMPERATURE,
            ),
            cv.Optional(CONF_COMPRESSOR_FREQ): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_FAN_RPM): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_OUTDOOR_PMV): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_DISCHARGE_PRESSURE): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_MICRO_COMPUTER_ENERGIZED_UPTIME): sensor.sensor_schema(
                unit_of_measurement=UNIT_SECOND,
                icon=ICON_TIMER,
                accuracy_decimals=0,
                state_class=STATE_CLASS_TOTAL_INCREASING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                device_class=DEVICE_CLASS_DURATION,
            ),
            cv.Optional(CONF_HW_COMPRESSOR_UPTIME): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_COOLING_COMPRESSOR_UPTIME): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_HEATING_COMPRESSOR_UPTIME): sensor.sensor_schema(
                unit_of_measurement=UNIT_SECOND,
                icon=ICON_TIMER,
                accuracy_decimals=0,
                state_class=STATE_CLASS_TOTAL_INCREASING,
                entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
                device_class=DEVICE_CLASS_DURATION,
            ),
            cv.Optional(CONF_AC_PUMP_UPTIME): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_HW_CYLINDER_HEATER_OPERATION_UPTIME): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_BACKUP_HEATER_OPERATION_UPTIME): sensor.sensor_schema(
                #Work in progress
            ),
            cv.Optional(CONF_BOOSTER_HEATER_OPERATION_UPTIME): sensor.sensor_schema(
                #Work in progress
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