#ifndef BOOK_REPOSITORY_HPP
#define BOOK_REPOSITORY_HPP

#include "domain/Book.hpp"
#include <vector>
#include <string>

namespace infra {

class BookRepository {
public:
    explicit BookRepository(const std::string& filename);
    std::vector<domain::Book> load();
    void save(const std::vector<domain::Book>& books);

private:
    std::string filename;
};

} // namespace infra

#endif // BOOK_REPOSITORY_HPP
