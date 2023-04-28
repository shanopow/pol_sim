#include <string>
#include <unordered_map>
#include <iostream>
#include <ostream>


class ElectionEvent{
    public:
    std::string flavour;
    int duration;
    virtual void SetFlavour(std::string flavour);
    virtual void SetDuration(int duration);
};

class ElectionTransfer : public ElectionEvent {
    public:
    std::string party_loser;
    std::string party_winner;
    int transfer_amount;

    // constructor
    ElectionTransfer(std::string flavour, int duration, std::string party_loser, std::string party_winner);
    
    void FlavourShower();

    // picks a random amount to move from loser to winner
    std::unordered_map<std::string, int> transfer(std::unordered_map<std::string, int> tally);
};

// a party loses votes, they are then redestributed to all other parties
class ElectionLoser : public ElectionEvent {
    public:
    std::string party_loser;
    int loss_amount;

    // constructor
    ElectionLoser(std::string flavour, int duration, std::string party_loser);

    void FlavourShower();

    // reduces the votes for the party by a random amount, then distributes between other parites in the tally pool
    std::unordered_map<std::string, int> loser(std::unordered_map<std::string, int> tally);
};

// a party wins votes, they are taken form all other parties
class ElectionWinner : public ElectionEvent {
    public:
    std::string party_winner;
    int win_amount;

    //constructor
    ElectionWinner(std::string flavour, int duration, std::string party_winner);

    void FlavourShower();

    // a random amount of votes are taken out of the tally pool and then given to a specific party
    std::unordered_map<std::string, int> winner(std::unordered_map<std::string, int> tally);
};

// events that changes aspects related to the voter pool
class VoterEvent{
    public:
    void setFlavour(std::string flavour);
};

// changes the attitudes of some random voters
class AttitudeEvent : public VoterEvent{
    public:
    int amount;
    AttitudeEvent(std::string flavour, int amount);
};