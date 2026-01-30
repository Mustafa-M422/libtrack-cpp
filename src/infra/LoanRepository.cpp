#include "infra/LoanRepository.hpp"
#include "infra/CsvUtils.hpp"
#include <fstream>
#include <iostream>

namespace infra {

LoanRepository::LoanRepository(const std::string& filename) : filename(filename) {}

std::vector<domain::Loan> LoanRepository::load() {
    std::vector<domain::Loan> loans;
    std::ifstream file(filename);
    if (!file.is_open()) return loans;

    std::string line;
    std::getline(file, line); // header

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = CsvUtils::parseLine(line);
        if (tokens.size() >= 6) {
            domain::Loan l;
            l.id = tokens[0];
            l.bookIsbn = tokens[1];
            l.memberId = tokens[2];
            try {
                l.borrowDate = std::stoll(tokens[3]);
                l.dueDate = std::stoll(tokens[4]);
                l.returnDate = std::stoll(tokens[5]);
                loans.push_back(l);
            } catch (...) {
                continue;
            }
        }
    }
    return loans;
}

void LoanRepository::save(const std::vector<domain::Loan>& loans) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "id,bookIsbn,memberId,borrowDate,dueDate,returnDate\n";
    for (const auto& l : loans) {
        file << CsvUtils::escape(l.id) << ","
             << CsvUtils::escape(l.bookIsbn) << ","
             << CsvUtils::escape(l.memberId) << ","
             << l.borrowDate << ","
             << l.dueDate << ","
             << l.returnDate << "\n";
    }
}

} // namespace infra
