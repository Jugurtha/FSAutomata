//
// Created by LENOVO on 03/12/2018.
//

#ifndef FSAUTOMATA_WORD_H
#define FSAUTOMATA_WORD_H

#include <string>
class Word {
public:
    Word(std::string word):word_(word){}
    Word mirror();
    const std::string &word()const{ return word_; }
    bool isEpsilon()const{ return word_.empty() || word_[0]==' ';}
    std::string::const_iterator begin()const{ return word_.cbegin();}
    std::string::const_iterator end()const{ return word_.cend();}
    const std::string operator[](size_t i)const{ std::string c; c.push_back(word_[i]); return c;}
    size_t size()const{ return word_.size();}
private:
   std::string word_;
};


#endif //FSAUTOMATA_WORD_H
