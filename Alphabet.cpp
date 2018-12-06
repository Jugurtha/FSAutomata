//
// Created by LENOVO on 23/10/2018.
//

#include "Alphabet.h"
#include <iostream>

Alphabet::Alphabet(): letters({'a','b'}){}

Alphabet::Alphabet(const std::unordered_set<char> &letters): letters(letters){
}

bool Alphabet::contains(const char &letter) const { return letters.count(letter) == 1;}

std::ostream& operator<<(std::ostream& out, const Alphabet &alphabet)
{
    out << "{ " ;
    const size_t size = alphabet.letters.size();
    auto it = alphabet.letters.cbegin();
    if(size>0)
    {
        out << *it;
        for(it++; it!=alphabet.letters.cend(); it++)
            out << ", " << *it;
    }
    out << " }";
    return out;
}

std::unordered_set<char>::const_iterator Alphabet::begin() const {
    return letters.cbegin();
}

std::unordered_set<char>::const_iterator Alphabet::end() const {
    return letters.cend();
}

size_t Alphabet::size() const {
    return letters.size();
}


