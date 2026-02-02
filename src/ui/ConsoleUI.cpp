#include "ui/ConsoleUI.hpp"
#include <iomanip>
#include <iostream>
#include <limits>


namespace ui {

ConsoleUI::ConsoleUI(app::LibraryService &srv) : service(srv) {}

void ConsoleUI::clearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ConsoleUI::waitForEnter() {
  std::cout << "\nPress Enter to return to menu...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}

void ConsoleUI::displayHeader() {
  // Simple "clear screen" by printing newlines to push content up
  std::cout << std::string(50, '\n');
  std::cout << "========================================\n";
  std::cout << "      LIBTRACK-CPP MANAGEMENT SYSTEM    \n";
  std::cout << "========================================\n";
}

void ConsoleUI::displayMenu() {
  std::cout << "\n[ MAIN MENU ]\n";
  std::cout << "1. List All Books\n";
  std::cout << "2. Search Books\n";
  std::cout << "3. Add New Book\n";
  std::cout << "4. Register Member\n";
  std::cout << "5. Borrow Book\n";
  std::cout << "6. Return Book\n";
  std::cout << "0. Exit\n";
  std::cout << "----------------------------------------\n";
  std::cout << "Select option: ";
}

void ConsoleUI::run() {
  while (true) {
    displayHeader();
    displayMenu();

    int choice;
    if (!(std::cin >> choice)) {
      std::cout << "Invalid input. Please enter a number.\n";
      clearInput();
      continue;
    }

    if (choice == 0) {
      std::cout << "\nGoodbye! Thank you for using LibTrack-CPP.\n";
      break;
    }

    switch (choice) {
    case 1:
      listBooks();
      break;
    case 2:
      searchBooks();
      break;
    case 3:
      addBook();
      break;
    case 4:
      registerMember();
      break;
    case 5:
      borrowBook();
      break;
    case 6:
      returnBook();
      break;
    default:
      std::cout << "Unknown option.\n";
      waitForEnter();
    }
  }
}

void ConsoleUI::listBooks() {
  auto books = service.getAllBooks();
  std::cout << "\n--- Book Inventory ---\n";
  std::cout << std::left << std::setw(5) << "ID" << std::setw(30) << "Title"
            << std::setw(20) << "Author"
            << "Status" << "\n";
  std::cout << std::string(65, '-') << "\n";

  if (books.empty()) {
    std::cout << "No books found in the library.\n";
  } else {
    for (const auto &b : books) {
      std::cout << std::left << std::setw(5) << b.id << std::setw(30)
                << b.title.substr(0, 29) << std::setw(20)
                << b.author.substr(0, 19)
                << (b.isBorrowed ? "[BORROWED]" : "[AVAILABLE]") << "\n";
    }
  }
  waitForEnter();
}

void ConsoleUI::searchBooks() {
  std::cout << "\nEnter search query: ";
  clearInput();
  std::string query;
  std::getline(std::cin, query);

  auto results = service.searchBooks(query);
  std::cout << "\n--- Search Results ---\n";
  if (results.empty()) {
    std::cout << "No matches found.\n";
  } else {
    for (const auto &b : results) {
      std::cout << "[" << b.id << "] " << b.title << " by " << b.author << "\n";
    }
  }
  waitForEnter();
}

void ConsoleUI::addBook() {
  int id;
  std::string title, author;

  std::cout << "\n--- Add New Book ---\n";
  std::cout << "Enter ID: ";
  while (!(std::cin >> id)) {
    std::cout << "Invalid ID. Try again: ";
    clearInput();
  }
  clearInput();

  std::cout << "Enter Title: ";
  std::getline(std::cin, title);

  std::cout << "Enter Author: ";
  std::getline(std::cin, author);

  service.addBook(domain::Book(id, title, author));
  std::cout << ">> Success: Book '" << title << "' added to library.\n";
  waitForEnter();
}

void ConsoleUI::registerMember() {
  int id;
  std::string name;

  std::cout << "\n--- Register Member ---\n";
  std::cout << "Enter Member ID: ";
  while (!(std::cin >> id)) {
    std::cout << "Invalid ID. Try again: ";
    clearInput();
  }
  clearInput();

  std::cout << "Enter Name: ";
  std::getline(std::cin, name);

  service.registerMember(domain::Member(id, name));
  std::cout << ">> Success: Member '" << name << "' registered.\n";
  waitForEnter();
}

void ConsoleUI::borrowBook() {
  int bookId, memberId;
  std::cout << "\n--- Borrow Book ---\n";
  std::cout << "Enter Book ID: ";
  std::cin >> bookId;
  std::cout << "Enter Member ID: ";
  std::cin >> memberId;
  clearInput();

  if (service.borrowBook(bookId, memberId)) {
    std::cout << ">> Success: Book borrowed successfully!\n";
  } else {
    std::cout << "!! Error: Failed to borrow book.\n";
    std::cout
        << "   (Check if Book ID exists, is available, and Member ID exists)\n";
  }
  waitForEnter();
}

void ConsoleUI::returnBook() {
  int bookId;
  std::cout << "\n--- Return Book ---\n";
  std::cout << "Enter Book ID to Return: ";
  std::cin >> bookId;
  clearInput();

  if (service.returnBook(bookId)) {
    std::cout << ">> Success: Book returned successfully!\n";
  } else {
    std::cout << "!! Error: Failed to return book.\n";
    std::cout << "   (Check if Book ID is valid and currently borrowed)\n";
  }
  waitForEnter();
}

} // namespace ui
