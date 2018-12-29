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

#include <unordered_set>
#include <string>

#include "Transition.h"

using namespace boost;
using namespace multi_index;

class Transitions {
public:

    struct by_random_access{};
    struct by_transition{};
    struct by_source{};
    struct by_source_word{};
    struct by_word_destination{};
    struct by_destination{};

    typedef multi_index_container<
            Transition,
            indexed_by<
                    random_access<tag<by_random_access>>,
                    hashed_unique< tag<by_transition>, const_mem_fun<Transition, const std::string, &Transition::transition> >,
                    hashed_non_unique< tag<by_source>, const_mem_fun<Transition, const std::string,&Transition::source> >,
                    hashed_non_unique< tag<by_destination>, const_mem_fun<Transition, const std::string,&Transition::destination> >,
                    hashed_non_unique< tag<by_source_word>,
                                       composite_key< Transition,
                                                      const_mem_fun<Transition, const std::string,&Transition::source>,
                                                      const_mem_fun<Transition, const std::string,&Transition::word>
                                                    >
                                     >,
                    hashed_non_unique< tag<by_word_destination>,
                                       composite_key< Transition,
                                                      const_mem_fun<Transition, const std::string,&Transition::word>,
                                                      const_mem_fun<Transition, const std::string,&Transition::destination>
                                                    >
                                     >

            >
    >  Transitions_container;

    typedef Transitions_container::index<by_random_access>::type::const_iterator const_iterator_by_random_access;
    typedef Transitions_container::index<by_transition>::type::const_iterator const_iterator_by_transition;
    typedef Transitions_container::index<by_source>::type::const_iterator const_iterator_by_source;
    typedef Transitions_container::index<by_source_word>::type::const_iterator const_iterator_by_source_word;
    typedef Transitions_container::index<by_word_destination>::type::const_iterator const_iterator_by_word_destination;
    typedef Transitions_container::index<by_destination>::type::const_iterator const_iterator_by_destination;

    Transitions(){}
    Transitions(const Transitions &II):container_(II.container_){}
    Transitions(std::initializer_list<Transition> list):container_(list){}

    bool insert(State *source, const std::string word, State *destination);
    bool insert(const Transition &transition);
    size_t erase(const std::string &source, const std::string &word, const std::string &destination);
    size_t erase(const Transition &transition);
    size_t erase_by_source(const std::string &source);
    const_iterator_by_source_word erase_by_source_word(const std::string &source, const std::string &word);
    const_iterator_by_word_destination erase_by_word_destination(const std::string &word, const std::string &destination);
    size_t erase_by_destination(const std::string &destination);
    size_t size()const;

    const Transition &operator[](const int i)const;
    const_iterator_by_random_access begin() const;
    const_iterator_by_random_access end() const;
    const std::unordered_set<std::string> getTransitions() const;

    const_iterator_by_transition operator[](boost::tuple<std::string, std::string, std::string> transition);
    bool exist(const std::string &source, const std::string &word, const std::string &destination);

    std::pair<const_iterator_by_source,const_iterator_by_source> findAll_by_source(const std::string &source)const;
    std::pair<const_iterator_by_destination,const_iterator_by_destination> findAll_by_destination(const std::string &destination)const;
    std::pair<const_iterator_by_source_word,const_iterator_by_source_word> findAll_by_source_word(const std::string &source, const std::string &word)const;
    std::pair<const_iterator_by_word_destination,const_iterator_by_word_destination> findAll_by_word_destination(const std::string &word, const std::string &destination)const;
    std::pair<const_iterator_by_source_word,const_iterator_by_source_word> findAll_by_source_word(const std::string &source, const char &word)const;
    std::pair<const_iterator_by_word_destination,const_iterator_by_word_destination> findAll_by_word_destination(const char &word, const std::string &destination)const;

private:
    Transitions_container container_;
    Transitions_container::index<by_random_access>::type& index_by_random_access = container_.get<by_random_access>();
    Transitions_container::index<by_transition>::type& index_by_transition = container_.get<by_transition>();
    Transitions_container::index<by_source>::type& index_by_source = container_.get<by_source>();
    Transitions_container::index<by_source_word>::type& index_by_source_word = container_.get<by_source_word>();
    Transitions_container::index<by_word_destination>::type& index_by_word_destination = container_.get<by_word_destination>();
    Transitions_container::index<by_destination>::type& index_by_destination = container_.get<by_destination>();

};

std::ostream& operator<<(std::ostream& out, const Transitions &transitions);

#endif //FSAUTOMATA_INSTRUCTIONS_H
