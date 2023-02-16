#include "stdlib.h"
#include "time.h"


#include <bits/stdc++.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

// party position in parliament
enum Position{
        government_lead,
        coalition_partner,
        opposition
    };
    
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

// parent law
class Law{
    public:
    std::string name;
    Party *introduced_by;
    // negative costs will put money to the treasury
    int days_till_free;
    Law(std::string name){
        this->name=name;
    }
};

// children of Law
class TaxLaw : Law{
    
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

class Voter{
    public:
    bool voted;
    Ideology *belief;

    Voter();
    Voter(Ideology *belief){
        this->belief = belief;
    }
    void show_belief(){
        std::cout << "Voter: " << this->belief->name << "\n";
    }
};

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


class Member{
    public:
    // loyalty, popularity, competency range from 0-5
    int loyalty=3;
    int popularity=3;
    int competency=3;
    std::string name;
    int age=0;
    Member();
    Member(std::string name){
        this->name = name;
    }
};

class Party{
    public:
    std::string name;
    std::vector<Member*> members;
    Ideology *ideology;  
    Position position = opposition;

    Party();
    Party(std::string name, Ideology *ideology, int member_amount){
        this->name = name;
        this->ideology = ideology;
        this->members = members;
        make_members(member_amount);
    }

    void make_members(int member_amount){
        srand(time(0));
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
        bool operator()(const T& l, const T& r) const
        {
            if (l.second != r.second) {
                return l.second > r.second;
            }
            return l.first > r.first;
        }
    };   
    
    void show_votes(){ 
        std::cout << "VOTES\n";
        std::set<std::pair<std::string, int>, comp> S(this->tally.begin(), this->tally.end());
        for (auto& it : S) {
            std::cout << it.first << ' ' << it.second << std::endl;
        }
    }

    // elections

    // removes empty parties with no members
    void election_cleanup(){
        
        for (auto & i : this->parties){
            if (i->members.size() <= 0){
                std::cout << i->name << " has been removed from the parliament!\n";
            }
        }
    }

    // adjust members based on their percentage of votes
    void parliament_shuffler(){
        for(int i = 0 ; i < this->parties.size() ; i++){
            int count = 0;
            // for now just hard set the votes to the member count;
            // check if less or more, then one by one add or delete members until satisfied
            
            // upsize the party
            if (this->parties[i]->members.size() < this->tally[this->parties[i]->name]){
                while (this->parties[i]->members.size() < this->tally[this->parties[i]->name]){
                    this->parties[i]->make_members(1);
                    count ++;
                }
            }
            
            // downsize the party
            else if (this->parties[i]->members.size() > this->tally[this->parties[i]->name]){
                while (this->parties[i]->members.size() > this->tally[this->parties[i]->name]){
                    this->parties[i]->members.pop_back();
                    count --;
                }
            }

            std::cout << this->parties[i]->name << " changed by " << count << "\n";
        }
    }

    // main election runner
    void hold_election(std::vector<Voter*> voters, std::vector<Ideology*> ideologies){     
        set_tally();
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(this->parties), std::end(this->parties), rng);
        
        for(int i = 0; i < voters.size() ; i++){
            if (voters[i]->belief->name != "Apathy"){
                for (int j = 0; j < this->parties.size() ; j++){ 
                    if (this->parties[j]->ideology->name == voters[i]->belief->name){
                        this->tally[this->parties[j]->name] ++;
                        break;
                    }   
                }
            }
            
            // apathetics will vote randomly
            else{
                unsigned long seed = mix(clock(), time(NULL), getpid());
                srand(seed);
                this->tally[this->parties[rand() % (parties.size())]->name] ++;
            }
        }
        show_votes();
        parliament_shuffler();
    }
};