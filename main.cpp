
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <string>
#include <iostream>
#include "Word.h"
#include "Alphabet.h"
#include "Transitions.h"
#include "States.h"


int main() {

    Word w("abcd");
    std::cout << w.word() << " : " << w.mirror().word() << "\n";

    std::cout << "\n--Alphabet check--\n\n";

    Alphabet X({'a', 'b', 'c'});
    std::cout << X.contains('c') << "\n";

    std::cout << "\n--Insert 5, one fails--\n\n";

    States S;
    std::cout << S.insert("S0") << "\n";
    std::cout << "!" << S.insert("S0") << "\n";
    std::cout << S.insert("S1") << "\n";
    std::cout << S.insert("S2") << "\n";
    std::cout << S.insert("S3") << "\n";
    std::cout << S.insert("S4") << "\n";

    std::cout << "\n--Print all--\n\n";

    for (auto it : S)//prints them all with different syntax
        std::cout << *it << "\n";

    std::cout<< "\n" << "Size : " << S.size() << "\n\n";
    std::cout << "S5 doesn't exist : " << S.exist("S5") << "\n\n";

    for (int i = 0; i < S.size(); ++i)
    {
        std::cout << "S[" << i << "] = " << *S[i] << "\n";
        std::cout << "@S[0] == S[\"S0\"] : " << (S[i] == S["S"+std::to_string(i)]) << "\n";
    }

    std::cout<< "\n" << "Erase S4 : " << S.erase("S4") << "\n\n";

    for (auto it : S)//prints them all with different syntax
        std::cout << *it << "\n";

    std::cout << "\n--Create Transitions--\n\n";

    Transitions II;
    std::cout << II.insert(S["S0"],"a",S["S1"]) << "\n";
    std::cout << II.insert(S["S0"],"b",S["S2"]) << "\n";
    std::cout << II.insert(S["S0"],"b",S["S1"]) << "\n";
    std::cout << II.insert(S["S1"],"b",S["S1"]) << "\n";
    std::cout << II.insert(S["S1"],"b",S["S2"]) << "\n";
    std::cout << II.insert(S["S2"],"b",S["S3"]) << "\n";
    std::cout << "!" << II.insert(S["S0"],"b",S["S2"]) << "\n";//Shouldn't be inserted

    std::cout << "\n--Print all one--\n\n";

    for(int i = 0;i< II.size();i++)//prints them all
        std::cout << II[i] << "\n";

    std::cout << "\n--Print all two--\n\n";

    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--find S1-b->S2 by_transition--\n\n";

    std::cout << *II[boost::make_tuple("S1", "b", "S2")] << "\n" ;

    std::cout << "\n-- S2-b->S1 doesn't exist--\n\n";

    std::cout << II.exist("S2", "b", "S1") << "\n";

    std::cout << "\n--find all initial S1 by_initial--\n\n";

    auto pairIt = II.findAll_by_initial("S1");
    for(auto it = pairIt.first; it != pairIt.second; it++)
        std::cout << *it << "\n";

    std::cout << "\n--find all final S1 by_final--\n\n";

    auto pairIt2 = II.findAll_by_final("S1");
    for(auto it = pairIt2.first; it != pairIt2.second; it++)
        std::cout << *it << "\n";

    std::cout << "\n--find all final S1-b-> by_initial_word--\n\n";

    auto pairIt3 = II.findAll_by_initial_word("S1","b");
    for(auto it = pairIt3.first; it != pairIt3.second; it++)
        std::cout << *it << "\n";

    std::cout << "\n--find all final -b->S1 by_word_final--\n\n";

    auto pairIt4 = II.findAll_by_word_final("b","S1");
    for(auto it = pairIt4.first; it != pairIt4.second; it++)
        std::cout << *it << "\n";

    std::cout << "\n--Before Erasing--\n\n";

    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase S1-b->S2 by_transition--\n\n";

    std::cout << II.erase("S1", "b", "S2") << "\n";
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase S1 by_initial--\n\n";

    std::cout << II.erase_by_initial("S1") << "\n";
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase S2 by_final--\n\n";

    std::cout << II.erase_by_final("S2") << "\n";
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";


    std::cout << "\n--Erase S0-a-> by_initial_word--\n\n";

    II.erase_by_initial_word("S0","a");
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase b->S1 by_word_final--\n\n";

    II.erase_by_word_final("b","S1");
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";



    return 0;
}