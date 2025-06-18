#pragma once

#include <string>
#include <fstream>
#include <mutex>

class Log {
public:
    static void init(const std::string& filename);
    static void close();

    static void debug(const std::string& msg);
    static void info(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);

private:
    static std::ofstream log_file_;
    static bool file_logging_enabled_;
    static std::mutex log_mutex_;

    static std::string timestamp();
};
