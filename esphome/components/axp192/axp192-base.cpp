#include "axp192-base.h"
#include "esphome/core/log.h"

/**
 * @brief Uses the platform-agnostic AXP192 library at https://github.com/tuupola/axp192
 * to interface with the ESPHome managed I2C Bus
 * 
 */
// BEST DOCS: https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/AXP192_datasheet_en.pdf
// https://github.com/tuupola/axp192
// https://esphome.io/cookbook/leak-detector-m5stickc
// https://github.com/tanakamasayuki/I2C_AXP192
// https://www.reddit.com/r/Esphome/comments/hbaj11/support_for_axp192_power_management_chip/
// https://github.com/airy10/esphome-m5stickC/network/members
// https://docs.nanoframework.net/devicesdetails/Axp192/README.html

namespace esphome {
namespace axp192 {

static const char *TAG = "axp192.base";


int32_t i2c_read(void *handle, uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size) {
  ((AXP192Component*)handle)->set_i2c_address(address);
  return ((AXP192Component*)handle)->read_register(reg,buffer,size);
}
int32_t i2c_write(void *handle, uint8_t address, uint8_t reg, const uint8_t *buffer, uint16_t size) {
 ((AXP192Component*)handle)->set_i2c_address(address);
  return ((AXP192Component*)handle)->write_register(reg,buffer,size);
}
 
void AXP192Component::setup() {

  // Wire-up the platform-agnostic AXP192 library with the I2C bus managed by ESPHome
  this->axp.read = &i2c_read;
  this->axp.write = &i2c_write;
  this->axp.handle = this;

}

void AXP192Component::dump_config() {
  float vacin, iacin, vvbus, ivbus, temp, pbat, vbat, icharge, idischarge, vaps, cbat, vts;

  ESP_LOGCONFIG(TAG, "AXP192:");
  LOG_I2C_DEVICE(this);
  /* All ADC registers will be read as floats. */
  axp192_read(&axp, AXP192_ACIN_VOLTAGE, &vacin);
  axp192_read(&axp, AXP192_ACIN_CURRENT, &iacin);
  axp192_read(&axp, AXP192_VBUS_VOLTAGE, &vvbus);
  axp192_read(&axp, AXP192_VBUS_CURRENT, &ivbus);
  axp192_read(&axp, AXP192_TEMP, &temp);
  axp192_read(&axp, AXP192_TS_INPUT, &vts);
  axp192_read(&axp, AXP192_BATTERY_POWER, &pbat);
  axp192_read(&axp, AXP192_BATTERY_VOLTAGE, &vbat);
  axp192_read(&axp, AXP192_CHARGE_CURRENT, &icharge);
  axp192_read(&axp, AXP192_DISCHARGE_CURRENT, &idischarge);
  axp192_read(&axp, AXP192_APS_VOLTAGE, &vaps);
  axp192_read(&axp, AXP192_COULOMB_COUNTER, &cbat);


  ESP_LOGD(TAG,
    "vacin: %.2fV iacin: %.2fA vvbus: %.2fV ivbus: %.2fA vts: %.2fV temp: %.0fC "
    "pbat: %.2fmW vbat: %.2fV icharge: %.2fA idischarge: %.2fA, vaps: %.2fV cbat: %.2fmAh",
    vacin, iacin, vvbus, ivbus, vts, temp, pbat, vbat, icharge, idischarge, vaps, cbat
);
  
}

float AXP192Component::get_setup_priority() const { return setup_priority::DATA; }


}  // namespace axp192
}  // namespace esphome
