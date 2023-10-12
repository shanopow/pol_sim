#ifndef IDEOLOGY_HPP
#define IDEOLOGY_HPP

#include <string>

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

#endif