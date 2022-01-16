import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

DEPENDENCIES = ['i2c']
CODEOWNERS = ['@crossan007']

axp192_ns = cg.esphome_ns.namespace('axp192')

AXP192Component = axp192_ns.class_('AXP192Component', i2c.I2CDevice, cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(AXP192Component)
}).extend(i2c.i2c_device_schema(None))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield i2c.register_i2c_device(var, config)