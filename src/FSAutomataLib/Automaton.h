//
// Created by LENOVO on 05/12/2018.
//

#ifndef FSAUTOMATA_AUTOMATON_H
#define FSAUTOMATA_AUTOMATON_H

#include <unordered_set>
#include <set>
#include <stack>
#include <algorithm>

#include "Alphabet.h"
#include "Word.h"
#include "States.h"
#include "Transitions.h"


class Automaton {
public:
    Automaton(const Automaton &automaton);
    Automaton(const std::string &id, Alphabet X = Alphabet({'a','b'}));
    Automaton(const std::string &id, const Alphabet &X, const States &S, const std::unordered_set<std::string> &Sinit,
              const Transitions &II, const std::unordered_set<std::string> &Sfinal);

    bool insertTransition(const std::string &source, const std::string &word, const std::string &destination);
    bool insertNewState(const std::string &state);
    bool insertSinkState();
    bool insertNewStates(const std::unordered_set<std::string> &states);
    bool setInitial(const std::string &state);
    bool setInitial(std::unordered_set<std::string> states);
    bool setFinal(const std::string &state);
    bool setFinal( std::unordered_set<std::string> states);
    void setId(const std::string &id){id_ = id;};

    const Alphabet &getX() const;
    const std::unordered_set<std::string> getStates()const;
    const std::unordered_set<std::string> &getSinit() const;
    const Transitions &getII() const;
    const std::unordered_set<std::string> &getSfinal() const;
    const std::string &id()const{ return id_;}

    bool isInitial(const std::string state)const;
    bool isFinal(const std::string state)const;

    friend std::ostream& operator<<(std::ostream& out, const Automaton &automaton);

    bool recognizes(const Word word) const;

    std::unordered_set<std::string> getAccessibleStates() const;
    std::unordered_set<std::string> getCoaccessibleStates() const;

    const Automaton  toReduced()const;
    const Automaton toPartiallyGeneralized() const;//-> |word|<=1
    const Automaton  removeEpsilonTransitions()const;
    const Automaton  toSimple()const;//-> |word|==1
    const Automaton  toDeterministic()const;
    const Automaton  toComplete()const;
    const Automaton  toComplementary()const;


private:
    std::string id_;
    Alphabet X;
    States S;
    std::unordered_set<std::string> Sinit;
    Transitions II;
    std::unordered_set<std::string> Sfinal;

    static size_t index;//Defined here for convinience.

    std::string concatStates(const std::set<std::string> &statesSetForLetter)const;
    bool intersect(const std::set<std::string> &orderedStates, const std::unordered_set<std::string> & unorderedStates)const;

    };

std::ostream& operator<<(std::ostream& out, const Automaton &automaton);
std::ostream& operator<<(std::ostream& out, const std::unordered_set<std::string> &str);
std::ostream& operator<<(std::ostream& out, const std::set<std::string> &str);
std::ostream& operator<<(std::ostream& out, std::stack<Transition> stack);

#endif //FSAUTOMATA_AUTOMATON_H
