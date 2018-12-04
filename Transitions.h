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

    struct by_random_access{};
    struct by_transition{};
    struct by_initial{};
    struct by_initial_word{};
    struct by_word_final{};
    struct by_final{};

    typedef multi_index_container<
            Transition,
            indexed_by<
                    random_access<tag<by_random_access>>,
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
    >  Transitions_container;

    typedef Transitions_container::index<by_random_access>::type::iterator iterator_by_random_access;
    typedef Transitions_container::index<by_transition>::type::iterator iterator_by_transition;
    typedef Transitions_container::index<by_initial>::type::iterator iterator_by_initial;
    typedef Transitions_container::index<by_initial_word>::type::iterator iterator_by_initial_word;
    typedef Transitions_container::index<by_word_final>::type::iterator iterator_by_word_final;
    typedef Transitions_container::index<by_final>::type::iterator iterator_by_final;

    Transitions(){}
    Transitions(const Transitions &II):container_(II.container_){}
    Transitions(std::initializer_list<Transition> list):container_(list){}

    bool insert(State *initial, const std::string &word, State *final);
    size_t erase(const std::string &initial, const std::string &word, const std::string &final);
    size_t erase_by_initial(const std::string &initial);
    iterator_by_initial_word erase_by_initial_word(const std::string &initial, const std::string &word);
    iterator_by_word_final erase_by_word_final(const std::string &word, const std::string &final);
    size_t erase_by_final(const std::string &final);
    size_t size();

    const Transition &operator[](const int i);
    iterator_by_random_access begin();
    iterator_by_random_access end();

    iterator_by_transition operator[](boost::tuple<std::string, std::string, std::string> transition);
    bool exist(const std::string &initial, const std::string &word, const std::string &final);

    std::pair<iterator_by_initial,iterator_by_initial> findAll_by_initial(const std::string &initial);
    std::pair<iterator_by_final,iterator_by_final> findAll_by_final(const std::string &final);
    std::pair<iterator_by_initial_word,iterator_by_initial_word> findAll_by_initial_word(const std::string &initial, const std::string &word);
    std::pair<iterator_by_word_final,iterator_by_word_final> findAll_by_word_final(const std::string &word, const std::string &final);

private:
    Transitions_container container_;
    Transitions_container::index<by_random_access>::type& index_by_random_access = container_.get<by_random_access>();
    Transitions_container::index<by_transition>::type& index_by_transition = container_.get<by_transition>();
    Transitions_container::index<by_initial>::type& index_by_initial = container_.get<by_initial>();
    Transitions_container::index<by_initial_word>::type& index_by_initial_word = container_.get<by_initial_word>();
    Transitions_container::index<by_word_final>::type& index_by_word_final = container_.get<by_word_final>();
    Transitions_container::index<by_final>::type& index_by_final = container_.get<by_final>();

};


#endif //FSAUTOMATA_INSTRUCTIONS_H
