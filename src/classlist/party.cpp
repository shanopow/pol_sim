#include "party.hpp"
#include "ideology.hpp"

Party::Party(std::string name, Ideology *main_ideology, int member_amount){
    this->name = name;
    this->main_ideology = main_ideology;
    make_members(member_amount);
}

void Party::make_members(int member_amount){
    std::vector <std::string> first_name = {"John", "Mary", "Peter", "Steve", "Michael", "Jane", "Shane", "Angela", "Niall", "Cathal", "Leo", "Anne", "Julie", "Michelle" };
    std::vector <std::string> second_name = {"Power", "Costello", "Humphrys", "Kelly", "Brown", "Cooper", "Stack", "Small", "Grande", "Martin", "Schwab", "Obama", "Dowling"};

    for (int i=0; i < member_amount ; i++){
        std::string picker1 = first_name[rand() % (first_name.size() - 1)];
        std::string picker2 = second_name[rand() % (second_name.size() - 1)];
        Member * member = new Member(picker1 + " " + picker2);
        this->members.push_back(member);
    }
}

void Party::show_members(){
    for (int i=0; i < this->members.size(); i++){
        std::cout << this->members[i]->name << "\n"; 
    }
}
