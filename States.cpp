//
// Created by LENOVO on 05/12/2018.
//

#include "States.h"


bool States::insert(const std::string &state)
{
    auto pair = index_by_state.insert(new State(state));
    return pair.second;
}

size_t States::erase(const std::string &state)
{
    auto it = index_by_state.find(state);
    if(it==index_by_state.end())
        return 0;
    auto p = *it;
    auto ret = index_by_state.erase(state);
    delete p;
    return ret;
}


State* States::operator[](const int i)const
{
    return index_by_random_access[i];
}

States::const_iterator_by_random_access States::begin() const
{
    return index_by_random_access.begin();
}

States::const_iterator_by_random_access States::end() const
{
    return index_by_random_access.end();
}

State* States::operator[](const std::string &state)
{
    auto it = index_by_state.find(state);
    return it==index_by_state.end()? nullptr:*it;
}

std::unordered_set<std::string> States::getStates() const
{
    std::unordered_set<std::string> states;
    for(auto ps : *this)
        states.insert(ps->id());
    return states;
}

bool States::exist(const std::string &state)
{
    return index_by_state.count(state)==1;
}

size_t States::size()const
{
    return container_.size();
}

States::~States()
{
    for(auto s : *this)
        if(s!= nullptr)
            delete s;

}


std::ostream& operator<<(std::ostream& out, const States &states)
{
    out << "{ " ;
    const size_t size = states.size();
    if(size>0)
    {
        out << *states[0];
        for(int i = 1; i < size; ++i)
            out << ", " << *states[i];
    }
    out << " }";
    return out;
}



