//
// Created by LENOVO on 03/12/2018.
//

#ifndef FSAUTOMATA_INSTRUCTION_H
#define FSAUTOMATA_INSTRUCTION_H

#include <iostream>
#include "boost/functional/hash/hash.hpp"

#include "Word.h"
#include "State.h"



class Transition {
public:
    Transition(State *initial, const Word &word, State *final);
    Transition(State *initial, const std::string &word, State *final);

    const std::string &initial()const { return initial_->id(); }
    const std::string &word() const { return word_.word(); }
    const std::string &final() const { return final_->id(); }
private:
    State * initial_;
    Word word_;
    State * final_;
};

bool operator==(const Transition &t1, const Transition &t2);
std::ostream& operator<<(std::ostream& out, const Transition &transition);

struct TransitionKey
{
    TransitionKey(const std::string &initial, const std::string &word, const std::string &final);
    std::string initial;
    std::string word;
    std::string final;
};

struct TransitionKeyEqual {
    bool operator()( const Transition &t1, const TransitionKey &t2) const;
    bool operator()(const TransitionKey &t2,  const Transition &t1) const;
};
struct TransitionHasher
{
    size_t operator()(const Transition &t) const { return boost::hash<std::string>()(t.initial() + t.word() + t.final()); }
    size_t operator()(const TransitionKey &tk) const { return boost::hash<std::string>()(tk.initial + tk.word + tk.final); }
    size_t operator()(const State *initial, const Word &word,const State *final) const { return boost::hash<std::string>()(initial->id() + word.word() + final->id()); }
};


#endif //FSAUTOMATA_INSTRUCTION_H
