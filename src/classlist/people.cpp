#include "people.hpp"
#include "ideology.hpp"

// traits are used by members
void TraitMaker(std::vector<std::vector<std::string>> delim_traits){
    std::vector<Trait*> traits;
    for (const auto &innerVec : delim_traits) {
        std::string style = innerVec[0];
        std::string name = innerVec[1];
        int magnitude = stoi(innerVec[2]);
        
        Trait *new_trait = new Trait(style, name, magnitude);
        traits.push_back(new_trait);
    }
}

Trait::Trait( std::string style, std::string desc, int magnitude){
    setStyle(style);
    setDesc(desc);
    setMagnitude(magnitude);
}

//setters
void Trait::setStyle(std::string style){
    this->style = style;
}

void Trait::setDesc(std::string desc){
    this->desc = desc;
}

void Trait::setMagnitude(int magnitude){
    this->magnitude;
}

Member::Member(std::string name){
    this->name = name;
    //setTraits(general_traits);
}

/*
void Member::setTraits(){
    // go to each map, and take rand amount of traits to apply
    for (auto section : general_traits) {
    }

}
*/

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
