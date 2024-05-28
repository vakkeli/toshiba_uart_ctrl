# Toshiba Heat pump control

This is a ESPHome External component for controlling Toshiba Air-to-Water heat pumps. 
The hardware used in this is the @issalig designed control board that will adjust the AB/TC-link physical interface to 3.3V logic level compatible with the ESP boards.
Thanks goes to @issalig and this is the repo https://github.com/issalig/toshiba_air_cond .

This is only tested with:
 - Heat pump model: Toshiba Estia S5 HWS-805
 - Controller model: HWS-AMS54
 - Above mentioned control board with Wemos D1 mini

A lot of features are still missing because I have not had the time to finish and polish this project.
However, it works for my use scenario as is.
Much more information could be pulled out of the pump and many features could be configured.

Feel free to add missing features and make pull requests. 
I might add the cooling switch at least when it gets too hot in here :D

You can first use the UART part only to see the RAW HEX UART communication to verify that your pump speaks the same language.
If the pump receives unknown messages there will be some kind of error message in the header and I think some of the heating/cooling capabilities are turned off.

## Hardware

Look above for the link to the hardware controller board.

### Connection

**CAUTION**
I fried few transistors by making the polarity error.
Always check the polarity on your own device before making the connection.

Below is the picture of the connection for my controller and pump.

![Alt text](./20240528_151204.jpg?raw=true "Connection")

## Operation

This code works as a second header remote, so it will give the same commands as the header remote would and receive and read all the same data.
This has not proved to be problem so far, but safety measures should be made (TO-DO #1).

### Request extra information

This component and the controller are able to read the hidden extra information in the "Field menu".
The update frequency can be changed with the ESPHome parameter `update_interval`.
The value represents what is the wait time between requests.
If you have two sensors enabled from the hidden menu and the `update_interval: 20s`, each sensor is going to be update every 40 seconds.

There are lots of stats that are not implemented yet.
Only those that are in the example are finished.

## TO-Do

 1. Restrict commands to be sent with a wait time only after the pump/header or this control board has made communication.
 2. Complete all the request data entries. Now only few are supported.
 3. Add all other basic functionalities. Most importantly, turn on cooling.
 4. UART throttles some times (From ESPHome logs). I don't know why, but maybe needs a fix.
 5. Could switch this controller to work as a secondary remote. Might be bothersome to decode the handshake (logged in the `logs_from_uart` file).


## Log captures by me

There is a `logs_from_uart` file in the component directory.
There lies a bunch of recorded communication between the pump and the header remote.
Could provide valuable information for extra functions.

## ESPHome example

Uncomment the last three lines to get raw UART logging from ESPHome.

```yaml
external_components:
  - source:
      type: git
      url: https://github.com/vakkeli/toshiba_uart_ctrl
    components: [ToshibaUART]

ToshibaUART:
  update_interval: 20s
  id: toshibauart

binary_sensor:
  - platform: ToshibaUART
    pump_onoff:
      name: "Toshiba Pump On/Off"
      id: pump_onoff
    heat_pump_heating:
      id: heat_pump_heating
      name: "Heat Pumping"
    heat_resistor_heating:
      id: heat_resistor_heating
      name: "Heating with Coil"
    hotwater_pump_heating:
      id: hotwater_pump_heating
      name: "Hotwater heat pumping"
    hotwater_resistor_heating:
      id: hotwater_resistor_heating
      name: "Hotwater Coil heating"

sensor:
  - platform: ToshibaUART
    zone1_water_temp:
      name: "Zone 1 water temperature"
      id: zone1_water_temp
    outside_air_temp: # Extra from "field menu"
      name: "Toshiba - Outdoor ambient temperature"
      id: outside_air_temp
    oudoor_unit_current: # Extra from "field menu"
      name: "Toshiba - Outdoor unit current"
      id: oudoor_unit_current
    heating_compressor_uptime: # Extra from "field menu"
      name: "Toshiba - Heating compressor uptime"
      id: heating_compressor_uptime

number:
  - platform: ToshibaUART
    zone1_target_temp:
      name: "Zone 1 target temperature"
      mode: box
    hotwater_target_temp:
      name: "Hotwater target temperature"
      mode: box


switch:
  - platform: ToshibaUART
    zone1_switch:
      name: "Toshiba - Zone 1"
    hotwater_switch:
      name: "Toshiba - Hotwater"
    auto_mode_switch:
      name: "Toshiba - Auto Mode"

uart:
  id: uart_bus
  tx_pin: 
    number: D8
    inverted: False
  rx_pin: 
    number: D7
    inverted: False
  baud_rate: 2400
  rx_buffer_size: 2048
  stop_bits: 1
  parity: NONE
#  debug:
#    direction: BOTH
#    dummy_receiver: true
```