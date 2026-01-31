#include "app/LibraryService.hpp"
#include <algorithm>
#include <iostream>

namespace app {

    // --- Helpers ---
    domain::Book* LibraryService::findBookById(int id) {
        for (auto& b : books) {
            if (b.id == id) return &b;
        }
        return nullptr;
    }

    domain::Member* LibraryService::findMemberById(int id) {
        for (auto& m : members) {
            if (m.id == id) return &m;
        }
        return nullptr;
    }

    domain::Loan* LibraryService::findActiveLoanForBook(int bookId) {
        for (auto& l : loans) {
            if (l.bookId == bookId && l.isActive) {
                return &l;
            }
        }
        return nullptr;
    }

    // --- Book Management ---
    void LibraryService::addBook(const domain::Book& book) {
        // In a real app, check for duplicate IDs
        books.push_back(book);
    }

    std::vector<domain::Book> LibraryService::searchBooks(const std::string& query) const {
        std::vector<domain::Book> result;
        // Simple substring search (case-sensitive for now for simplicity)
        for (const auto& b : books) {
            if (b.title.find(query) != std::string::npos || 
                b.author.find(query) != std::string::npos) {
                result.push_back(b);
            }
        }
        return result;
    }

    std::vector<domain::Book> LibraryService::getAllBooks() const {
        return books;
    }

    // --- Member Management ---
    void LibraryService::registerMember(const domain::Member& member) {
        members.push_back(member);
    }

    domain::Member* LibraryService::getMember(int id) {
        return findMemberById(id);
    }

    // --- Loan Logic ---
    bool LibraryService::borrowBook(int bookId, int memberId) {
        domain::Book* book = findBookById(bookId);
        domain::Member* member = findMemberById(memberId);

        if (!book || !member) {
            return false; // Book or Member not found
        }

        if (book->isBorrowed) {
            return false; // Already borrowed
        }

        // Create Loan
        domain::Loan newLoan(bookId, memberId);
        loans.push_back(newLoan);

        // Update Book Status
        book->isBorrowed = true;
        
        // Update Member
        member->activeLoanBookIds.push_back(bookId);

        return true;
    }

    bool LibraryService::returnBook(int bookId) {
        domain::Book* book = findBookById(bookId);
        domain::Loan* loan = findActiveLoanForBook(bookId);

        if (!book || !loan) {
            return false; // Not borrowed or not found
        }

        // Close Loan
        loan->isActive = false;

        // Update Book Status
        book->isBorrowed = false;

        // Update Member (remove from active loans)
        // We need to find which member had it, usually stored in loan
        domain::Member* member = findMemberById(loan->memberId);
        if (member) {
            auto& ids = member->activeLoanBookIds;
            ids.erase(std::remove(ids.begin(), ids.end(), bookId), ids.end());
        }

        return true;
    }

}
