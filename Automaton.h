//
// Created by LENOVO on 05/12/2018.
//

#ifndef FSAUTOMATA_AUTOMATON_H
#define FSAUTOMATA_AUTOMATON_H

#include <unordered_set>

#include "Alphabet.h"
#include "Word.h"
#include "States.h"
#include "Transitions.h"

class Automaton {
public:
    Automaton(const std::string &id, Alphabet X = Alphabet({'a','b'}));
    Automaton(const std::string &id, const Alphabet &X, const States &S, const std::unordered_set<std::string> &Sinit,
              const Transitions &II, const std::unordered_set<std::string> &Sfinal);

    bool insertTransition(const std::string &initial, const std::string &word, const std::string &final);
    bool insertNewState(const std::string &state);
    bool setInitial(const std::string &state);
    bool setInitial(std::unordered_set<std::string> states);
    bool setFinal(const std::string &state);
    bool setFinal( std::unordered_set<std::string> states);
    void setId(const std::string &id){id_ = id;};

    const Alphabet &getX() const;
    const std::unordered_set<std::string> getStates();
    const std::unordered_set<std::string> &getSinit() const;
    const Transitions &getII() const;
    const std::unordered_set<std::string> &getSfinal() const;
    const std::string &id()const{ return id_;}

    friend std::ostream& operator<<(std::ostream& out, const Automaton &automaton);

    bool isRecognized(const Word word) const;

    void toReduced();
    const Automaton toPartiallyGeneralized() const;//-> |word|<=1
    void removeEpsilonTransitions();
    void toSimple();//-> |word|==1
    void toDeterministic();
    void toComplete();
    void tocomplementary();


private:
    std::string id_;
    Alphabet X;
    States S;
    std::unordered_set<std::string> Sinit;
    Transitions II;
    std::unordered_set<std::string> Sfinal;
};

std::ostream& operator<<(std::ostream& out, const Automaton &automaton);
std::ostream& operator<<(std::ostream& out, const std::unordered_set<std::string> &str);

#endif //FSAUTOMATA_AUTOMATON_H
