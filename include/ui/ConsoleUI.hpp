#pragma once

#include "app/LibraryService.hpp"

namespace ui {

class ConsoleUI {
private:
  app::LibraryService &service;

  void displayHeader();
  void displayMenu();
  void clearInput();
  void waitForEnter();

  // Actions
  void listBooks();
  void searchBooks();
  void addBook();
  void registerMember();
  void borrowBook();
  void returnBook();

public:
  explicit ConsoleUI(app::LibraryService &srv);
  void run();
};

} // namespace ui
