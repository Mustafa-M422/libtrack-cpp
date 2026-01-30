#ifndef DATE_UTILS_HPP
#define DATE_UTILS_HPP

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

namespace utils {

inline std::time_t getCurrentTime() {
    return std::time(nullptr);
}

inline std::string formatDate(std::time_t t) {
    if (t == 0) return "N/A";
    std::tm tm_buf{};
#ifdef _WIN32
    localtime_s(&tm_buf, &t);
#else
    localtime_r(&t, &tm_buf);
#endif
    std::stringstream ss;
    ss << std::put_time(&tm_buf, "%Y-%m-%d");
    return ss.str();
}

inline std::time_t addDays(std::time_t t, int days) {
    return t + (days * 24 * 60 * 60);
}

inline int getDaysDifference(std::time_t start, std::time_t end) {
    double diff = std::difftime(end, start);
    return static_cast<int>(diff / (24 * 60 * 60));
}

} // namespace utils

#endif // DATE_UTILS_HPP
