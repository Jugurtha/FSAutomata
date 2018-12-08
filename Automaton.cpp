//
// Created by LENOVO on 05/12/2018.
//

#include "Automaton.h"

Automaton::Automaton(const std::string &id, Alphabet X): id_(id), X(X) {}

Automaton::Automaton(const std::string &id, const Alphabet &X, const States &S,
                     const std::unordered_set<std::string> &Sinit, const Transitions &II,
                     const std::unordered_set<std::string> &Sfinal) : id_(id), X(X)
{
    for(auto s : S)
    {
        this->S.insert(s->id());
        if(Sinit.count(s->id())==1)
            this->Sinit.insert(s->id());
        if(Sfinal.count(s->id())==1)
            this->Sfinal.insert(s->id());
    }
    for(auto t : II)
        this->II.insert(S[t.initial()],t.word(),S[t.final()]);
}

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
    out << automaton.id() << "\t<" << "\n";
    out << "\tX = " << automaton.X << ",\n";
    out << "\tS = "  << automaton.S << ",\n";
    out << "\tSinit = "  << automaton.Sinit << ",\n";
    out << "\tII = "  << automaton.II << ",\n";
    out << "\tSfinal = "  << automaton.Sfinal << "\n\t>";
    return out;
}

void Automaton::toSimple() {
    toPartiallyGeneralized();
    removeEpsilonTransitions();
}

void Automaton::toDeterministic() {
    toSimple();
    //...
}

void Automaton::tocomplementary() {

}

void Automaton::toComplete() {
    //At least simple
}

const Automaton Automaton::toPartiallyGeneralized() const//-> |word|<=1
{
    Automaton temp(id_,X,S,Sinit,II,Sfinal);
    static int index = 0;
    for(auto t : II)
    {
        if(t.word().size()>1)
        {
            Transition transition(t);//We make a copy...
            if(temp.II.erase(t)!=1)//We erase the transition with |word|>1
            {
                std::cout << "toPartiallyGeneralized failed on erasing transition : "+ t.transition() +".\n";
                return  temp;
            }
            State *ptrPreviousState = nullptr, *ptrNewState = nullptr;
            int i = 0;
            size_t size =  transition.word().size();
            auto initial = transition.initial();
            for(i=0;i<size-1;i++)
            {
                std::string newState(transition.initial()+"_"+std::to_string(index+1));
                if(!temp.S.insert(newState))
                {
                    std::cout << "toPartiallyGeneralized failed on insertion of new state : " + newState + ".\n";
                    return  temp;
                } else
                    index++;
                ptrPreviousState = temp.S[initial];
                ptrNewState =  temp.S[newState];
                if(ptrNewState == nullptr || ptrPreviousState == nullptr)
                {
                    std::cout << "toPartiallyGeneralized failed on retrieval of states : " + initial + ", " + newState + ".\n";
                    return  temp;
                }
                temp.II.insert(ptrPreviousState,transition.getWord()[i],ptrNewState);
                initial = newState;
            }
            temp.II.insert(ptrNewState,transition.getWord()[i],transition.finalPtr());
        }
    }
    return temp;
}

void Automaton::removeEpsilonTransitions() {

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







