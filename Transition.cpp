//
// Created by LENOVO on 03/12/2018.
//

#include "Transition.h"

Transition::Transition(State *initial, const Word &word, State *final) : initial_(initial), word_(word), final_(final)
{

}

Transition::Transition(State *initial, const std::string &word, State *final) : initial_(initial), word_(word), final_(final) {

}

std::ostream& operator<<(std::ostream &out, const Transition &transition) {
    out  << "(" << transition.initial() << ", " << transition.word() << ", " << transition.final() << ")";
    return out;
}

bool operator==(const Transition &t1, const Transition &t2)
{
    return (t1.initial() == t2.initial()) && (t1.word() == t2.word()) && (t1.final() == t2.final());
}

