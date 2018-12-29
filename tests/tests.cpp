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
        std::streambuf* coutBuf = std::cout.rdbuf();//Back up the buffer
        std::cout.rdbuf(out.rdbuf()); //redirect cout to out

        SECTION("For each Style for")
        {
            for(auto it : S)
                std::cout << *it << ",";

            REQUIRE( out.str() == "S0,S1,S2,S3,S4,");
        }
        SECTION("Range Style for")
        {
            for(int i=0;i < S.size();i++)
                std::cout << *S[i] << ",";

            REQUIRE( out.str() == "S0,S1,S2,S3,S4,");
        }
        std::cout.rdbuf(coutBuf);//Restore buffer
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
        bool success = S.erase("S4");
        std::ostringstream out;
        std::streambuf* coutBuf = std::cout.rdbuf();//Back up the buffer
        std::cout.rdbuf(out.rdbuf()); //redirect cout to out

        for(auto it : S)
            std::cout << *it << ",";

        REQUIRE( out.str() == "S0,S1,S2,S3,");

        std::cout.rdbuf(coutBuf);//Restore buffer
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
        std::streambuf *coutBuf = std::cout.rdbuf();//Back up the buffer
        std::cout.rdbuf(out.rdbuf()); //redirect cout to out

        SECTION("Range Style for")
        {
            for (int i = 0; i < II.size(); i++)//prints them all
                std::cout << II[i] << ",";

            REQUIRE(out.str() == "(S0, a, S1),(S0, b, S2),(S0, b, S1),(S1, b, S1),(S1, b, S2),(S2, b, S3),");
        }
        SECTION("For each Style for")
        {
            for (auto it : II)//prints them all with different syntax
                std::cout << it << ",";

            REQUIRE(out.str() == "(S0, a, S1),(S0, b, S2),(S0, b, S1),(S1, b, S1),(S1, b, S2),(S2, b, S3),");
        }
        std::cout.rdbuf(coutBuf);//Restore buffer
    }
    SECTION("Test FinadAll Methods")
    {
        REQUIRE(true);
    }
}








