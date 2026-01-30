#include "infra/BookRepository.hpp"
#include "infra/CsvUtils.hpp"
#include <fstream>
#include <iostream>

namespace infra {

BookRepository::BookRepository(const std::string& filename) : filename(filename) {}

std::vector<domain::Book> BookRepository::load() {
    std::vector<domain::Book> books;
    std::ifstream file(filename);
    if (!file.is_open()) return books; // Return empty if no file

    std::string line;
    // Skip header
    if (std::getline(file, line)) {
        // Validation of header could go here
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = CsvUtils::parseLine(line);
        if (tokens.size() >= 6) {
            domain::Book b;
            b.isbn = tokens[0];
            b.title = tokens[1];
            b.author = tokens[2];
            try {
                b.publicationYear = std::stoi(tokens[3]);
                b.totalCopies = std::stoi(tokens[4]);
                b.availableCopies = std::stoi(tokens[5]);
                books.push_back(b);
            } catch (...) {
                // Log error or skip malformed line
                std::cerr << "Skipping malformed line in books.csv: " << line << "\n";
            }
        }
    }
    return books;
}

void BookRepository::save(const std::vector<domain::Book>& books) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    // Write Header
    file << "isbn,title,author,publicationYear,totalCopies,availableCopies\n";

    for (const auto& b : books) {
        file << CsvUtils::escape(b.isbn) << ","
             << CsvUtils::escape(b.title) << ","
             << CsvUtils::escape(b.author) << ","
             << b.publicationYear << ","
             << b.totalCopies << ","
             << b.availableCopies << "\n";
    }
}

} // namespace infra
