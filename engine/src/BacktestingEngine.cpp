#include "BacktestingEngine.h"
#include "Log.h"

BacktestEngine::BacktestEngine(double startingCash) 
: cash_(startingCash), position_(0), entryPrice_(0), inPosition_(false) {}

bool BacktestEngine::loadData(const std::string& filepath) {
  return data_.loadFromCSV(filepath);
}

void BacktestEngine::run() {
  Log::info("Starting backtest...");
  if (data_.isEmpty()) {
    Log::error("No data loaded. Please load data before running the backtest.");
    return;
  }
  do {
    onBar();
  } while (data_.next());
  Log::info("Backtest completed.");
}

void BacktestEngine::printSummary() const {
  Log::info("Backtest Summary:");
  Log::info("Final Cash: " + std::to_string(cash_));
  Log::info("Final Position: " + std::to_string(position_));
  Log::info("Entry Price: " + std::to_string(entryPrice_));
}

void BacktestEngine::onBar() {
  const Bar& bar = data_.current();
  if (!inPosition_) {
    if (bar.close > bar.open) {
      // Enter position
      position_ = cash_ / bar.close;
      entryPrice_ = bar.close;
      cash_ -= position_ * entryPrice_;
      inPosition_ = true;
      Log::info("BUY at " + std::to_string(bar.close) + " on " + bar.timestamp);
    }
  } else {
    if (bar.close < entryPrice_ * 0.99) {
      // Exit position
      cash_ += position_ * bar.close;
      Log::info("SELL at " + std::to_string(bar.close) + " on " + bar.timestamp);
      position_ = 0;
      entryPrice_ = 0;
      inPosition_ = false;
    }
  }
}
