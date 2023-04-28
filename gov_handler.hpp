#include "stdlib.h"
#include "time.h"

#include <bits/stdc++.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

// traits are used by members
class Trait{
    public:
    std::string desc;
    int magnitude; // how much this changes
    std::string style; // which style of trait this is;
    int cost; // how many points it costs to take this trait

    // constructor
    Trait(std::string desc, int magnitude, std::string style, int cost);    
    //setters
    void setDesc(std::string desc);

    void setMagnitude(int magnitude);

    void setStyle(std::string style);

    void setCost(int cost);
};

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

// party position in parliament
enum Position{
        government_lead,
        coalition_partner,
        opposition,
    };

// generic rand scrambler (for seeding)
unsigned long mix(unsigned long a, unsigned long b, unsigned long c);

class Member{
    public:

    int loyalty;
    int popularity;
    int competency;
    std::string name;
    int age=0;
    
    Member(std::string name);

    void setTraits();
};

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
    Voter(Ideology *belief);

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
    // setters    
    void set_tally();

    //showers
    void show_parliament();
    
    struct comp {
        template <typename T>
 
        // Comparator function
        bool operator()(const T& l, const T& r) const{
            if (l.second != r.second) {
                return l.second > r.second;
            }
            return l.first > r.first;
        }
    };   
    
    void show_votes(float turnout);

    // removes empty parties with no members
    void election_cleanup();
    
    // adjust members based on their percentage of votes
    void parliament_shuffler(int turnout);

    // generates events during an election
    void election_events();

    // main election runner
    void hold_election(std::vector<Voter*> voters, std::vector<Ideology*> ideologies);

};