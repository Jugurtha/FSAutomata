//
// Created by LENOVO on 03/12/2018.
//

#ifndef FSAUTOMATA_INSTRUCTIONS_H
#define FSAUTOMATA_INSTRUCTIONS_H

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include "Transition.h"

using namespace boost;
using namespace multi_index;

class Transitions {
public:
    struct by_transition{};
    struct by_initial{};
    struct by_initial_word{};
    struct by_word_final{};
    struct by_final{};

    typedef multi_index_container<
            Transition,
            indexed_by<
                    random_access<>,
//                    hashed_unique< tag<by_transition>, identity< Transition >, TransitionHasher >,
                    hashed_unique< tag<by_transition>, const_mem_fun<Transition, const std::string, &Transition::transition> >,
                    hashed_non_unique< tag<by_initial>, const_mem_fun<Transition, const std::string,&Transition::initial> >,
                    hashed_non_unique< tag<by_final>, const_mem_fun<Transition, const std::string,&Transition::final> >,
                    hashed_non_unique< tag<by_initial_word>,
                                       composite_key< Transition,
                                                      const_mem_fun<Transition, const std::string,&Transition::initial>,
                                                      const_mem_fun<Transition, const std::string,&Transition::word>
                                                    >
                                     >,
                    hashed_non_unique< tag<by_word_final>,
                                       composite_key< Transition,
                                                      const_mem_fun<Transition, const std::string,&Transition::word>,
                                                      const_mem_fun<Transition, const std::string,&Transition::final>
                                                    >
                                     >

            >
    >  Instructions_container;


    Instructions_container container;

};


#endif //FSAUTOMATA_INSTRUCTIONS_H
