#include "ideology.hpp"


Ideology::Ideology(std::string name, int sens_progress, int sens_religion, int sens_equality, int sens_centralise, int sens_assimilation, int sens_military, int sens_democracy, int sens_globalist, int sens_security){
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
