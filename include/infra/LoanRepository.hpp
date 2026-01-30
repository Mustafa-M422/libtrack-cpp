#ifndef LOAN_REPOSITORY_HPP
#define LOAN_REPOSITORY_HPP

#include "domain/Loan.hpp"
#include <vector>
#include <string>

namespace infra {

class LoanRepository {
public:
    explicit LoanRepository(const std::string& filename);
    std::vector<domain::Loan> load();
    void save(const std::vector<domain::Loan>& loans);

private:
    std::string filename;
};

} // namespace infra

#endif // LOAN_REPOSITORY_HPP
