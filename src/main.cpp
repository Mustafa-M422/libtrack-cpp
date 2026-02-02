#include "app/LibraryService.hpp"
#include "infra/FileRepository.hpp"
#include <iostream>
#include <limits>
#include <string>

// Simple helper to clear input buffer
void clearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
  // Setup dependency injection
  infra::FileRepository repo("books.csv", "members.csv", "loans.csv");
  app::LibraryService service(repo);

  // NOTE: Data is now loaded from CSV files automatically on startup!

  while (true) {
    std::cout << "\n=== LibTrack-CPP Manager ===\n";
    std::cout << "1. List All Books\n";
    std::cout << "2. Search Books\n";
    std::cout << "3. Add New Book\n";
    std::cout << "4. Register Member\n";
    std::cout << "5. Borrow Book\n";
    std::cout << "6. Return Book\n";
    std::cout << "0. Exit\n";
    std::cout << "Select option: ";

    int choice;
    if (!(std::cin >> choice)) {
      std::cout << "Invalid input. Please enter a number.\n";
      clearInput();
      continue;
    }

    if (choice == 0) {
      std::cout << "Goodbye!\n";
      break;
    }

    switch (choice) {
    case 1: {
      auto books = service.getAllBooks();
      std::cout << "\n--- Book List ---\n";
      if (books.empty())
        std::cout << "No books in library.\n";
      for (const auto &b : books) {
        std::cout << "[" << b.id << "] " << b.title << " by " << b.author
                  << (b.isBorrowed ? " (Borrowed)" : " (Available)") << "\n";
      }
      break;
    }
    case 2: {
      std::cout << "Enter search query: ";
      clearInput(); // Consume previous newline
      std::string query;
      std::getline(std::cin, query);
      auto results = service.searchBooks(query);
      std::cout << "\n--- Search Results ---\n";
      if (results.empty())
        std::cout << "No matches found.\n";
      for (const auto &b : results) {
        std::cout << "[" << b.id << "] " << b.title << " by " << b.author
                  << "\n";
      }
      break;
    }
    case 3: {
      int id;
      std::string title, author;
      std::cout << "Enter ID: ";
      std::cin >> id;
      clearInput();
      std::cout << "Enter Title: ";
      std::getline(std::cin, title);
      std::cout << "Enter Author: ";
      std::getline(std::cin, author);

      service.addBook(domain::Book(id, title, author));
      std::cout << "Book added successfully!\n";
      break;
    }
    case 4: {
      int id;
      std::string name;
      std::cout << "Enter Member ID: ";
      std::cin >> id;
      clearInput();
      std::cout << "Enter Name: ";
      std::getline(std::cin, name);

      service.registerMember(domain::Member(id, name));
      std::cout << "Member registered!\n";
      break;
    }
    case 5: { // Borrow Book
      int bookId, memberId;
      std::cout << "Enter Book ID: ";
      std::cin >> bookId;
      std::cout << "Enter Member ID: ";
      std::cin >> memberId;
      clearInput();

      if (service.borrowBook(bookId, memberId)) {
        std::cout << "Book borrowed successfully!\n";
      } else {
        std::cout << "Failed to borrow book. (Check if valid/available)\n";
      }
      break;
    }
    case 6: { // Return Book
      int bookId;
      std::cout << "Enter Book ID to Return: ";
      std::cin >> bookId;
      clearInput();

      if (service.returnBook(bookId)) {
        std::cout << "Book returned successfully!\n";
      } else {
        std::cout << "Failed to return book. (Check if valid/borrowed)\n";
      }
      break;
    }
    default:
      std::cout << "Unknown option.\n";
    }
  }

  return 0;
}
