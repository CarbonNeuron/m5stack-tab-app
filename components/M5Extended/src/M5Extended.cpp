#include "./M5Extended.hpp"


namespace cLib {

bool M5StackTab5Extended::set_battery_qc_charging_enabled(bool enable) {
  logger_.info("Setting battery QC charging to {}", enable ? "enabled" : "disabled");
  return set_io_expander_output(0x44, IO44_BIT_CHG_EN, enable);
}

} // namespace cLib