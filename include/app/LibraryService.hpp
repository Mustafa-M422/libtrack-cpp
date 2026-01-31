#pragma once

#include "domain/Book.hpp"
#include "domain/Member.hpp"
#include "domain/Loan.hpp"
#include <vector>
#include <string>
#include <optional>

namespace app {

    class LibraryService {
    private:
        // In-memory storage for now (will be replaced by Repository later)
        std::vector<domain::Book> books;
        std::vector<domain::Member> members;
        std::vector<domain::Loan> loans;

        // Helpers
        domain::Book* findBookById(int id);
        domain::Member* findMemberById(int id);
        domain::Loan* findActiveLoanForBook(int bookId);

    public:
        LibraryService() = default;

        // Book Management
        void addBook(const domain::Book& book);
        std::vector<domain::Book> searchBooks(const std::string& query) const;
        std::vector<domain::Book> getAllBooks() const;

        // Member Management
        void registerMember(const domain::Member& member);
        domain::Member* getMember(int id);

        // Loan Logic
        bool borrowBook(int bookId, int memberId);
        bool returnBook(int bookId);
    };

}
