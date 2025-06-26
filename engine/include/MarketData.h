#pragma once

#include <string>
#include <vector>

#include "Bar.h"

class MarketData {
public:
  // Iterator type aliases for STL compatibility
  using iterator = std::vector<Bar>::iterator;
  using const_iterator = std::vector<Bar>::const_iterator;

  MarketData(const std::string &csvFilePath);

  // Load CSV into internal bar list
  bool loadFromCSV(const std::string &filepath);

  int size() const;
  bool isEmpty() const;
  void clear();
  
  // STL-style iterator access
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  const Bar &get(int index) const;
  int getCurrentIndex() const;
  const Bar &getFirst() const;
  const Bar &getLast() const;
  const std::vector<Bar> &getAll() const;

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
  const_iterator currentIter_;

  bool isValidIndex(int index) const;
};