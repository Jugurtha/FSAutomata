//
// Created by LENOVO on 03/12/2018.
//

#include "Word.h"

Word Word::mirror()
{
    std::string mirrorWord;
    for(auto it = word_.rbegin(); it!=word_.rend();it++)
        mirrorWord.push_back(*it);
    return Word(mirrorWord);
}

Word::Word(std::string word){
    if(word.empty() || word[0]==' ' || word.find(" ")!=word.npos)
        word_ = " ";
    else
        word_ = word;
}
