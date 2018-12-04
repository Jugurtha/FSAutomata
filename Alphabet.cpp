//
// Created by LENOVO on 23/10/2018.
//

#include "Alphabet.h"

Alphabet::Alphabet(): letters({'a','b'}){}

Alphabet::Alphabet(const std::set<char> &letters): letters(letters){
}

bool Alphabet::contains(const char &letter) const { return letters.count(letter) == 1;}
