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


#endif //FSAUTOMATA_STATE_H
