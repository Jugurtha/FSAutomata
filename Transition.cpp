//
// Created by LENOVO on 03/12/2018.
//

#include "Transition.h"

Transition::Transition(State *source, const Word &word, State *destination) : source_(source), word_(word), destination_(destination)
{

}

Transition::Transition(State *source, const std::string &word, State *destination) : source_(source), word_(word), destination_(destination) {

}

std::ostream& operator<<(std::ostream &out, const Transition &transition) {
    out  << "(" << transition.source() << ", " << transition.word() << ", " << transition.destination() << ")";
    return out;
}

bool operator==(const Transition &t1, const Transition &t2)
{
    return (t1.source() == t2.source()) && (t1.word() == t2.word()) && (t1.destination() == t2.destination());
}

