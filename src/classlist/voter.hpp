#ifndef VOTER_HPP
#define VOTER_HPP

#include "ideology.hpp"
#include "party.hpp"
#include <unordered_map>

class Ideology;
class Party;

class Voter{
    public:
    bool voted;
    Ideology *belief;
    Party *prev_voted = NULL;
    Voter(Ideology *belief);
    void show_belief();
    void vote();
    void show_attitudes(std::vector<Voter*> voters);
};

#endif