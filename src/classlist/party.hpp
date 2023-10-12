#ifndef PARTY_HPP
#define PARTY_HPP

#include <string>
#include <vector>
#include <iostream>

enum Position{
    government_lead,
    coalition_partner,
    opposition,
};

class Party{
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