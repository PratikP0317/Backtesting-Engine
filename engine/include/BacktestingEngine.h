#pragma once

#include <string>
#include "MarketData.h"

class BacktestEngine {
public:
  BacktestEngine(double startingCash);

  bool loadData(const std::string& filepath);
  void run();
  void printSummary() const;

private:
  MarketData data_;
  double cash_;
  double position_;   
  double entryPrice_;
  bool inPosition_;

  void onBar(const Bar& bar);  
};
