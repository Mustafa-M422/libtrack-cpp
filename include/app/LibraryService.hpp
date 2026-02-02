#pragma once

#include "domain/Book.hpp"
#include "domain/Loan.hpp"
#include "domain/Member.hpp"
#include "infra/IRepository.hpp"
#include <optional>
#include <string>
#include <vector>


namespace app {

class LibraryService {
private:
  infra::IRepository &repo;

  // In-memory storage (synced with simple repo)
  std::vector<domain::Book> books;
  std::vector<domain::Member> members;
  std::vector<domain::Loan> loans;

  // Helpers
  domain::Book *findBookById(int id);
  domain::Member *findMemberById(int id);
  domain::Loan *findActiveLoanForBook(int bookId);

public:
  explicit LibraryService(infra::IRepository &r);

  // Book Management
  void addBook(const domain::Book &book);
  std::vector<domain::Book> searchBooks(const std::string &query) const;
  std::vector<domain::Book> getAllBooks() const;

  // Member Management
  void registerMember(const domain::Member &member);
  domain::Member *getMember(int id);

  // Loan Logic
  bool borrowBook(int bookId, int memberId);
  bool returnBook(int bookId);
};

} // namespace app
