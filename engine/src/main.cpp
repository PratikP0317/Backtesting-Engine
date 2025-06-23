#include "MarketData.h"
#include "Log.h"
#include <iostream>

int main() {
  std::cout << "Market Data Application Started" << std::endl;
  MarketData md;
  std::time_t t = std::time(0);
  std::tm* now = std::localtime(&t);
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", now);
  std::string logFileName = "app_" + std::string(buffer) + ".log";
  //Log::init(logFileName);
  Log::init("app.log");
  if (!md.loadFromCSV("data/spy_minute.csv")) {
    Log::error("Failed to load sample data.");
    return 1;
  }

  Log::info("Loaded bars: " + std::to_string(md.size()));
  Log::info("First bar timestamp: " + md.getFirst().timestamp);
  Log::info("Last bar VWAP: " + std::to_string(md.getLast().vwap));

  md.reset();
  Log::debug("Current index after reset: " + std::to_string(md.getCurrentIndex()));

  md.next();
  Log::debug("After next(), timestamp: " + md.current().timestamp);

  int index = md.findIndexByTimestamp("2025-06-13 12:24:00+00:00");
  Log::info("Index for 12:24:00: " + std::to_string(index));

  auto range = md.getRange(0, 2);
  Log::info("Range size (0 to 2): " + std::to_string(range.size()));

  auto between = md.getBetweenTimestamps("2025-06-13 12:23:00+00:00", "2025-06-13 12:24:00+00:00");
  Log::info("Bars between 12:23 and 12:24: " + std::to_string(between.size()));

  return 0;
}
