#pragma once

#include <string>

struct Bar {
  std::string symbol;
  std::string timestamp;
  double open;
  double high;
  double low;
  double close;
  long volume;
  long tradeCount;
  double vwap;
};
