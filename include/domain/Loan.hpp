#pragma once

#include <ctime>

namespace domain {

    struct Loan {
        int bookId;
        int memberId;
        std::time_t loanDate;
        std::time_t dueDate;
        bool isActive;

        Loan() : bookId(0), memberId(0), loanDate(0), dueDate(0), isActive(false) {}
        Loan(int bId, int mId) : bookId(bId), memberId(mId), isActive(true) {
            loanDate = std::time(nullptr);
            // Default loan period: 14 days
            dueDate = loanDate + (14 * 24 * 60 * 60);
        }
    };

}
