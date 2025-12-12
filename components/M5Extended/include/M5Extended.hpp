#pragma once

#include <m5stack-tab5.hpp>

namespace cLib {
class M5StackTab5Extended : public espp::M5StackTab5 {
public:
  static M5StackTab5Extended &get() {
    static M5StackTab5Extended instance;
    return instance;
  }

  bool set_battery_qc_charging_enabled(bool enable);

};
} // namespace cLib