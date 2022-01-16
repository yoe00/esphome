import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import switch
from esphome.const import CONF_ID
from .. import AXP192Component, axp192_ns

CODEOWNERS = ["@crossan007"]
DEPENDENCIES = ["axp192"]

AXP192Switch = axp192_ns.class_("AXP192Switch", switch.Switch, cg.Component)

AXPControllablePort = axp192_ns.enum("AXPControllablePort")

AXP_PORTS = {
   "LDO3": AXPControllablePort.LDO3
}

CONFIG_SCHEMA = switch.SWITCH_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(AXP192Switch),
        cv.GenerateID('axp'): cv.use_id(AXP192Component),
        cv.Required('port'): cv.enum(
            AXP_PORTS, upper=True, space="_"
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield switch.register_switch(var, config)

    # TODO: Maybe there's a better (non-id-requiring way) to get this component.
    axp = yield cg.get_variable(config["axp"])
    cg.add(var.set_axp(axp))
    cg.add(var.set_port(config['port']))