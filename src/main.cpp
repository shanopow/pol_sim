#include "file_reader.hpp"
#include "classlist/parliament.hpp"

#include <unistd.h>
#include "time.h"
#include <Windows.h>

// main
int main(){
    FileReader *filer = new FileReader("../data/traits.csv");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // We create our objects wirth a factory here
    
    
    
    
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

    // create trait objects
    filer->ReadIn();
    TraitMaker(filer->total_lines);

    // make parties
    Party *part1 = new Party("Whigs", ideo2, 36);
    Party *part2 = new Party("Tories", ideo1, 22);
    Party *part3 = new Party("Workers Party", ideo3, 4);
    Party *part4 = new Party("Meme Party", ideo1, 2);
    Party *part5 = new Party("Solidarity Party",ideo3, 16);
    
    std::vector<Party*> parties = {part1, part2, part3, part4, part5};

    Parliament parliament = Parliament(80, part1, parties);

    
    // day by day
    for(int day=0; day < 2; day++){
        parliament.show_parliament();
        if (parliament.day_till_election <= 0){
            SetConsoleTextAttribute(hConsole, 2);
            std::cout << "Election time!" << "\n";
            SetConsoleTextAttribute(hConsole, 15);
            parliament.hold_election(voters, ideologies);
        }
        parliament.day_till_election --;
    }
    return 0;
}