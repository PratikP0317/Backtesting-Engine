#include <fstream>  
#include <sstream>
#include <stdexcept>  
#include <string>
#include <vector>


#include "MarketData.h"
#include "Log.h"


bool MarketData::loadFromCSV(const std::string &filepath) {
  Log::info("Attempting to load CSV: " + filepath);
  std::ifstream file(filepath);
  if (!file.is_open()) {
    Log::error("Failed to open CSV: " + filepath);
    return false;
  }

  std::string line;
  std::getline(file, line); // Skip header
  Log::debug("Skipped CSV header line");

  int lineNumber = 1;
  while (std::getline(file, line)) {
    lineNumber++;
    std::istringstream ss(line);
    Bar bar;
    std::string token;

    try {
      std::getline(ss, bar.symbol, ',');
      std::getline(ss, bar.timestamp, ',');
      std::getline(ss, token, ','); bar.open = std::stod(token);
      std::getline(ss, token, ','); bar.high = std::stod(token);
      std::getline(ss, token, ','); bar.low  = std::stod(token);
      std::getline(ss, token, ','); bar.close = std::stod(token);
      std::getline(ss, token, ','); bar.volume = std::stol(token);
      std::getline(ss, token, ','); bar.tradeCount = std::stol(token);
      std::getline(ss, token, ','); bar.vwap = std::stod(token);
      //Log all the data loaded
      Log::info("Loaded bar: " + bar.symbol + " at " + bar.timestamp + "\n" +
           "Open: " + std::to_string(bar.open) + "\n" +
           "High: " + std::to_string(bar.high) + "\n" +
           "Low: " + std::to_string(bar.low) + "\n" +
           "Close: " + std::to_string(bar.close) + "\n" +
           "Volume: " + std::to_string(bar.volume) + "\n" +
           "Trade Count: " + std::to_string(bar.tradeCount) + "\n" +
           "VWAP: " + std::to_string(bar.vwap));
    } catch (const std::exception& e) {
      Log::warn("Failed to parse line " + std::to_string(lineNumber) + ": " + e.what());
      continue;
    }
    bars_.push_back(bar);
  }

  Log::info("Successfully loaded " + std::to_string(bars_.size()) + " bars from " + filepath);
  file.close();
  return true;
}

const Bar& MarketData::get(int index) const {
  if (index < 0 || index >= static_cast<int>(bars_.size())) {
    throw std::out_of_range("Index out of range in MarketData::get");
  }
  return bars_[index];
}

const Bar& MarketData::getFirst() const {
  if (bars_.empty()) {
    throw std::out_of_range("No bars available in MarketData::getFirst");
  }
  return bars_.front();
}

const Bar& MarketData::getLast() const {
  if (bars_.empty()) {
    throw std::out_of_range("No bars available in MarketData::getLast");
  }
  return bars_.back();
}