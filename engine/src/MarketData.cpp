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

  int lineNumber = 1;
  Log::info("Starting to parse CSV file: " + filepath);
  Log::info("symbol,timestamp,open,high,low,close,volume,tradeCount,vwap");
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

      // Log loaded bar data
      // Log::info(bar.symbol + "," + bar.timestamp + "," + std::to_string(bar.open) + "," + 
      //           std::to_string(bar.high) + "," + std::to_string(bar.low) + "," + 
      //           std::to_string(bar.close) + "," + std::to_string(bar.volume) + "," + 
      //           std::to_string(bar.tradeCount) + "," + std::to_string(bar.vwap));
    } catch (const std::exception& e) {
      Log::warn("Failed to parse line " + std::to_string(lineNumber) + ": " + e.what());
      return false;
    }
    bars_.push_back(bar);
  }

  Log::info("Successfully loaded " + std::to_string(bars_.size()) + " bars from " + filepath);
  file.close();
  return true;
}

bool MarketData::isValidIndex(int index) const {
  return index >= 0 && index < static_cast<int>(bars_.size());
}

const Bar& MarketData::get(int index) const {
  if (!isValidIndex(index)) {
    throw std::out_of_range("Index out of range in MarketData::get");
  }
  return bars_[index];
}

const Bar& MarketData::getFirst() const {
  if (isEmpty()) {
    throw std::out_of_range("No bars available in MarketData::getFirst");
  }
  return bars_.front();
}

const Bar& MarketData::getLast() const {
  if (isEmpty()) {
    throw std::out_of_range("No bars available in MarketData::getLast");
  }
  return bars_.back();
}

const Bar& MarketData::current() const {
  if (isEmpty()) {
    throw std::out_of_range("No bars available in MarketData::current");
  }
  if (!isValidIndex(currentIndex_)) {
    throw std::out_of_range("currentIndex_ out of range in MarketData::current");
  }
  return bars_[currentIndex_];
}

bool MarketData::next() {
  if (isValidIndex(currentIndex_ + 1)) {
    currentIndex_++;
    return true;
  }
  return false;
}

bool MarketData::prev() {
  if (isValidIndex(currentIndex_ - 1)) {
    currentIndex_--;
    return true;
  }
  return false;
}

bool MarketData::reset() {
  if (isValidIndex(currentIndex_)) {
    currentIndex_ = 0;
    return true;
  }
  return false;
}

bool MarketData::setCurrentIndex(int index) {
  if (isValidIndex(index)) {
    currentIndex_ = index;
    return true;
  }
  return false;
}

bool MarketData::isLast() const {
  return !isValidIndex(currentIndex_ + 1);
}

std::vector<Bar> MarketData::getRange(int start, int end) const {
  if (!isValidIndex(start) || !isValidIndex(end) || start > end) {
    return {};
  }
  return std::vector<Bar>(bars_.begin() + start, bars_.begin() + end + 1);
}

int MarketData::findIndexByTimestamp(const std::string& timestamp) const {
  for (size_t i = 0; i < bars_.size(); ++i) {
    if (bars_[i].timestamp == timestamp) {
      return static_cast<int>(i);
    }
  }
  return -1;
}

std::vector<Bar> MarketData::getBetweenTimestamps(const std::string& start, const std::string& end) const {
  if (isValidIndex(findIndexByTimestamp(start)) &&
      isValidIndex(findIndexByTimestamp(end))) {
    int startIndex = findIndexByTimestamp(start);
    int endIndex = findIndexByTimestamp(end);
    return getRange(startIndex, endIndex);
  }
  return {};
}

bool MarketData::move(int offset) {
  int newIndex = currentIndex_ + offset;
  if (isValidIndex(newIndex)) {
    currentIndex_ = newIndex;
    return true;
  }
  return false;
}