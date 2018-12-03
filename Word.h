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
private:
   std::string word_;
};


#endif //FSAUTOMATA_WORD_H
