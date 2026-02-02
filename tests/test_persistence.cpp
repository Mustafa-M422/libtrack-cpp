#include "infra/FileRepository.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>


void testBooks() {
  std::cout << "Testing Book Persistence...\n";
  infra::FileRepository repo("test_books.csv", "test_members.csv",
                             "test_loans.csv");

  std::vector<domain::Book> books;
  books.emplace_back(1, "Book One", "Author A");
  books.emplace_back(2, "Book Two", "Author B");
  books[1].isBorrowed = true;

  repo.saveBooks(books);

  auto loadedBooks = repo.loadBooks();
  assert(loadedBooks.size() == 2);
  assert(loadedBooks[0].title == "Book One");
  assert(loadedBooks[1].isBorrowed == true);
  std::cout << "Books Passed!\n";
}

void testMembers() {
  std::cout << "Testing Member Persistence...\n";
  infra::FileRepository repo("test_books.csv", "test_members.csv",
                             "test_loans.csv");

  std::vector<domain::Member> members;
  members.emplace_back(1, "Alice");
  members[0].activeLoanBookIds = {101, 102};

  repo.saveMembers(members);

  auto loadedMembers = repo.loadMembers();
  assert(loadedMembers.size() == 1);
  assert(loadedMembers[0].name == "Alice");
  assert(loadedMembers[0].activeLoanBookIds.size() == 2);
  assert(loadedMembers[0].activeLoanBookIds[1] == 102);
  std::cout << "Members Passed!\n";
}

int main() {
  testBooks();
  testMembers();

  // Cleanup
  std::remove("test_books.csv");
  std::remove("test_members.csv");
  std::remove("test_loans.csv");

  std::cout << "All persistence tests passed!\n";
  return 0;
}
