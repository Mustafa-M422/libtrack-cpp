#include "app/LibraryService.hpp"
#include "infra/FileRepository.hpp"
#include "ui/ConsoleUI.hpp"
#include <iostream>

int main() {
  // Setup dependency injection
  infra::FileRepository repo("books.csv", "members.csv", "loans.csv");
  app::LibraryService service(repo);

  // User Interface
  ui::ConsoleUI consoleUI(service);
  consoleUI.run();

  return 0;
}
