#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

namespace domain {
struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    int publicationYear;
    int totalCopies;
    int availableCopies;
};
}

#endif // BOOK_HPP
