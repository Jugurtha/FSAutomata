//
// Created by LENOVO on 23/10/2018.
//

#ifndef FSA_ALPHABET_H
#define FSA_ALPHABET_H

#include <unordered_set>
#include <vector>

class Alphabet {
public:
    Alphabet();
    explicit Alphabet(const std::unordered_set<char> &letters);
    bool contains(const char &letter) const;
    friend std::ostream& operator<<(std::ostream& out, const Alphabet &alphabet);
    std::unordered_set<char>::const_iterator begin()const;
    std::unordered_set<char>::const_iterator end()const;
    size_t size()const;

private:
    const std::unordered_set<char> letters;

};

std::ostream& operator<<(std::ostream& out, const Alphabet &alphabet);


#endif //FSA_ALPHABET_H
