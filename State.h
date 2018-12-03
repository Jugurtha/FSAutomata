//
// Created by LENOVO on 03/12/2018.
//

#ifndef FSAUTOMATA_STATE_H
#define FSAUTOMATA_STATE_H


#include <string>
#include "boost/functional/hash.hpp"

class State {
public:
    State(std::string id):id_(id){}
    const std::string &id() const { return id_;}
private:
    std::string id_;
};


struct StateHasher
{
    size_t operator()(const State &s) const { return boost::hash<std::string>()(s.id()); }
    size_t operator()(State* const&s) const { return boost::hash<std::string>()(s->id()); }
    size_t operator()(const std::string &s) const { return boost::hash<std::string>()(s); }
};
struct StateEqual
{
    size_t operator()(State* const&s, std::string str) const { return s->id()==str; }
    size_t operator()(std::string str, State* const&s) const { return s->id()==str; }
    size_t operator()(std::string str1, std::string str2) const { return str1==str2; }
};


#endif //FSAUTOMATA_STATE_H
