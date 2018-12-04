//
// Created by LENOVO on 23/10/2018.
//

#ifndef FSA_ALPHABET_H
#define FSA_ALPHABET_H

#include <set>

class Alphabet {
public:
    Alphabet();
    explicit Alphabet(const std::set<char> &letters);
    bool contains(const char &letter) const;

private:
    const std::set<char> letters;

};


#endif //FSA_ALPHABET_H
