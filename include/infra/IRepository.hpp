#pragma once

#include "domain/Book.hpp"
#include "domain/Member.hpp"
#include "domain/Loan.hpp"
#include <vector>

namespace infra {

    class IRepository {
    public:
        virtual ~IRepository() = default;

        // Book persistence
        virtual void saveBooks(const std::vector<domain::Book>& books) = 0;
        virtual std::vector<domain::Book> loadBooks() = 0;

        // Member persistence
        virtual void saveMembers(const std::vector<domain::Member>& members) = 0;
        virtual std::vector<domain::Member> loadMembers() = 0;

        // Loan persistence
        virtual void saveLoans(const std::vector<domain::Loan>& loans) = 0;
        virtual std::vector<domain::Loan> loadLoans() = 0;
    };

}
