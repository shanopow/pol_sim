#include "election_events.hpp"

//Election Events
void ElectionEvent::SetFlavour(std::string flavour){
    this->flavour = flavour;
}

void ElectionEvent::SetDuration(int duration){
    this->duration = duration;
}

// Election Transfer
ElectionTransfer::ElectionTransfer(std::string flavour, int duration, std::string party_loser, std::string party_winner){
    this->party_loser = party_loser;
    this->party_winner = party_winner;
    
    // inherited methods
    ElectionTransfer::SetFlavour(flavour);
    ElectionTransfer::SetDuration(duration);
}

void ElectionTransfer::FlavourShower(){
    std::cout << this->party_loser << " lost " << this->transfer_amount <<  " votes to " << this->party_winner << std::endl;
}

// picks a random amount to move from loser to winner
std::unordered_map<std::string, int> ElectionTransfer::Transfer(std::unordered_map<std::string, int> tally){
    int picker = rand() % 3;
    if (picker <= 0){
        picker = 1;
    }
    this->transfer_amount = picker;
    tally[party_loser] -= picker;
    tally[party_winner] += picker;
    return tally;
}

// Election Loser

// a party loses votes, they are then redestributed to all other parties
ElectionLoser::ElectionLoser(std::string flavour, int duration, std::string party_loser){
    this->party_loser = party_loser;
    // inherited methods
    ElectionLoser::SetFlavour(flavour);
    ElectionLoser::SetDuration(duration);
}

void ElectionLoser::FlavourShower(){
    std::cout << this->party_loser << " lost " << this->loss_amount <<  " votes" << std::endl;
}

// reduces the votes for the party by a random amount, then distributes between other parites in the tally pool
std::unordered_map<std::string, int> ElectionLoser::Loser(std::unordered_map<std::string, int> tally){
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

// Election Winner
// a party wins votes, they are taken from all other parties
ElectionWinner::ElectionWinner(std::string flavour, int duration, std::string party_winner){
    this->party_winner = party_winner;
    // inherited methods
    SetFlavour(flavour);
    SetDuration(duration);
}
    
void ElectionWinner::FlavourShower(){
    std::cout << this->party_winner << " won " << this->win_amount <<  " votes" << std::endl;
}

// a random amount of votes are taken out of the tally pool and then given to a specific party
std::unordered_map<std::string, int> ElectionWinner::Winner(std::unordered_map<std::string, int> tally){
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

// events that changes aspects related to the voter pool
void VoterEvent::setFlavour(std::string flavour){
    this->flavour = flavour; 
}

// changes the attitudes of some random voters
AttitudeEvent::AttitudeEvent(std::string flavour, int amount){
    this->amount = amount;
    setFlavour(flavour);
}