#include "BacktestingEngine.h"
#include "Log.h"
#include <iostream>

int main() {
  std::cout << "Starting Engine" << std::endl;
  std::time_t t = std::time(0);
  std::tm* now = std::localtime(&t);
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", now);
  std::string logFileName = "app_" + std::string(buffer) + ".log";
  //Log::init(logFileName);
  Log::init("app.log", true);

  BacktestEngine engine(100'000.0);
  if (!engine.loadData("data/spy_minute.csv")) {
    Log::error("Failed to load market data.");
    return 1;
  }
  engine.run();
  engine.printSummary();
  Log::close();

  return 0;
}
