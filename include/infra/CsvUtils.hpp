#ifndef CSV_UTILS_HPP
#define CSV_UTILS_HPP

#include <vector>
#include <string>
#include <sstream>

namespace infra {

class CsvUtils {
public:
    // Parses a CSV line into a vector of strings, handling quotes.
    static std::vector<std::string> parseLine(const std::string& line);

    // Escapes text for CSV (wraps in quotes if contains comma/quote).
    static std::string escape(const std::string& text);
};

} // namespace infra

#endif // CSV_UTILS_HPP
