//
// Created by LENOVO on 05/12/2018.
//

#include "States.h"


bool States::insert(const std::string &initial)
{
    auto pair = index_by_state.insert(new State(initial));
    return pair.second;
}

size_t States::erase(const std::string &initial)
{
    auto it = index_by_state.find(initial);
    if(it==index_by_state.end())
        return 0;
    auto p = *it;
    auto ret = index_by_state.erase(initial);
    delete p;
    return ret;
}


State* States::operator[](const int i)
{
    return index_by_random_access[i];
}

States::iterator_by_random_access States::begin()
{
    return index_by_random_access.begin();
}

States::iterator_by_random_access States::end()
{
    return index_by_random_access.end();
}

State* States::operator[](const std::string &initial)
{
    auto it = index_by_state.find(initial);
    return it==index_by_state.end()? nullptr:*it;
}

bool States::exist(const std::string &initial)
{
    return index_by_state.count(initial)==1;
}

size_t States::size()
{
    return container_.size();
}

States::~States()
{
    for(auto s : *this)
        if(s!= nullptr)
            delete s;

}



