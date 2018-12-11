//
// Created by LENOVO on 03/12/2018.
//

#include "Transitions.h"

bool Transitions::insert(State *source, const std::string word, State *destination)
{
    auto pair = index_by_transition.emplace(source,Word(word),destination);
    return pair.second;
}

bool Transitions::insert(const Transition &transition)
{
    return insert(transition.sourcePtr(),transition.word(), transition.destinationPtr());
}

size_t Transitions::size() const
{
    return index_by_random_access.size();
}

const Transition &Transitions::operator[](const int i)const
{
    return index_by_random_access[i];
}

Transitions::const_iterator_by_transition Transitions::operator[](boost::tuple<std::string, std::string, std::string> transition)
{
    return index_by_transition.find(boost::get<0>(transition)+boost::get<1>(transition)+boost::get<2>(transition));
}

Transitions::const_iterator_by_random_access Transitions::begin() const
{
    return index_by_random_access.cbegin();
}

Transitions::const_iterator_by_random_access Transitions::end()const
{
    return index_by_random_access.cend();
}

bool Transitions::exist(const std::string &source, const std::string &word, const std::string &destination)
{
    return index_by_transition.count(source+word+destination)==1;
}


std::pair<Transitions::const_iterator_by_source,Transitions::const_iterator_by_source> Transitions::findAll_by_source(const std::string &source)const
{
    return index_by_source.equal_range(source);
}

std::pair<Transitions::const_iterator_by_destination,Transitions::const_iterator_by_destination> Transitions::findAll_by_destination(const std::string &destination)const
{
	return index_by_destination.equal_range(destination);
}

std::pair<Transitions::const_iterator_by_source_word,Transitions::const_iterator_by_source_word> Transitions::findAll_by_source_word(const std::string &source, const std::string &word)const
{
	return index_by_source_word.equal_range(boost::make_tuple(source,word));
}

std::pair<Transitions::const_iterator_by_word_destination,Transitions::const_iterator_by_word_destination> Transitions::findAll_by_word_destination(const std::string &word, const std::string &destination)const
{
	return index_by_word_destination.equal_range(boost::make_tuple(word,destination));
}


size_t Transitions::erase(const std::string &source, const std::string &word, const std::string &destination)
{
    return index_by_transition.erase(source+word+destination);
}

size_t Transitions::erase(const Transition &transition)
{
    return index_by_transition.erase(transition.transition());
}

size_t Transitions::erase_by_source(const std::string &source)
{
    return index_by_source.erase(source);
}
Transitions::const_iterator_by_source_word Transitions::erase_by_source_word(const std::string &source, const std::string &word)
{
    auto pIt = index_by_source_word.equal_range(boost::make_tuple(source,word));
    return index_by_source_word.erase(pIt.first,pIt.second);
}
Transitions::const_iterator_by_word_destination Transitions::erase_by_word_destination(const std::string &word, const std::string &destination)
{
    auto pIt = index_by_word_destination.equal_range(boost::make_tuple(word,destination));
    return index_by_word_destination.erase(pIt.first,pIt.second);
}
size_t Transitions::erase_by_destination(const std::string &destination)
{
    return index_by_destination.erase(destination);
}

const std::unordered_set<std::string> Transitions::getTransitions() const
{
    std::unordered_set<std::string> transitions;
    for(auto t : *this)
        transitions.insert(t.transition());
    return transitions;
}

std::ostream& operator<<(std::ostream& out, const Transitions &transitions)
{
    out << "{ " ;
    const size_t size = transitions.size();
    if(size>0)
    {
        if(size==1)
            out << transitions[0];
        else
        {
            out << "\n\t\t" << transitions[0];
            for(int i = 1; i < size; ++i)
                out << ", \n\t\t" << transitions[i];
        }

    }
    out << " }";
    return out;
}