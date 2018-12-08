//
// Created by LENOVO on 03/12/2018.
//

#include "Transitions.h"

bool Transitions::insert(State *initial, const std::string word, State *final)
{
    auto pair = index_by_transition.emplace(initial,Word(word),final);
    return pair.second;
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

bool Transitions::exist(const std::string &initial, const std::string &word, const std::string &final)
{
    return index_by_transition.count(initial+word+final)==1;
}


std::pair<Transitions::const_iterator_by_initial,Transitions::const_iterator_by_initial> Transitions::findAll_by_initial(const std::string &initial)
{
    return index_by_initial.equal_range(initial);
}

std::pair<Transitions::const_iterator_by_final,Transitions::const_iterator_by_final> Transitions::findAll_by_final(const std::string &final)
{
	return index_by_final.equal_range(final);
}

std::pair<Transitions::const_iterator_by_initial_word,Transitions::const_iterator_by_initial_word> Transitions::findAll_by_initial_word(const std::string &initial, const std::string &word)
{
	return index_by_initial_word.equal_range(boost::make_tuple(initial,word));
}

std::pair<Transitions::const_iterator_by_word_final,Transitions::const_iterator_by_word_final> Transitions::findAll_by_word_final(const std::string &word, const std::string &final)
{
	return index_by_word_final.equal_range(boost::make_tuple(word,final));
}


size_t Transitions::erase(const std::string &initial, const std::string &word, const std::string &final)
{
    return index_by_transition.erase(initial+word+final);
}

size_t Transitions::erase(const Transition &transition)
{
    return index_by_transition.erase(transition.transition());
}

size_t Transitions::erase_by_initial(const std::string &initial)
{
    return index_by_initial.erase(initial);
}
Transitions::const_iterator_by_initial_word Transitions::erase_by_initial_word(const std::string &initial, const std::string &word)
{
    auto pIt = index_by_initial_word.equal_range(boost::make_tuple(initial,word));
    return index_by_initial_word.erase(pIt.first,pIt.second);
}
Transitions::const_iterator_by_word_final Transitions::erase_by_word_final(const std::string &word, const std::string &final)
{
    auto pIt = index_by_word_final.equal_range(boost::make_tuple(word,final));
    return index_by_word_final.erase(pIt.first,pIt.second);
}
size_t Transitions::erase_by_final(const std::string &final)
{
    return index_by_final.erase(final);
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