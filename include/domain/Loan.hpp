#ifndef LOAN_HPP
#define LOAN_HPP

#include <string>
#include <ctime>

namespace domain {
struct Loan {
    std::string id;
    std::string bookIsbn;
    std::string memberId;
    std::time_t borrowDate;
    std::time_t dueDate;
    std::time_t returnDate; // 0 if not returned
};
}

#endif // LOAN_HPP
