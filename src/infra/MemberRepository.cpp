#include "infra/MemberRepository.hpp"
#include "infra/CsvUtils.hpp"
#include <fstream>
#include <iostream>

namespace infra {

MemberRepository::MemberRepository(const std::string& filename) : filename(filename) {}

std::vector<domain::Member> MemberRepository::load() {
    std::vector<domain::Member> members;
    std::ifstream file(filename);
    if (!file.is_open()) return members;

    std::string line;
    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = CsvUtils::parseLine(line);
        if (tokens.size() >= 2) {
            domain::Member m;
            m.id = tokens[0];
            m.name = tokens[1];
            members.push_back(m);
        }
    }
    return members;
}

void MemberRepository::save(const std::vector<domain::Member>& members) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "id,name\n";
    for (const auto& m : members) {
        file << CsvUtils::escape(m.id) << ","
             << CsvUtils::escape(m.name) << "\n";
    }
}

} // namespace infra
