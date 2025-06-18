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
  void clear() { bars_.clear();  current_index_ = 0; }

  const Bar &get(int index) const;
  const Bar &getFirst() const;
  const Bar &getLast() const;
  const Bar &getCurrent() const;

  const std::vector<Bar> &getAll() const {return bars_;}

  // Peek at current bar without advancing
  const Bar& current() const;
private:
  std::vector<Bar> bars_;
  int current_index_ = 0;
};