#pragma once

#include <string>
#include <vector>

namespace domain {

    struct Member {
        int id;
        std::string name;

        // In a real DB we wouldn't store full loan objects here, maybe just IDs.
        // But for this simple in-memory/file struct, keeping track of active loan IDs is useful.
        std::vector<int> activeLoanBookIds; 

        Member() : id(0) {}
        Member(int id, std::string n) : id(id), name(std::move(n)) {}
    };

}
