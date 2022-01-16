#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "../axp192-base.h"

namespace esphome {
namespace axp192 {

enum AXPControllablePort {
  DCDC1,
  DCDC2,
  DCDC3,
  LDO1,
  LDO2 = AXP192_LDO2_ENABLE,
  LDO3 = AXP192_LDO3_ENABLE
};

class AXP192Switch : public switch_::Switch, public Component {
 public:
  void set_axp(AXP192Component *axp) { axp_ = axp; }
  void set_port(AXPControllablePort port) { port_ = port; }

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  float get_setup_priority() const override;

  void setup() override;
  void dump_config() override;

 protected:
  void write_state(bool state) override;

  AXP192Component *axp_;
  AXPControllablePort port_;
};

}  // namespace axp192
}  // namespace esphome
