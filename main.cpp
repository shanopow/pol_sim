#include "stdlib.h"
#include "time.h"

#include <unistd.h>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "gov_handler.hpp"

// main
int main(){
    // make ideologies
    Ideology *ideo0 =  new Ideology("Apathy", 0,0,0,0,0,0,0,0,0);
    Ideology *ideo1 =  new Ideology("Nationalism", 0,5,-2,2,5,5,-2,-3,3);
    Ideology *ideo2 = new Ideology("Liberalism", 2,-3, 0,0,-2,-1,2,4,0);
    Ideology *ideo3 = new Ideology("Socialism", 5,-4,5,3,0,0,4,4,-1);
    std::vector<Ideology*> ideologies = {ideo0, ideo1, ideo2, ideo3};

    // make voter population
    std::vector<Voter*> voters = {};
    unsigned long seed = mix(clock(), time(NULL), getpid());
    srand(seed);
    for(int i = 0; i < 100 ; i++){
        int picker = rand() % (ideologies.size());
        Voter *voter = new Voter(ideologies[picker]);
        voters.push_back(voter);
    }

    // make parties
    Party *part1 = new Party("Whigs", ideo2, 36);
    Party *part2 = new Party("Tories", ideo1, 22);
    Party *part3 = new Party("Workers Party", ideo3, 4);
    Party *part4 = new Party("Meme Party", ideo1, 2);
    Party *part5 = new Party("Solidarity Party",ideo3, 16);
    std::vector<Party*> parties = {part1, part2, part3, part4, part5};

    Parliament parliament = Parliament(80, part1, parties);

    // make traits
    std::vector<std::unordered_map<std::string, int>> general_traits;
    // inits empty, traits will be added based on current parties
    std::unordered_map<std::string, std::string> voting_traits{};
    // each positive and negative should balance out for fairness
    std::unordered_map<std::string, int> loyalty_traits{
        {"Disgruntled", -1},
        {"Deluded", -2},
        {"Scheming", -3},
        {"Trusting", 1},
        {"Gullible", 3},
        {"Content", 2},
        {"Devoted", 4},
        {"Inciter", -4}
    };

    std::unordered_map<std::string, int> popularity_traits{
        {"Media Personality", 2},
        {"Local Hero", 1},
        {"Fool", -1},
        {"Orator", 2},
        {"Agressive", -2},
        {"Scandalous", -3},
    };

    std::unordered_map<std::string, int> competency_traits{
        {"Old Guard", 1},
        {"Green", -1},
        {"Senile", -3},
        {"Paper Pusher", 2},
        {"Bureaucrat", 3},
        {"Lazy", -1}
    };
    
    // dump them onto the vector
    general_traits.push_back(loyalty_traits);
    general_traits.push_back(popularity_traits);
    general_traits.push_back(competency_traits);
    
    // day by day
    for(int day=0; day < 2; day++){
        parliament.show_parliament();
        if (parliament.day_till_election <= 0){
            std::cout << "Election time!" << "\n";
            parliament.hold_election(voters, ideologies);
        }
        parliament.day_till_election --;
    }
    return 0;
}