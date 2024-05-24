#include "utils/Helper.h"

#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <ctime>

namespace fs = std::filesystem;

std::string get_current_time_str() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time);
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}

void log_results(const std::vector<int>& vector, double elapsed_time, double performance, double recovery, double grade) {
    // Create a new log folder with current timestamp
    std::string timestamp = get_current_time_str();
    fs::path log_dir = fs::path("../log") / timestamp;
    fs::create_directories(log_dir);
    std::ofstream log_file(log_dir / "circuit_info.log");

    // Log the results
    log_file << "Elapsed time: " << elapsed_time << " seconds" << std::endl;
    log_file << "Performance: " << performance << std::endl;
    log_file << "Recovery: " << recovery << std::endl;
    log_file << "Grade: " << grade << std::endl;
    log_file << "Final Circuit Configuration: ";
    for (const auto& v : vector) {
        log_file << v << " ";
    }
    log_file << std::endl;

    // Close log file
    log_file.close();
}
