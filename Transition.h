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
    Transition(State *source, const Word &word, State *destination);
    Transition(State *source, const std::string &word, State *destination);

    const std::string source()const { return source_->id(); }
    State* sourcePtr()const { return source_; }
    const std::string word() const { return word_.word(); }
    const Word getWord() const { return word_; }
    const std::string destination() const { return destination_->id(); }
    State* destinationPtr() const { return destination_; }
    const std::string transition() const { return source_->id()+word_.word()+destination_->id(); }
private:
    State * source_;
    Word word_;
    State * destination_;
};

bool operator==(const Transition &t1, const Transition &t2);
std::ostream& operator<<(std::ostream& out, const Transition &transition);


#endif //FSAUTOMATA_INSTRUCTION_H
