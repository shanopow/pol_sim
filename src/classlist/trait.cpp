#include "trait.hpp"

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
