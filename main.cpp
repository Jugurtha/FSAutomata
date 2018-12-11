
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include "Word.h"
#include "Alphabet.h"
#include "Transitions.h"
#include "States.h"
#include "Automaton.h"


std::string randStr(const Alphabet &alphabet, size_t length)
{
    std::mt19937_64 gen{std::random_device{}()};
    std::uniform_int_distribution<size_t > dist{0, alphabet.size()-1};
    std::vector<char> v(alphabet.begin(),alphabet.end());
    std::string str;
    for (size_t i = 0; i < length; ++i)
        str.push_back(v[dist(gen)]);
    return str;
}

int main() {
    srand(time(NULL));
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

    std::cout << "\n--find all source S1 by_source--\n\n";

    auto pairIt = II.findAll_by_source("S1");
    for(auto it = pairIt.first; it != pairIt.second; it++)
        std::cout << *it << "\n";

    std::cout << "\n--find all destination S1 by_destination--\n\n";

    auto pairIt2 = II.findAll_by_destination("S1");
    for(auto it = pairIt2.first; it != pairIt2.second; it++)
        std::cout << *it << "\n";

    std::cout << "\n--find all destination S1-b-> by_source_word--\n\n";

    auto pairIt3 = II.findAll_by_source_word("S1","b");
    for(auto it = pairIt3.first; it != pairIt3.second; it++)
        std::cout << *it << "\n";

    std::cout << "\n--find all destination -b->S1 by_word_destination--\n\n";

    auto pairIt4 = II.findAll_by_word_destination("b","S1");
    for(auto it = pairIt4.first; it != pairIt4.second; it++)
        std::cout << *it << "\n";

    std::cout << "\n--Before Erasing--\n\n";

    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase S1-b->S2 by_transition--\n\n";

    std::cout << II.erase("S1", "b", "S2") << "\n";
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase S1 by_source--\n\n";

    std::cout << II.erase_by_source("S1") << "\n";
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase S2 by_destination--\n\n";

    std::cout << II.erase_by_destination("S2") << "\n";
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";


    std::cout << "\n--Erase S0-a-> by_source_word--\n\n";

    II.erase_by_source_word("S0","a");
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase b->S1 by_word_destination--\n\n";

    II.erase_by_word_destination("b","S1");
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Automaton--\n\n";

    Automaton A("A1",Alphabet({'a','b','c'}));

    for (int j = 0; j < 5; ++j)
        A.insertNewState("S"+std::to_string(j));

    std::unordered_set<std::string>  finalStates({"S0","S1"});
    A.setFinal(finalStates);

    std::unordered_set<std::string>  initialStates({"S3","S4"});
    A.setInitial(initialStates);

    for (int k = 0; k < 6; ++k)
        A.insertTransition("S"+std::to_string(rand()%5), randStr(A.getX(),k%3 +1), "S"+std::to_string(rand()%5));
/*
    A.insertTransition("S0", "abc", "S1");
    A.insertTransition("S0", "ac", "S1");
    A.insertTransition("S0", "a", "S1");
    A.insertTransition("S0", "b", "S1");
*/
    std::cout << A << "\n";

    std::cout << "\n--to Partially Generalized--\n\n";

    std::cout << A.toPartiallyGeneralized() << "\n";

//*
    std::cout << "\n--Remove Epsilon Transitions--\n\n";

    Automaton A1("A1",Alphabet({'0','1','2'}));

    for (int j = 0; j < 3; ++j)
        A1.insertNewState("S"+std::to_string(j));

    std::unordered_set<std::string>  finalStates1({"S2"});
    A1.setFinal(finalStates1);

    std::unordered_set<std::string>  initialStates1({"S0"});
    A1.setInitial(initialStates1);

    A1.insertTransition("S0", "0", "S0");
    A1.insertTransition("S0", " ", "S1");
    A1.insertTransition("S1", "1", "S1");
    A1.insertTransition("S1", "", "S2");
    A1.insertTransition("S2", "2", "S2");

    std::cout << A1 << "\n";

    std::cout << A1.removeEpsilonTransitions() << "\n";
//*/
/*
    std::cout << "\n--Remove Epsilon Transitions--\n\n";

    Automaton A1("A1",Alphabet({'a','b'}));

    A1.insertNewStates({"P","Q","R","Q1","R1","R2"});

    std::unordered_set<std::string>  finalStates1({"Q","R"});
    A1.setFinal(finalStates1);

    std::unordered_set<std::string>  initialStates1({"P"});
    A1.setInitial(initialStates1);


    A1.insertTransition("P", " ", "Q");
    A1.insertTransition("P", " ", "R");
    A1.insertTransition("Q", "a", "Q1");
    A1.insertTransition("Q1", "a", "Q");
    A1.insertTransition("R", "a", "R1");
    A1.insertTransition("R1", "a", "R2");
    A1.insertTransition("R2", "a", "R");

    std::cout << A1 << "\n";

    std::cout << A1.removeEpsilonTransitions() << "\n";

//*/

    return 0;
}