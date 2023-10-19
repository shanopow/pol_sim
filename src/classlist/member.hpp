#ifndef MEMBER_HPP
#define MEMBER_HPP

#include "trait.hpp"

class Trait;

class Member{
    public:
    int loyalty;
    int popularity;
    int competency;
    std::string name;
    int age=0;

    std::vector<Trait> general_traits;
    Member(std::string name);

    //void setTraits();
};

#endif