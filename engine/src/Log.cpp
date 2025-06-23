#include "Log.h"
#include <iostream>
#include <ctime>
#include <filesystem>  // C++17

std::ofstream Log::log_file_;
bool Log::file_logging_enabled_ = false;
std::mutex Log::log_mutex_;

void Log::init(const std::string& filename) {
  std::lock_guard<std::mutex> lock(log_mutex_);
  std::filesystem::create_directory("logs");
  std::string full_path = "logs/" + filename;

  log_file_.open(full_path, std::ios::out | std::ios::app);
  file_logging_enabled_ = log_file_.is_open();

  if (!file_logging_enabled_) {
    std::cerr << "[error] Failed to open log file: " << full_path << std::endl;
  }
}

void Log::close() {
  std::lock_guard<std::mutex> lock(log_mutex_);
  if (log_file_.is_open()) {
    log_file_.close();
  }
}

std::string Log::timestamp() {
  std::time_t now = std::time(nullptr);
  char buf[32];
  std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
  return std::string(buf);
}

void Log::debug(const std::string& msg) {
  std::lock_guard<std::mutex> lock(log_mutex_);
  std::string formatted = "[Debug] " + timestamp() + " - " + msg;
  std::cout << formatted << std::endl;
  if (file_logging_enabled_) log_file_ << formatted << std::endl;
}

void Log::info(const std::string& msg) {
  std::lock_guard<std::mutex> lock(log_mutex_);
  std::string formatted = "[Info] " + timestamp() + " - " + msg;
  std::cout << formatted << std::endl;
  if (file_logging_enabled_) log_file_ << formatted << std::endl;
}

void Log::warn(const std::string& msg) {
  std::lock_guard<std::mutex> lock(log_mutex_);
  std::string formatted = "[Warn] " + timestamp() + " - " + msg;
  std::cout << formatted << std::endl;
  if (file_logging_enabled_) log_file_ << formatted << std::endl;
}

void Log::error(const std::string& msg) {
  std::lock_guard<std::mutex> lock(log_mutex_);
  std::string formatted = "[ERROR] " + timestamp() + " - " + msg;
  std::cerr << formatted << std::endl;
  if (file_logging_enabled_) log_file_ << formatted << std::endl;
}
