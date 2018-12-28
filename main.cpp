
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/tokenizer.hpp>
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
//*/
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
//*
    std::cout << "\n--Remove Epsilon Transitions--\n\n";

    Automaton A01("A01",Alphabet({'a','b'}));

    A01.insertNewStates({"P","Q","R","Q1","R1","R2"});


    A01.setFinal(std::unordered_set<std::string>({"Q","R"}));

    A01.setInitial("P");


    A01.insertTransition("P", " ", "Q");
    A01.insertTransition("P", " ", "R");
    A01.insertTransition("Q", "a", "Q1");
    A01.insertTransition("Q1", "a", "Q");
    A01.insertTransition("R", "a", "R1");
    A01.insertTransition("R1", "a", "R2");
    A01.insertTransition("R2", "a", "R");

    std::cout << A01 << "\n";

    std::cout << A01.removeEpsilonTransitions() << "\n";

//*/

//*
    std::cout << "\n\n--To Simple--\n\n";

    Automaton A3("A3",Alphabet({'a','b'}));

    A3.insertNewStates({"P","Q","R","S","T"});

    A3.setFinal(std::unordered_set<std::string>({"Q","R"}));

    A3.setInitial("P");

    A3.insertTransition("P", "bab", "Q");
    A3.insertTransition("P", " ", "Q");
    A3.insertTransition("Q", "a", "R");
    A3.insertTransition("Q", "b", "S");


    std::cout << A3 << "\n";

    std::cout << A3.toSimple() << "\n";
//*/

    std::cout << "\n\n--To complete--\n\n";

    Automaton A2("A2",Alphabet({'a','b'}));

    A2.insertNewStates({"P","Q","R","Q1","R1","R2"});

    A2.setFinal(std::unordered_set<std::string>({"Q","R"}));

    A2.setInitial("P");


    A2.insertTransition("P", "b", "Q");
    A2.insertTransition("P", "a", "R");
    A2.insertTransition("Q", "a", "Q1");
    A2.insertTransition("Q1", "a", "Q");
    A2.insertTransition("R", "a", "R1");
    A2.insertTransition("R1", "a", "R2");
    A2.insertTransition("R2", "b", "R");

    std::cout << A2 << "\n";

    std::cout << A2.toComplete() << "\n";

/*
    std::string text="S0|S1|S2}";
    boost::tokenizer<boost::char_separator<char> > tok(text,boost::char_separator<char>("{},"));
    for(auto str : tok)
        std::cout << str << "\n";
*/

    std::cout << "\n\n--To Deterministic--\n\n";

    Automaton A5("A5",Alphabet({'a','b','c'}));

    A5.insertNewStates({"P","Q","R"});

    A5.setFinal(std::unordered_set<std::string>({"Q","R"}));

    A5.setInitial("P");

    A5.insertTransition("P", "a", "Q");
    A5.insertTransition("P", "b", "R");
    A5.insertTransition("P", "b", "Q");
    A5.insertTransition("R", "c", "Q");
    A5.insertTransition("Q", "a", "R");
    A5.insertTransition("Q", "a", "R");

    std::cout << A5 << "\n";

    std::cout << A5.toDeterministic() << "\n";


    std::cout << "\n\n--To Complementary--\n\n";

    Automaton A6("A6",Alphabet({'a','b','c'}));

    A6.insertNewStates({"P","Q","R"});

    A6.setFinal(std::unordered_set<std::string>({"Q","R"}));

    A6.setInitial("P");

    A6.insertTransition("P", "a", "Q");
    A6.insertTransition("P", "b", "R");
    A6.insertTransition("P", "b", "Q");
    A6.insertTransition("R", "c", "Q");
    A6.insertTransition("Q", "a", "R");
    A6.insertTransition("Q", "a", "R");

    std::cout << A6 << "\n";

    std::cout << A6.toComplementary() << "\n";



    std::cout << "\n\n--recognises--\n\n";

    Automaton A7("A7",Alphabet({'a','b','c'}));

    A7.insertNewStates({"P","Q","R"});

    A7.setFinal(std::unordered_set<std::string>({"Q","R"}));

    A7.setInitial("P");

    A7.insertTransition("P", "a", "Q");
    A7.insertTransition("P", "b", "R");
    A7.insertTransition("P", "b", "Q");
    A7.insertTransition("R", "c", "Q");
    A7.insertTransition("Q", "a", "R");

    std::cout << A7 << "\n";
    std::string str("bcacaca");
    while(str!="stop")
    {
        std::cout << A7.recognizes(Word(str)) << "\n";
        std::cin >> str;
    }


    return 0;
}