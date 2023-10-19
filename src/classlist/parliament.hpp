#ifndef PARLIAMENT_HPP
#define PARLIAMENT_HPP

#include "party.hpp"
#include "voter.hpp"
#include "election_events.hpp"
#include <set>
#include <random>
#include <map>
#include <algorithm>

unsigned long mix(unsigned long a, unsigned long b, unsigned long c);

class Party;
class Ideology;

class Parliament{
    public:
    int seat_number;
    int day_till_election=0;
    bool in_session=false;
    Party * in_power;
    std::vector<Party*> parties;
    std::unordered_map<std::string, int> tally;

    Parliament(int seat_number, Party *in_power, std::vector<Party*> parties);
    void set_tally();
    void show_parliament();
    void show_votes(float turnout);
    void election_cleanup();
    void parliament_shuffler(int turnout);
    void election_events();
    void hold_election(std::vector<Voter*> voters, std::vector<Ideology*> ideologies);
};

#endif 