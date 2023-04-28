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

#include "election_events.hpp"

// traits are used by members
class Trait{
    public:
    
    std::string desc;
    int magnitude; // how much this changes
    std::string style; // which style of trait this is;
    int cost; // how many points it costs to take this trait

    // constructor
    Trait(std::string desc, int magnitude, std::string style, int cost){
        setDesc(desc);
        setMagnitude(magnitude);
        setStyle(style);
        setCost(cost);    
    }
    
    //setters
    void setDesc(std::string desc){
        this->desc = desc;
    }

    void setMagnitude(int magnitude){
        this->magnitude;
    }

    void setStyle(std::string style){
        this->style = style;
    }

    void setCost(int cost){
        this->cost = cost;
    }
};

class Ideology{
    public:
    // sensitivites range from -5 to 5, ints only
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
    Ideology(std::string name, int sens_progress, int sens_religion, int sens_equality, int sens_centralise, int sens_assimilation, int sens_military, int sens_democracy, int sens_globalist, int sens_security){
        this->name = name;
        this->sens_progress = sens_progress;
        this->sens_religion = sens_religion;
        this->sens_equality = sens_equality;
        this->sens_centralise = sens_centralise;
        this->sens_assimilation = sens_assimilation;
        this->sens_military = sens_military;
        this->sens_democracy = sens_democracy;
        this->sens_globalist = sens_globalist;
        this->sens_security = sens_security;
    }
};

// party position in parliament
enum Position{
        government_lead,
        coalition_partner,
        opposition,
    };

// generic rand scrambler (for seeding)
unsigned long mix(unsigned long a, unsigned long b, unsigned long c){
        a=a-b;  a=a-c;  a=a^(c >> 13);
        b=b-c;  b=b-a;  b=b^(a << 8);
        c=c-a;  c=c-b;  c=c^(b >> 13);
        a=a-b;  a=a-c;  a=a^(c >> 12);
        b=b-c;  b=b-a;  b=b^(a << 16);
        c=c-a;  c=c-b;  c=c^(b >> 5);
        a=a-b;  a=a-c;  a=a^(c >> 3);
        b=b-c;  b=b-a;  b=b^(a << 10);
        c=c-a;  c=c-b;  c=c^(b >> 15);
        return c;
    }


class Member{
    public:
    // loyalty, popularity, competency range from 0-5
    int loyalty;
    int popularity;
    int competency;
    std::string name;
    int age=0;

    //static storage for all of the traits in the games
    std::vector<Trait> general_traits;
    // this empty constructor should be removed
    Member(std::string name){
        this->name = name;
        //setTraits(general_traits);
    }

    void setTraits(){
        // go to each map, and take rand amount of traits to apply
        for (auto section : general_traits) {
        }

    }
};

class Party{
    public:
    std::string name;
    std::vector<Member*> members;
    Ideology *ideology;  
    Position position = opposition;

    Party(std::string name, Ideology *ideology, int member_amount){
        this->name = name;
        this->ideology = ideology;
        make_members(member_amount);
    }

    void make_members(int member_amount){
        std::vector <std::string> first_name = {"John", "Mary", "Peter", "Steve", "Michael", "Jane", "Shane", "Angela", "Niall", "Cathal", "Leo", "Anne", "Julie", "Michelle" };
        std::vector <std::string> second_name = {"Power", "Costello", "Humphrys", "Kelly", "Brown", "Cooper", "Stack", "Small", "Grande", "Martin", "Schwab", "Obama", "Dowling"};

        for (int i=0; i < member_amount ; i++){
            std::string picker1 = first_name[rand() % (first_name.size() - 1)];
            std::string picker2 = second_name[rand() % (second_name.size() - 1)];
            Member * member = new Member(picker1 + " " + picker2);
            this->members.push_back(member);
        }
    }

    void show_members(){
        for (int i=0; i < this->members.size(); i++){
            std::cout << this->members[i]->name << "\n"; 
        }
    }
};

class Voter{
    public:
    bool voted;
    Ideology *belief;
    Party *prev_voted = NULL;
    Voter(Ideology *belief){
        this->belief = belief;
    }
    void show_belief(){
        std::cout << "Voter: " << this->belief->name << "\n";
    }

    void vote(){
    }

    void show_attitudes(std::vector<Voter*> voters){
        std::unordered_map<std::string, int> belief_tally;
        for (auto & i : voters){
            belief_tally[i->belief->name] ++;
        }

        std::cout << "BELIEFS\n";
        for (auto& it : belief_tally) {
            std::cout << it.first << ' ' << it.second << std::endl;
        }
    }
};

class Parliament{
    public:
    int seat_number;
    int day_till_election=0;
    bool in_session=false;
    Party * in_power;
    
    std::vector<Party*> parties;
    std::unordered_map<std::string, int> tally;

    Parliament(int seat_number, Party *in_power, std::vector<Party*> parties){
        this->seat_number=seat_number;
        this-> in_power = in_power;
        this-> parties = parties;
        set_tally();
    }

    // setters    
    void set_tally(){
        for (int i = 0 ; i < parties.size() ; i++){
            this->tally[parties[i]->name] = 0;
        }
    }

    //showers
    void show_parliament(){
        std::cout << "----------------------------------------" << "\n";
        std::cout << "PARLIAMENT:" << "\n";
        for(int i = 0 ; i < parties.size() ; i++){
            std::cout << parties[i]->name;
            std::cout << " members: " << parties[i]->members.size() << "\n";
        }
    }

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
    
    void show_votes(float turnout){  
        std::cout << "\nTURNOUT\n";
        std::cout << turnout << "%\n";
        std::cout << "\nVOTES\n";
        std::set<std::pair<std::string, int>, comp> S(this->tally.begin(), this->tally.end());
        for (auto& it : S) {
            std::cout << it.first << ' ' << it.second << std::endl;
        }
    }

    // removes empty parties with no members
    void election_cleanup(){ 
        for (auto & i : this->parties){
            if (i->members.size() <= 0){
                std::cout << i->name << " has been removed from the parliament!\n";
            }
        }
    }

    // adjust members based on their percentage of votes
    void parliament_shuffler(int turnout){
        std::cout << "\nCHANGES\n";
        float vote_leftovers = 0;
        for(int i = 0 ; i < this->parties.size() ; i++){
            int count = 0;
            // get vote share and seat share of the party
            float vote_share = (float(this->tally[this->parties[i]->name]) / float(turnout));
            float seat_share = (float(this->parties[i]->members.size()) / float(this->seat_number));
            
            // how many seats they need to reach
            float vote_target = (vote_share * this->seat_number);
            // round down, add remainder to leftovers for later
            float new_target = floor(vote_target);
            vote_leftovers += (vote_target - new_target);
            
            // the adjust their seats until it reflects this percentage
            // upsize the party
            if (seat_share < vote_share){
                while (this->parties[i]->members.size() < new_target){
                    this->parties[i]->make_members(1);
                    count ++;
                }
            }

            // downsize the party
            else if (seat_share > vote_share){
                while (this->parties[i]->members.size() > new_target){
                    this->parties[i]->members.pop_back();
                    count --;
                }
            }            
            std::cout << this->parties[i]->name << " changed by " << count << "\n";
        }
        
        // leftover seats given to random parties
        while (vote_leftovers > 0){
            int random = rand() % this->parties.size();
            this->parties[random]->make_members(1);
            vote_leftovers --;
        }
    }
    // generates events during an election
    void election_events(){
        // chance of generating an election event
        float election_event_chance = 75.0;
        // tries to generate a random event for the election
        while(election_event_chance > 0){
            // chance of the vent happening
            float event_happened = rand() % 100;
            if (event_happened < election_event_chance){
                // choose the type of event to happen
                // chances are distributed are 40% transfer, 30% loser, 30% winner
                int event_chooser = rand() % 100;
                if ((event_chooser) <= 40 ){
                    // transfer event
                    ElectionTransfer *event = new ElectionTransfer("A transfer has occured", 0, this->parties[rand() % (parties.size())]->name, this->parties[rand() % (parties.size())]->name);
                    this->tally = event->transfer(this->tally);
                    event->FlavourShower();
                }
                
                else if (event_chooser >= 70){
                    // loser event
                    ElectionLoser *event = new ElectionLoser("A party has lost some support among its voter base!", 0, this->parties[rand() % (parties.size())]->name);
                    this->tally = event->loser(this->tally);
                    event->FlavourShower();
                }
                else{
                    // winner event
                    ElectionWinner *event = new ElectionWinner("A party has won some support with other parties voters!", 0, this->parties[rand() % (parties.size())]->name);
                    this->tally = event->winner(this->tally);
                    event->FlavourShower();
                }
                election_event_chance -= 10;
                // TODO
                // our event is always null this is bad, likely because preded above event_chooser
            }
            // event gen chance failed so give up
            else{
                break;
            }
        }
    }

    // main election runner
    void hold_election(std::vector<Voter*> voters, std::vector<Ideology*> ideologies){     
        int turnout = 0;
        // chances for voting for each type of person
        float normal_chance = 90.0;
        float apath_chance = 30.0;
        float loyalty_chance = 80.0;
        float party_picker = 60.0;
        
        set_tally();
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(this->parties), std::end(this->parties), rng);
        for(int i = 0; i < voters.size() ; i++){
            
            // normal voters go here
            if (voters[i]->belief->name != "Apathy"){
                float voted = rand() % 100;
                if (voted < normal_chance){
                    float loyalty = rand() % 100;
                    // votes for the party they voted for before
                    if (loyalty < loyalty_chance && voters[i]->prev_voted != NULL){
                        turnout ++;
                        this->tally[voters[i]->prev_voted->name] ++;
                    }

                    // finds the parties that match their ideology to vote for, will try to choose the bigger parties with the most members first
                    else{
                        std::map<int, Party*, std::greater<int>> vote_choice = {};
                        for (int j = 0; j < this->parties.size() ; j++){ 
                            if (this->parties[j]->ideology->name == voters[i]->belief->name){
                                vote_choice[this->parties[j]->members.size()] = this->parties[j];
                            }
                        }

                        for (auto const& x : vote_choice){
                            float chose_party = rand() % 100;
                            if (party_picker < chose_party){
                                this->tally[x.second->name] ++;
                                voters[i]->prev_voted = x.second;
                                turnout ++;
                                break;
                            }
                        }
                    }
                }
            }

            // apathetics will vote randomly or not at all
            else{
                float voted = rand() % 100;
                if (voted < apath_chance){
                    // voted
                    this->tally[this->parties[rand() % (parties.size())]->name] ++;
                    turnout ++;
                }
            }
        }

        float true_turnout = (turnout / (float)voters.size()) * 100;
        show_votes(true_turnout);
        //election_events();
        parliament_shuffler(turnout);
        this->day_till_election = 10;
    }
};