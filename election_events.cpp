#include <string>
#include <unordered_map>

// election related event to change votes for a faction
// abstract parent class
class ElectionEvent{
    public:
    std::string flavour;
    int duration;
    //setters for inheriting
    virtual void SetFlavour(std::string flavour){
        this->flavour = flavour;
    }

    virtual void SetDuration(int duration){
        this->duration = duration;
    }
};

// transfer from one party to anothers
class ElectionTransfer : public ElectionEvent {
    public:
    std::string party_loser;
    std::string party_winner;
    int transfer_amount;
    // constructor
    ElectionTransfer(std::string flavour, int duration, std::string party_loser, std::string party_winner){
        this->party_loser = party_loser;
        this->party_winner = party_winner;
        
        // inherited methods
        SetFlavour(flavour);
        SetDuration(duration);
    }
    void FlavourShower(){
        std::cout << this->party_loser << " lost " << this->transfer_amount <<  " votes to " << this->party_winner << std::endl;
    }

    // picks a random amount to move from loser to winner
    std::unordered_map<std::string, int> transfer(std::unordered_map<std::string, int> tally){
        int picker = rand() % 3;
        if (picker <= 0){
            picker = 1;
        }
        this->transfer_amount = picker;
        tally[party_loser] -= picker;
        tally[party_winner] += picker;
        return tally;
    }
};

// a party loses votes, they are then redestributed to all other parties
class ElectionLoser : public ElectionEvent {
    public:
    std::string party_loser;
    int loss_amount;
    // constructor
    ElectionLoser(std::string flavour, int duration, std::string party_loser){
        this->party_loser = party_loser;
        // inherited methods
        SetFlavour(flavour);
        SetDuration(duration);
    }
    
    void FlavourShower(){
        std::cout << this->party_loser << " lost " << this->loss_amount <<  " votes" << std::endl;
    }

    // reduces the votes for the party by a random amount, then distributes between other parites in the tally pool
    std::unordered_map<std::string, int> loser(std::unordered_map<std::string, int> tally){
        int picker = rand() % 3;
        if (picker <= 0){
            picker = 1;
        }
        this->loss_amount = picker;
        tally[party_loser] -= picker;
        // send out the freed votes
        while (picker > 0){
            // pick random party in tally to give to
            picker--;
        }
        return tally;
    }
};

// a party wins votes, they are taken form all other parties
class ElectionWinner : public ElectionEvent {
    public:
    std::string party_winner;
    int win_amount;
    //constructor
    ElectionWinner(std::string flavour, int duration, std::string party_winner){
        this->party_winner = party_winner;
        // inherited methods
        SetFlavour(flavour);
        SetDuration(duration);
    }
    
    void FlavourShower(){
        std::cout << this->party_winner << " won " << this->win_amount <<  " votes" << std::endl;
    }

    // a random amount of votes are taken out of the tally pool and then given to a specific party
    std::unordered_map<std::string, int> winner(std::unordered_map<std::string, int> tally){
        int picker = rand() % 3;
        if (picker <= 0){
            picker = 1;
        }
        win_amount = picker;
        tally[party_winner] += picker;
        // send out the freed votes
        while (picker > 0){
            // pick random party in tally to take from
            picker--;
        }
        return tally;
    }
};

// events that changes aspects related to the voter pool
class VoterEvent{
    public:
    std::string flavour;
    void setFlavour(std::string flavour){
        this->flavour = flavour; 
    }
};

// changes the attitudes of some random voters
class AttitudeEvent : public VoterEvent{
    public:
    int amount;
    AttitudeEvent(std::string flavour, int amount){
        this->amount = amount;
        setFlavour(flavour);
    }
};