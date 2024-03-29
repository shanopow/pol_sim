#include "parliament.hpp"

// generic rand scrambler (for seeding)
unsigned long mix(unsigned long a, unsigned long b, unsigned long c){
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

Parliament::Parliament(int seat_number, Party *in_power, std::vector<Party*> parties){
    this->seat_number=seat_number;
    this-> in_power = in_power;
    this-> parties = parties;
    set_tally();
}

// setters    
void Parliament::set_tally(){
    for (int i = 0 ; i < parties.size() ; i++){
        this->tally[parties[i]->name] = 0;
    }
}

//showers
void Parliament::show_parliament(){
    std::cout << "----------------------------------------" << "\n";
    std::cout << "PARLIAMENT:" << "\n";
    for(int i = 0 ; i < parties.size() ; i++){
        std::cout << parties[i]->name;
        std::cout << " members: " << parties[i]->members.size() << " (" << parties[i]->last_result << ") " << "\n";
    }
    std::cout << "\n";
}

struct comp {
    template <typename T>

    // Comparator function
    bool operator()(const T& l, const T& r) const{
        if (l.second != r.second) {
            return l.second > r.second;
        }
        return l.first > r.first;
    }
};   
    
void Parliament::show_votes(float turnout){  
    std::cout << "\nTURNOUT\n";
    std::cout << turnout << "%\n";
    std::cout << "\nVOTES\n";
    std::set<std::pair<std::string, int>, comp> S(this->tally.begin(), this->tally.end());
    for (auto& it : S) {
        std::cout << it.first << ' ' << it.second << std::endl;
    }
}

// removes empty parties with no members
void Parliament::election_cleanup(){ 
    for (auto & i : this->parties){
        if (i->members.size() <= 0){
            std::cout << i->name << " has been removed from the parliament!\n";
        }
    }
}

// adjust members based on their percentage of votes
void Parliament::parliament_shuffler(int turnout){
    int taken_seats = 0;
    int leftover_seats = 0;

    for(int i = 0 ; i < this->parties.size() ; i++){
        int count = 0;
        
        // get vote share and seat share of the party
        float vote_share = (float(this->tally[this->parties[i]->name]) / float(turnout));
        float seat_share = (float(this->parties[i]->members.size()) / float(this->seat_number));
        
        // how many seats they need to reach
        float vote_target = (vote_share * this->seat_number);
        
        // round down to solid number
        float new_target = floor(vote_target);
        
        // the adjust their seats until it reflects this percentage
        // upsize the party
        if (seat_share < vote_share){
            while (this->parties[i]->members.size() < new_target){
                this->parties[i]->make_members(1);
                count ++;
            }
        }

        // downsize the party
        else if (seat_share > vote_share){
            while (this->parties[i]->members.size() > new_target){
                this->parties[i]->members.pop_back();
                count --;
            }
        }
        // update the taken seats and add to the parties last result
        taken_seats += this->parties[i]->members.size();
        this->parties[i]->last_result = count;
    }
    
    // leftover seats given to random parties
    leftover_seats = this->seat_number - taken_seats;
    while (leftover_seats > 0){
        int random = rand() % this->parties.size();
        this->parties[random]->make_members(1);
        this->parties[random]->last_result ++;
        leftover_seats --;
    }
}
// generates events during an election
void Parliament::election_events(){
    // chance of generating an election event
    float election_event_chance = 75.0;
    
    // tries to generate a random event for the election
    while(election_event_chance > 0){
        // chance of the vent happening
        float event_happened = rand() % 100;
        if (event_happened < election_event_chance){
            // choose the type of event to happen
            // chances are distributed are 40% transfer, 30% loser, 30% winner
            int event_chooser = rand() % 100;
            if ((event_chooser) <= 40 ){
                // transfer event
                ElectionTransfer *event = new ElectionTransfer("A transfer has occured", 0, this->parties[rand() % (parties.size())]->name, this->parties[rand() % (parties.size())]->name);
                this->tally = event->Transfer(this->tally);
                event->FlavourShower();
            }
            
            else if (event_chooser >= 70){
                // loser event
                ElectionLoser *event = new ElectionLoser("A party has lost some support among its voter base!", 0, this->parties[rand() % (parties.size())]->name);
                this->tally = event->Loser(this->tally);
                event->FlavourShower();
            }
            else{
                // winner event
                ElectionWinner *event = new ElectionWinner("A party has won some support with other parties voters!", 0, this->parties[rand() % (parties.size())]->name);
                this->tally = event->Winner(this->tally);
                event->FlavourShower();
            }
            election_event_chance -= 10;
            // TODO
            // our event is always null this is bad, likely because preded above event_chooser
        }
        // event gen chance failed so give up
        else{
            break;
        }
    }
}

// main election runner
void Parliament::hold_election(std::vector<Voter*> voters, std::vector<Ideology*> ideologies){     
    int turnout = 0;
    // chances for voting for each type of person
    float normal_chance = 90.0;
    float apath_chance = 30.0;
    float loyalty_chance = 80.0;
    float party_picker = 60.0;
    
    set_tally();
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(this->parties), std::end(this->parties), rng);
    for(int i = 0; i < voters.size() ; i++){
        
        // normal voters go here
        if (voters[i]->belief->name != "Apathy"){
            float voted = rand() % 100;
            if (voted < normal_chance){
                float loyalty = rand() % 100;
                // votes for the party they voted for before
                if (loyalty < loyalty_chance && voters[i]->prev_voted != NULL){
                    turnout ++;
                    this->tally[voters[i]->prev_voted->name] ++;
                }

                // finds the parties that match their ideology to vote for, will try to choose the bigger parties with the most members first
                else{
                    std::map<int, Party*, std::greater<int>> vote_choice = {};
                    for (int j = 0; j < this->parties.size() ; j++){ 
                        if (this->parties[j]->main_ideology->name == voters[i]->belief->name){
                            vote_choice[this->parties[j]->members.size()] = this->parties[j];
                        }
                    }

                    for (auto const& x : vote_choice){
                        float chose_party = rand() % 100;
                        if (party_picker < chose_party){
                            this->tally[x.second->name] ++;
                            voters[i]->prev_voted = x.second;
                            turnout ++;
                            break;
                        }
                    }
                }
            }
        }

        // apathetics will vote randomly or not at all
        else{
            float voted = rand() % 100;
            if (voted < apath_chance){
                // voted
                this->tally[this->parties[rand() % (parties.size())]->name] ++;
                turnout ++;
            }
        }
    }

    float true_turnout = (turnout / (float)voters.size()) * 100;
    show_votes(true_turnout);
    //election_events();
    parliament_shuffler(turnout);
    this->day_till_election = 10;
}