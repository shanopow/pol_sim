#ifndef PEOPLE_HPP
#define PEOPLE_HPP

#include <string>
#include <vector>

class Trait{
    public:
    std::string desc;
    int magnitude;
    std::string style;
    int cost;

    Trait(std::string desc, int magnitude, std::string style, int cost);

    void setDesc(std::string desc);
    void setMagnitude(int magnitude);
    void setStyle(std::string style);
    void setCost(int cost);
};

class Member{
    public:
    int loyalty;
    int popularity;
    int competency;
    std::string name;
    int age=0;

    std::vector<Trait> general_traits;
    Member(std::string name);

    //void setTraits();
};

#endif