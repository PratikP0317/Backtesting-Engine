#pragma once

#include <string>
#include <vector>

#include "Bar.h"

class MarketData {
public:
  // Load CSV into internal bar list
  bool loadFromCSV(const std::string &filepath);

  int size() const { return static_cast<int>(bars_.size());}
  bool isEmpty() const { return bars_.empty(); }
  void clear() { bars_.clear();  currentIndex_ = 0; }

  const Bar &get(int index) const;
  int getCurrentIndex() const { return currentIndex_; }
  const Bar &getFirst() const;
  const Bar &getLast() const;
  const std::vector<Bar> &getAll() const {return bars_;}

  const Bar &current() const;
  bool next();
  bool prev();
  bool reset();
  bool setCurrentIndex(int index);

  bool isLast() const;

  std::vector<Bar> getRange(int start, int end) const;
  int findIndexByTimestamp(const std::string& timestamp) const;
  std::vector<Bar> getBetweenTimestamps(const std::string& start, const std::string& end) const;

  bool move(int offset);

private:
  std::vector<Bar> bars_;
  int currentIndex_ = 0;

  bool isValidIndex(int index) const;
};