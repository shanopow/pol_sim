#include "voter.hpp"


Voter::Voter(Ideology *belief){
    this->belief = belief;
}

void Voter::show_belief(){
    std::cout << "Voter: " << this->belief->name << "\n";
}

void Voter::vote(){
}

void Voter::show_attitudes(std::vector<Voter*> voters){
    std::unordered_map<std::string, int> belief_tally;
    for (auto & i : voters){
        belief_tally[i->belief->name] ++;
    }

    std::cout << "BELIEFS\n";
    for (auto& it : belief_tally) {
        std::cout << it.first << ' ' << it.second << std::endl;
    }
}