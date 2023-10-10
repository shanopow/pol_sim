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

class Ideology{
    public:
    std::string name;
    int sens_progress=0;
    int sens_religion=0;
    int sens_equality=0;
    int sens_centralise=0;
    int sens_assimilation=0;
    int sens_military=0;    
    int sens_democracy=0;
    int sens_globalist=0;
    int sens_security=0;

    Ideology();
    Ideology(std::string name, int sens_progress, int sens_religion, int sens_equality, int sens_centralise, int sens_assimilation, int sens_military, int sens_democracy, int sens_globalist, int sens_security);
};

enum Position{
    government_lead,
    coalition_partner,
    opposition,
};

unsigned long mix(unsigned long a, unsigned long b, unsigned long c);

class Party{
    public:
    std::string name;
    std::vector<Member*> members;
    Ideology *ideology;  
    Position position = opposition;

    Party(std::string name, Ideology *ideology, int member_amount);
    void make_members(int member_amount);
    void show_members();
};

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