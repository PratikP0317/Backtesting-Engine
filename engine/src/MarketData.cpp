#include <fstream>  
#include <sstream>
#include <stdexcept>  
#include <string>
#include <vector>
#include <algorithm>

#include "MarketData.h"
#include "Log.h"

MarketData::MarketData() : currentIter_(bars_.cend()) {
}

MarketData::MarketData(const std::string &csvFilePath) : currentIter_(bars_.cend()) {
  if (!loadFromCSV(csvFilePath)) {
    throw std::runtime_error("Failed to load CSV file: " + csvFilePath);
  }
}


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
      Log::error("Failed to parse line " + std::to_string(lineNumber) + ": " + e.what());
      return false;
    }
    bars_.push_back(bar);
  }  Log::info("Successfully loaded " + std::to_string(bars_.size()) + " bars from " + filepath);
  file.close();
  if (!bars_.empty()) {
    currentIter_ = bars_.cbegin();  // Reset to first bar
  }
  return true;
}

int MarketData::size() const {
  return static_cast<int>(bars_.size());
}

bool MarketData::isEmpty() const {
  return bars_.empty();
}

void MarketData::clear() {
  bars_.clear();
  currentIter_ = bars_.cend();
}

// STL-style iterator methods
MarketData::iterator MarketData::begin() {
  return bars_.begin();
}

MarketData::iterator MarketData::end() {
  return bars_.end();
}

MarketData::const_iterator MarketData::begin() const {
  return bars_.begin();
}

MarketData::const_iterator MarketData::end() const {
  return bars_.end();
}

MarketData::const_iterator MarketData::cbegin() const {
  return bars_.cbegin();
}

MarketData::const_iterator MarketData::cend() const {
  return bars_.cend();
}

bool MarketData::isValidIterator(const_iterator iter) const {
  return iter >= bars_.cbegin() && iter < bars_.cend();
}

const Bar& MarketData::current() const {
  if (isEmpty()) {
    throw std::out_of_range("No bars available in MarketData::current");
  }
  if (!isValidIterator(currentIter_)) {
    throw std::out_of_range("currentIter_ out of range in MarketData::current");
  }
  return *currentIter_;
}

bool MarketData::next() {
  if (isValidIterator(currentIter_) && (currentIter_ + 1) != bars_.cend()) {
    currentIter_++;
    return true;
  }
  return false;
}

bool MarketData::prev() {
  if (isValidIterator(currentIter_) && currentIter_ != bars_.cbegin()) {
    currentIter_--;
    return true;
  }
  return false;
}

bool MarketData::reset() {
  if (!isEmpty()) {
    currentIter_ = bars_.cbegin();
    return true;
  }
  return false;
}

bool MarketData::findByTimestamp(const_iterator &itr, const std::string& timestamp) const {
  if (isEmpty()) {
    return false;
  }

  const_iterator saveIter = itr;
  itr = std::find_if(bars_.cbegin(), bars_.cend(),
                     [&timestamp](const Bar& bar) { return bar.timestamp == timestamp; });

  if (isValidIterator(itr)) {
    Log::info("Found bar with timestamp: " + timestamp);
    return true;
  }
  itr = saveIter; 
  return false;
}

bool MarketData::seek(const_iterator &itr, int offset, const SeekMode &mode) {
  if (isEmpty()) {
    return false;
  }

  const_iterator saveIter = itr;
  switch (mode) {
    case SeekMode::CURRENT:
      itr = bars_.cbegin() + offset;
      break;
    case SeekMode::BEGIN:
      itr = bars_.cbegin() + offset;
      break;
    case SeekMode::END:
      itr = bars_.cend() + offset - 1;
      break;
  }

  // Validate the iterator after seeking
  if (!isValidIterator(itr)) {
    itr = saveIter; 
  }
  Log::info("Seeked iterator to position: " + std::to_string(std::distance(bars_.cbegin(), itr)));
  return true;
}