//
// Created by LENOVO on 05/12/2018.
//

#ifndef FSAUTOMATA_STATES_H
#define FSAUTOMATA_STATES_H


#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include <unordered_set>

#include "State.h"

using namespace boost;
using namespace multi_index;

class States {
public:

    struct by_random_access{};
    struct by_state{};

    typedef multi_index_container<
                                    State*,
                                    indexed_by<
                                                random_access<tag<by_random_access>>,
                                                hashed_unique< tag<by_state>, const_mem_fun<State, const std::string&, &State::id> >
                                               >
                                  > States_container;
    typedef States_container::index<by_random_access>::type::const_iterator const_iterator_by_random_access;
    typedef States_container::index<by_state>::type::const_iterator const_iterator_by_state;

    States(){}
    States(const States &states)= delete;
    ~States();

    bool insert(const std::string &state);
    bool insert(State *state);
    size_t erase(const std::string &state);


    State* operator[](const int i)const;
    const_iterator_by_random_access begin() const;
    const_iterator_by_random_access end() const;
    std::unordered_set<std::string> getStates() const;

    State* operator[](const std::string &state);
    bool exist(const std::string &state);
    size_t size()const;


private:
    States_container container_;
    States_container::index<by_random_access>::type& index_by_random_access = container_.get<by_random_access>();
    States_container::index<by_state>::type& index_by_state = container_.get<by_state>();

};

std::ostream& operator<<(std::ostream& out, const States &states);

#endif //FSAUTOMATA_STATES_H
