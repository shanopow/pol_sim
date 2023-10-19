#ifndef TRAIT_HPP
#define TRAIT_HPP

#include <string>
#include <vector>

void TraitMaker(std::vector<std::vector<std::string>> delim_traits);

class Trait{
    public:
    std::string desc;
    int magnitude;
    std::string style;
    int cost;

    Trait(std::string style, std::string desc, int magnitude);

    void setDesc(std::string desc);
    void setMagnitude(int magnitude);
    void setStyle(std::string style);
};

#endif