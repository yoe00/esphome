Exposes control of an AXP192 power management IC to ESPHome YAML configuration

Device functionality enumerated at https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/AXP192_datasheet_en.pdf
Pinout chart here: https://github.com/m5stack/M5-Schematic/blob/master/Core/AXP192%20Datasheet%20v1.13_cn.pdf

Requires base "axp192" configuration declaration:
```
axp192:
  address: <addres of the IC>
  i2c_id: <name/id of the I2C bus>
```

Following the `axp192` configuraiton, various `sensor`, `GPIO`, `battery`, and `power_supply` elements become available:


# Power Supply
https://esphome.io/components/power_supply.html

This allows ESPHome to dynamically enable/disable power to the selected peripherials, and optionall present a "switch" entity in HomeAssistant

```
power_supply:
  - platform: axp192
    axp_id: <name/id of the configured AXP entity>
    id: anything
    port: "DC1", "DC2", "DC3", "LDO0", "LDO1", "LDO2", "LDO3"
    voltage: <float>
    show_switch_entity: <boolean> #Whether or not to present this output as a "Switch" in HomeAssistant (possibly redundant with `internal: true`)
```

# Battery

```
battery:
  - platform: axp192
    axp_id: <name/id of the configured AXP entity>
    id: anything
    voltage: <4.1/4.15/4.2/4.36>
    charge_rage: <ENUM>
```

# Sensors

```
sensor:
  - platform: axp192
    axp_id: <name/id of the configured AXP entity>
    id: anything
    battery_time: #time until battery is charged
    battery_level: # level of the primary battery
      name: "Battery Level"
    power_source: #USB, or Battery
    power_usage: # current power usage (mA or mW)
    power_ok: # 
    output_voltage: #
```

# GPIO
The AXP192 exposes 3 GPIO pins, which are available for use within ESPHome
GPIO0: LDO/ADC
GPIO1: PWM/ADC
GPIO2: PWM/ADC
GPIO3: GPIO
GPIO4: GPIO


# Services:
* Soft Reset
* Hard Reset
```