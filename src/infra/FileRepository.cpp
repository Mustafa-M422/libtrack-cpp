#include "infra/FileRepository.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace infra {

// --- Helpers ---
std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

// --- Book Persistence ---
void FileRepository::saveBooks(const std::vector<domain::Book> &books) {
  std::ofstream outFile(bookFile);
  if (!outFile) {
    std::cerr << "Error opening " << bookFile << " for writing.\n";
    return;
  }

  for (const auto &b : books) {
    // Format: id,title,author,isBorrowed
    outFile << b.id << "," << b.title << "," << b.author << ","
            << (b.isBorrowed ? 1 : 0) << "\n";
  }
}

std::vector<domain::Book> FileRepository::loadBooks() {
  std::vector<domain::Book> books;
  std::ifstream inFile(bookFile);
  if (!inFile)
    return books; // File might not exist yet

  std::string line;
  while (std::getline(inFile, line)) {
    if (line.empty())
      continue;
    auto parts = split(line, ',');
    if (parts.size() >= 4) {
      try {
        int id = std::stoi(parts[0]);
        std::string title = parts[1];
        std::string author = parts[2];
        bool borrowed = std::stoi(parts[3]) != 0;

        domain::Book b(id, title, author);
        b.isBorrowed = borrowed;
        books.push_back(b);
      } catch (...) {
        // Ignore malformed lines
      }
    }
  }
  return books;
}

// --- Member Persistence ---
void FileRepository::saveMembers(const std::vector<domain::Member> &members) {
  std::ofstream outFile(memberFile);
  if (!outFile)
    return;

  for (const auto &m : members) {
    // Format: id,name,loanId1;loanId2...
    outFile << m.id << "," << m.name << ",";

    for (size_t i = 0; i < m.activeLoanBookIds.size(); ++i) {
      outFile << m.activeLoanBookIds[i];
      if (i < m.activeLoanBookIds.size() - 1)
        outFile << ";";
    }
    outFile << "\n";
  }
}

std::vector<domain::Member> FileRepository::loadMembers() {
  std::vector<domain::Member> members;
  std::ifstream inFile(memberFile);
  if (!inFile)
    return members;

  std::string line;
  while (std::getline(inFile, line)) {
    if (line.empty())
      continue;
    auto parts = split(line, ',');
    if (parts.size() >= 2) {
      try {
        int id = std::stoi(parts[0]);
        std::string name = parts[1];
        domain::Member m(id, name);

        if (parts.size() > 2 && !parts[2].empty()) {
          auto loanIds = split(parts[2], ';');
          for (const auto &lId : loanIds) {
            if (!lId.empty())
              m.activeLoanBookIds.push_back(std::stoi(lId));
          }
        }
        members.push_back(m);
      } catch (...) {
      }
    }
  }
  return members;
}

// --- Loan Persistence ---
void FileRepository::saveLoans(const std::vector<domain::Loan> &loans) {
  std::ofstream outFile(loanFile);
  if (!outFile)
    return;

  for (const auto &l : loans) {
    // Format: bookId,memberId,isActive
    outFile << l.bookId << "," << l.memberId << "," << (l.isActive ? 1 : 0)
            << "\n";
  }
}

std::vector<domain::Loan> FileRepository::loadLoans() {
  std::vector<domain::Loan> loans;
  std::ifstream inFile(loanFile);
  if (!inFile)
    return loans;

  std::string line;
  while (std::getline(inFile, line)) {
    if (line.empty())
      continue;
    auto parts = split(line, ',');
    if (parts.size() >= 3) {
      try {
        int bookId = std::stoi(parts[0]);
        int memberId = std::stoi(parts[1]);
        bool active = std::stoi(parts[2]) != 0;

        domain::Loan l(bookId, memberId);
        l.isActive = active;
        loans.push_back(l);
      } catch (...) {
      }
    }
  }
  return loans;
}

} // namespace infra
