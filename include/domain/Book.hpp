#pragma once

#include <string>
#include <iostream>

namespace domain {

    struct Book {
        int id;
        std::string title;
        std::string author;
        bool isBorrowed;

        Book() : id(0), isBorrowed(false) {}
        Book(int id, std::string t, std::string a) 
            : id(id), title(std::move(t)), author(std::move(a)), isBorrowed(false) {}
    };

}
