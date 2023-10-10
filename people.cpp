#include <vector>
#include <string>

#include "people.hpp"
// traits are used by members
Trait::Trait(std::string desc, int magnitude, std::string style, int cost){
    setDesc(desc);
    setMagnitude(magnitude);
    setStyle(style);
    setCost(cost);    
}

//setters
void Trait::setDesc(std::string desc){
    this->desc = desc;
}

void Trait::setMagnitude(int magnitude){
    this->magnitude;
}

void Trait::setStyle(std::string style){
    this->style = style;
}

void Trait::setCost(int cost){
    this->cost = cost;
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