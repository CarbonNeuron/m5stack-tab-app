#include <atomic>
#include <chrono>
#include <thread>

#include "M5Extended.hpp"
#include "logger.hpp"
#include "task.hpp"

using namespace std::chrono_literals;

extern "C" void app_main(void) {
  espp::Logger logger({.tag = "M5STACK-TAB5-APP-MAIN", .level = espp::Logger::Verbosity::DEBUG});

  logger.info("Bootup");

  cLib::M5StackTab5Extended &tab5 = cLib::M5StackTab5Extended::get();

  logger.info("Running on M5Stack Tab5");

  // first let's get the internal i2c bus and probe for all devices on the bus
  logger.info("Probing internal I2C bus...");
  auto &i2c = tab5.internal_i2c();
  std::vector<uint8_t> found_addresses;
  for (uint8_t address = 1; address < 128; address++) {
    if (i2c.probe_device(address)) {
      found_addresses.push_back(address);
    }
  }
  logger.info("Found devices at addresses: {::#02x}", found_addresses);

  // Initialize the IO expanders
  logger.info("Initializing IO expanders...");
  if (!tab5.initialize_io_expanders()) {
    logger.error("Failed to initialize IO expanders!");
    return;
  }

  logger.info("Starting charging...");
  tab5.set_charging_enabled(true);
  tab5.set_battery_qc_charging_enabled(true);

  logger.info("Initialization complete.");
}
