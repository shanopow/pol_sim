#ifndef GOVHANDLER_HPP
#define GOVHANDLER_HPP

#include <bits/stdc++.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <iostream>

#include <vector>
#include <unordered_map>
#include <map>

#include "people.hpp"

unsigned long mix(unsigned long a, unsigned long b, unsigned long c);


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