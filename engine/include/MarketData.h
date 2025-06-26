#pragma once

#include <string>
#include <vector>

#include "Bar.h"

class MarketData {
public:
  // Iterator type aliases for STL compatibility
  using iterator = std::vector<Bar>::iterator;
  using const_iterator = std::vector<Bar>::const_iterator;

  enum class SeekMode{
    CURRENT,
    BEGIN,
    END 
  };

  MarketData();
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

  const Bar &current() const;
  bool next();
  bool prev();
  bool reset();

  bool findByTimestamp(const_iterator &itr, const std::string& timestamp) const;
  bool seek(const_iterator &itr, int offset, const SeekMode &mode);


  bool isValidIterator(const_iterator iter) const;

private:
  std::vector<Bar> bars_;
  const_iterator currentIter_;
};