//
// Created by LENOVO on 03/12/2018.
//

#include "State.h"

std::ostream& operator<<(std::ostream& out, const State &state)
{
    out  << state.id();
    return out;
}

bool operator==(const State &s1, const State &s2)
{
    return s1.id()==s2.id();
}