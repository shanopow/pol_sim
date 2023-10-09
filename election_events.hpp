// ElectionEvent.hpp
#ifndef ELECTIONEVENT_HPP
#define ELECTIONEVENT_HPP

#include <string>
#include <unordered_map>
#include <iostream>

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
    ElectionTransfer(std::string flavour, int duration, std::string party_loser, std::string party_winner);
    void FlavourShower();
    std::unordered_map<std::string, int> Transfer(std::unordered_map<std::string, int> tally);
};

class ElectionLoser : public ElectionEvent {
    public:
    std::string party_loser;
    int loss_amount;
    ElectionLoser(std::string flavour, int duration, std::string party_loser);
    void FlavourShower();
    std::unordered_map<std::string, int> Loser(std::unordered_map<std::string, int> tally);
};

class ElectionWinner : public ElectionEvent {
    public:
    std::string party_winner;
    int win_amount;
    ElectionWinner(std::string flavour, int duration, std::string party_winner);
    void FlavourShower();
    std::unordered_map<std::string, int> Winner(std::unordered_map<std::string, int> tally);
};

class VoterEvent{
    public:
    std::string flavour;
    void setFlavour(std::string flavour);
};

class AttitudeEvent : public VoterEvent{
    public:
    int amount;
    AttitudeEvent(std::string flavour, int amount);
};

#endif // ELECTIONEVENT_HPP
