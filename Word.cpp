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
