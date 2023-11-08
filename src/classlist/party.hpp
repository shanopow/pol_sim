#ifndef PARTY_HPP
#define PARTY_HPP

#include "member.hpp"
#include "ideology.hpp"
#include "baseclass.hpp"
#include <iostream>

enum Position{
    government_lead,
    coalition_partner,
    opposition,
};

class Ideology;
class Member;

class Party : public Base{
    public:
    std::string name;
    std::vector<Member*> members;
    Ideology *main_ideology;  
    Position position = opposition;
    int last_result=0;

    Party(std::string name, Ideology *main_ideology, int member_amount);
    void make_members(int member_amount);
    void show_members();
};

#endif