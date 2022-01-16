#include "axp192_switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace axp192 {

static const char *const TAG = "switch.axp192";

float AXP192Switch::get_setup_priority() const { return setup_priority::DATA; }
void AXP192Switch::setup() {
  ESP_LOGCONFIG(TAG, "Setting up AXP Switch '%s'...", this->name_.c_str());

  this->turn_on();
 
}
void AXP192Switch::dump_config() {
  LOG_SWITCH("", "AXP Switch", this);

  //const LogString *restore_mode = LOG_STR("");

}


void AXP192Switch::write_state(bool state) {

  if (state) {
    axp192_ioctl(&this->axp_->axp, this->port_);
  }
  else {
    // Conveniently, the register for disabling a controllable output 
    // is one above the one for enabling it.
    axp192_ioctl(&this->axp_->axp,  this->port_+1);
  }

 
  this->publish_state(state);
}

}  // namespace axp192
}  // namespace esphome
