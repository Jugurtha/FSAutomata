//
// Created by LENOVO on 29/12/2018.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <sstream>
#include <iostream>
#include "Automaton.h"

TEST_CASE( "Alphabet check" ) {

    Alphabet X({'a', 'b', 'c'});
    SECTION("Verifying contains")
    {
        REQUIRE(X.contains('c'));
    }

}

TEST_CASE("Word Check")
{
    Word w("abcd");

    SECTION("Mirror of word")
    {
        REQUIRE(w.mirror().word() == "dcba");
    }
}

TEST_CASE("States Check")
{
    States S;
    SECTION("Insert 5 States, one fails")
    {
        REQUIRE(S.insert("S0"));
        REQUIRE_FALSE(S.insert("S0"));
        REQUIRE(S.insert("S1"));
        REQUIRE(S.insert("S2"));
        REQUIRE(S.insert("S3"));
        REQUIRE(S.insert("S4"));
    }

    S.insert("S0");
    S.insert("S1");
    S.insert("S2");
    S.insert("S3");
    S.insert("S4");

    SECTION("Test Print And Iterators of States")
    {
        std::ostringstream out;

        SECTION("For each Style for")
        {
            for(auto it : S)
                out << *it << ",";

            REQUIRE( out.str() == "S0,S1,S2,S3,S4,");
        }
        SECTION("Range Style for")
        {
            for(int i=0;i < S.size();i++)
                out << *S[i] << ",";

            REQUIRE( out.str() == "S0,S1,S2,S3,S4,");
        }
    }
    SECTION("Square Brackets")
    {
        REQUIRE(*S[0]==State("S0"));
        REQUIRE(*S["S0"]==State("S0"));
    }
    SECTION("Test Size")
    {
        REQUIRE(S.size()==5);
    }
    SECTION("Test Exist")
    {
        REQUIRE(S.exist("S0"));
        REQUIRE_FALSE(S.exist("S5"));
    }
    SECTION("Test Erase")
    {
        REQUIRE(S.erase("S4"));

        std::ostringstream out;
        for(auto it : S)
            out << *it << ",";

        REQUIRE(out.str() == "S0,S1,S2,S3,");
    }
}

TEST_CASE("Transitions check")
{
    Transitions II;
    States S;
    S.insert("S0");
    S.insert("S1");
    S.insert("S2");
    S.insert("S3");
    S.insert("S4");

    SECTION("Test Insertion of Transition")
    {
        REQUIRE(II.insert(S["S0"],"a",S["S1"]));
        REQUIRE(II.insert(S["S0"],"b",S["S2"]));
        REQUIRE(II.insert(S["S0"],"b",S["S1"]));
        REQUIRE(II.insert(S["S1"],"b",S["S1"]));
        REQUIRE(II.insert(S["S1"],"b",S["S2"]));
        REQUIRE(II.insert(S["S2"],"b",S["S3"]));
        REQUIRE_FALSE(II.insert(S["S0"],"b",S["S2"]));//Shouldn't be inserted
    }

    II.insert(S["S0"],"a",S["S1"]);
    II.insert(S["S0"],"b",S["S2"]);
    II.insert(S["S0"],"b",S["S1"]);
    II.insert(S["S1"],"b",S["S1"]);
    II.insert(S["S1"],"b",S["S2"]);
    II.insert(S["S2"],"b",S["S3"]);

    SECTION("Test Print And Iterators of Transitions") {
        std::ostringstream out;

        SECTION("Range Style for")
        {
            for (int i = 0; i < II.size(); i++)//prints them all
                out << II[i] << ",";

            REQUIRE(out.str() == "(S0, a, S1),(S0, b, S2),(S0, b, S1),(S1, b, S1),(S1, b, S2),(S2, b, S3),");
        }
        SECTION("For each Style for")
        {
            for (auto it : II)
                out << it << ",";

            REQUIRE(out.str() == "(S0, a, S1),(S0, b, S2),(S0, b, S1),(S1, b, S1),(S1, b, S2),(S2, b, S3),");
        }
    }
    SECTION("Test FinadAll Methods")
    {
        std::ostringstream out(std::ios_base::ate);

        SECTION("Test FinadAll_by_transition(Square Brackets)")
        {
            REQUIRE(*II[boost::make_tuple("S1", "b", "S2")]==Transition(S["S1"], "b", S["S2"]));
        }
        SECTION("Test FinadAll_by_source")
        {
            auto pairIt = II.findAll_by_source("S1");
            for(auto it = pairIt.first; it != pairIt.second; it++)
                out << *it << "\n";

            REQUIRE(out.str()=="(S1, b, S2)\n"
                               "(S1, b, S1)\n");
        }
        SECTION("Test FinadAll_by_destination")
        {
            auto pairIt2 = II.findAll_by_destination("S1");
            for(auto it = pairIt2.first; it != pairIt2.second; it++)
                out << *it << "\n";
            REQUIRE(out.str()=="(S1, b, S1)\n"
                               "(S0, b, S1)\n"
                               "(S0, a, S1)\n");
        }
        SECTION("Test FinadAll_by_source_word")
        {
            auto pairIt3 = II.findAll_by_source_word("S1","b");
            for(auto it = pairIt3.first; it != pairIt3.second; it++)
                out << *it << "\n";
            REQUIRE(out.str()=="(S1, b, S2)\n"
                    "(S1, b, S1)\n");
        }
        SECTION("Test FinadAll_by_word_destination")
        {
            auto pairIt4 = II.findAll_by_word_destination("b","S1");
            for(auto it = pairIt4.first; it != pairIt4.second; it++)
                out << *it << "\n";
            REQUIRE(out.str()=="(S1, b, S1)\n"
                               "(S0, b, S1)\n");
        }
    }
    SECTION("Test Exist")
    {
        REQUIRE_FALSE(II.exist("S2", "b", "S1"));
        REQUIRE(II.exist("S0", "b", "S1"));
    }
    SECTION("Test Erase")
    {
        std::ostringstream out;
        SECTION("Erase by_transition")
        {
            REQUIRE(II.erase("S1", "b", "S2"));
            for(auto it : II)
                out << it << "\n";
            REQUIRE(out.str()=="(S0, a, S1)\n"
                               "(S0, b, S2)\n"
                               "(S0, b, S1)\n"
                               "(S1, b, S1)\n"
                               "(S2, b, S3)\n");
            REQUIRE_FALSE(II.erase("S10", "b", "S2"));
        }
        SECTION("Erase by_source")
        {
            REQUIRE(II.erase_by_source("S1"));
            for(auto it : II)
                out << it << "\n";
            REQUIRE(out.str()=="(S0, a, S1)\n"
                               "(S0, b, S2)\n"
                               "(S0, b, S1)\n"
                               "(S2, b, S3)\n");
            REQUIRE_FALSE(II.erase_by_source("S10"));
        }
        SECTION("Erase by_destination")
        {
            REQUIRE(II.erase_by_destination("S2"));
            for(auto it : II)
                out << it << "\n";
            REQUIRE(out.str()=="(S0, a, S1)\n"
                               "(S0, b, S1)\n"
                               "(S1, b, S1)\n"
                               "(S2, b, S3)\n");
            REQUIRE_FALSE(II.erase_by_destination("S20"));
        }
        SECTION("Erase by_source_word")
        {
            II.erase_by_source_word("S0","a");
            for(auto it : II)
                out << it << "\n";
            REQUIRE(out.str()=="(S0, b, S2)\n"
                               "(S0, b, S1)\n"
                               "(S1, b, S1)\n"
                               "(S1, b, S2)\n"
                               "(S2, b, S3)\n");
        }
        SECTION("Erase by_word_destination")
        {
            II.erase_by_word_destination("b","S1");
            for(auto it : II)
                out << it << "\n";
            REQUIRE(out.str()=="(S0, a, S1)\n"
                               "(S0, b, S2)\n"
                               "(S1, b, S2)\n"
                               "(S2, b, S3)\n");
        }
    }

}

TEST_CASE("Automaton Check")
{
    std::ostringstream out;
    SECTION("Automaton Creation And Initialisation")
    {
        Automaton A("A1",Alphabet({'a','b','c'}));

        for (int j = 0; j < 5; ++j)
            A.insertNewState("S"+std::to_string(j));

        std::unordered_set<std::string>  finalStates({"S0","S1"});
        A.setFinal(finalStates);

        std::unordered_set<std::string>  initialStates({"S3","S4"});
        A.setInitial(initialStates);

        A.insertTransition("S0", "abc", "S1");
        A.insertTransition("S1", "ac", "S2");
        A.insertTransition("S2", "a", "S3");
        A.insertTransition("S3", "b", "S4");
        A.insertTransition("S0", " ", "S1");
        A.insertTransition("S1", "", "S2");

        out << A << "\n";

        REQUIRE(out.str()=="A1\t<\n"
                           "\tX = { c, a, b },\n"
                           "\tS = { S0, S1, S2, S3, S4 },\n"
                           "\tSinit = { S3, S4 },\n"
                           "\tII = { \n"
                           "\t\t(S0, abc, S1), \n"
                           "\t\t(S1, ac, S2), \n"
                           "\t\t(S2, a, S3), \n"
                           "\t\t(S3, b, S4), \n"
                           "\t\t(S0,  , S1), \n"
                           "\t\t(S1,  , S2) },\n"
                           "\tSfinal = { S0, S1 }\n"
                           "\t>\n");
    }
}








