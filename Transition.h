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

    const std::string initial()const { return initial_->id(); }
    State* initialPtr()const { return initial_; }
    const std::string word() const { return word_.word(); }
    const Word getWord() const { return word_; }
    const std::string final() const { return final_->id(); }
    State* finalPtr() const { return final_; }
    const std::string transition() const { return initial_->id()+word_.word()+final_->id(); }
private:
    State * initial_;
    Word word_;
    State * final_;
};

bool operator==(const Transition &t1, const Transition &t2);
std::ostream& operator<<(std::ostream& out, const Transition &transition);


#endif //FSAUTOMATA_INSTRUCTION_H
