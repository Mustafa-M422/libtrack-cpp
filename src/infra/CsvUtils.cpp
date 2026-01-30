#include "infra/CsvUtils.hpp"

namespace infra {

std::vector<std::string> CsvUtils::parseLine(const std::string& line) {
    std::vector<std::string> result;
    std::string current;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                current += '"'; // Escaped quote
                ++i;
            } else {
                inQuotes = !inQuotes; // Toggle State
            }
        } else if (c == ',' && !inQuotes) {
            result.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    result.push_back(current);
    return result;
}

std::string CsvUtils::escape(const std::string& text) {
    bool needsQuotes = false;
    std::string result;
    result.reserve(text.size() + 2);

    for (char c : text) {
        if (c == '"') {
            needsQuotes = true;
            result += "\"\""; // Double quote escape
        } else {
            if (c == ',') needsQuotes = true;
            result += c;
        }
    }

    if (needsQuotes) {
        return "\"" + result + "\"";
    }
    return text;
}

} // namespace infra
