//
// Created by LENOVO on 05/12/2018.
//

#include "Automaton.h"

Automaton::Automaton(const std::string &id, Alphabet X): id_(id), X(X) {}

bool Automaton::insertTransition(const std::string &initial, const std::string &word, const std::string &final) {
    if( !S.exist(initial) || !S.exist(final) )
        return false;
    return II.insert(S[initial], word, S[final]);
}

bool Automaton::insertNewState(const std::string &state) {
    return S.insert(state);
}

bool Automaton::setInitial(const std::string &state) {
    if(!S.exist(state))
        return false;

    auto p = Sinit.insert(state);
    return p.second;
}

bool Automaton::setFinal(const std::string &state) {
    if(!S.exist(state))
        return false;

    auto p = Sfinal.insert(state);
    return p.second;
}

const Alphabet &Automaton::getX() const {
    return X;
}

const std::unordered_set<std::string> Automaton::getStates(){
    std::unordered_set<std::string> set;
    for(auto s : S.getStates())
        set.insert(s);
    return set;
}

const std::unordered_set<std::string> &Automaton::getSinit() const {
    return Sinit;
}

const Transitions &Automaton::getII() const {
    return II;
}

const std::unordered_set<std::string> &Automaton::getSfinal() const {
    return Sfinal;
}

bool Automaton::setFinal(std::unordered_set<std::string> states) {
    for(auto s : states)
        if(!S.exist(s))
            return false;
    Sfinal.insert(states.begin(),states.end());
    return true;
}

bool Automaton::setInitial(std::unordered_set<std::string> states) {
    for(auto s : states)
        if(!S.exist(s))
            return false;
    Sinit.insert(states.begin(),states.end());
    return true;
}

std::ostream& operator<<(std::ostream& out, const Automaton &automaton)
{
    out << automaton.id() << " <" << "\n";
    out << "X = " << automaton.X << ",\n";
    out << "S = "  << automaton.S << ",\n";
    out << "Sinit = "  << automaton.Sinit << ",\n";
    out << "II = "  << automaton.II << ",\n";
    out << "Sfinal = "  << automaton.Sfinal << " >";
    return out;
}


std::ostream& operator<<(std::ostream& out, const std::unordered_set<std::string> &str)
{
    out << "{ " ;
    const size_t size = str.size();
    auto it = str.cbegin();
    if(size>0)
    {
        out << *it;
        for(it++; it!=str.cend(); it++)
            out << ", " << *it;
    }
    out << " }";
    return out;
}



