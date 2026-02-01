#pragma once

#include "infra/IRepository.hpp"
#include <string>

namespace infra {

    class FileRepository : public IRepository {
    private:
        std::string bookFile;
        std::string memberFile;
        std::string loanFile;

    public:
        FileRepository(std::string bFile, std::string mFile, std::string lFile)
            : bookFile(std::move(bFile)), memberFile(std::move(mFile)), loanFile(std::move(lFile)) {}

        // Implementation stubs for now
        void saveBooks(const std::vector<domain::Book>& books) override;
        std::vector<domain::Book> loadBooks() override;

        void saveMembers(const std::vector<domain::Member>& members) override;
        std::vector<domain::Member> loadMembers() override;

        void saveLoans(const std::vector<domain::Loan>& loans) override;
        std::vector<domain::Loan> loadLoans() override;
    };

}
