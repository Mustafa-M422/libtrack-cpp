#include "infra/FileRepository.hpp"
#include <iostream>

namespace infra {

    // --- Book Persistence ---
    void FileRepository::saveBooks(const std::vector<domain::Book>& books) {
        // TODO: Implement JSON/CSV saving
        (void)books; // Suppress unused warning
        std::cout << "[FileRepository] Stub: Saving books to " << bookFile << std::endl;
    }

    std::vector<domain::Book> FileRepository::loadBooks() {
        // TODO: Implement loading
        std::cout << "[FileRepository] Stub: Loading books from " << bookFile << std::endl;
        return {}; 
    }

    // --- Member Persistence ---
    void FileRepository::saveMembers(const std::vector<domain::Member>& members) {
        (void)members;
        std::cout << "[FileRepository] Stub: Saving members to " << memberFile << std::endl;
    }

    std::vector<domain::Member> FileRepository::loadMembers() {
        std::cout << "[FileRepository] Stub: Loading members from " << memberFile << std::endl;
        return {};
    }

    // --- Loan Persistence ---
    void FileRepository::saveLoans(const std::vector<domain::Loan>& loans) {
        (void)loans;
        std::cout << "[FileRepository] Stub: Saving loans to " << loanFile << std::endl;
    }

    std::vector<domain::Loan> FileRepository::loadLoans() {
        std::cout << "[FileRepository] Stub: Loading loans from " << loanFile << std::endl;
        return {};
    }

}
