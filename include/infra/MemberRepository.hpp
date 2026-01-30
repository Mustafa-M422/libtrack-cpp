#ifndef MEMBER_REPOSITORY_HPP
#define MEMBER_REPOSITORY_HPP

#include "domain/Member.hpp"
#include <vector>
#include <string>

namespace infra {

class MemberRepository {
public:
    explicit MemberRepository(const std::string& filename);
    std::vector<domain::Member> load();
    void save(const std::vector<domain::Member>& members);

private:
    std::string filename;
};

} // namespace infra

#endif // MEMBER_REPOSITORY_HPP
