
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <string>
#include <iostream>
#include "Word.h"
#include "Alphabet.h"

using namespace boost::multi_index;

struct animal
{
    std::string name;
    int legs;
};

typedef multi_index_container<
        animal,
        indexed_by<
                hashed_non_unique<
                        member<
                                animal, std::string, &animal::name
                        >
                >,
                hashed_non_unique<
                        member<
                                animal, int, &animal::legs
                        >
                >
        >
> animal_multi;

struct street_entry
{
    // quadrant coordinates
    int x;
    int y;

    std::string name;

    street_entry(int x,int y,const std::string& name):x(x),y(y),name(name){}
};

typedef multi_index_container<
        street_entry,
        indexed_by<
                hashed_non_unique<
                        composite_key<
                                street_entry,
                                member<street_entry, int, &street_entry::x>, member<street_entry, int, &street_entry::y>
                        >
                >,
                hashed_non_unique<member<street_entry, std::string, &street_entry::name> >
        >
> street_locator;

street_locator sl;

void streets_in_quadrant(int x,int y)
{
    std::pair<street_locator::iterator,street_locator::iterator> p=
            sl.equal_range(std::make_tuple(x,y));

    while(p.first!=p.second){
        std::cout<<p.first->name<<std::endl;
        ++p.first;
    }
}

#include "Transitions.h"
int main() {
    /*
    animal_multi animals;

    animals.insert({"cat", 4});
    animals.insert({"shark", 0});
    animals.insert({"spider", 8});
    animals.insert({"spider", 6});
    animals.insert({"spider", 4});

    std::cout << animals.count("cat") << '\n';

    auto &name_index = animals.get<0>();
    std::cout << name_index.count("spider") << '\n';
    auto pairIt = animals.equal_range("spider");
    for(auto it = pairIt.first; it != pairIt.second; it++)
        std::cout << it->name << " : " << it->legs << "\n";
    */
    Word w("abcd");
    std::cout << w.word() << " : " << w.mirror().word() << "\n";

    std::cout << "\n--Alphabet check--\n\n";

    Alphabet X({'a','b','c'});
    std::cout << X.contains('c') << "\n";

    std::cout << "\n--Insert 5, one fails--\n\n";

    State S0("S0"), S1("S1"), S2("S2"), S3("S3");

    Transitions II;
    std::cout << II.insert(&S0,"a",&S1) << "\n";
    std::cout << II.insert(&S0,"b",&S2) << "\n";
    std::cout << II.insert(&S0,"b",&S1) << "\n";
    std::cout << II.insert(&S1,"b",&S1) << "\n";
    std::cout << II.insert(&S1,"b",&S2) << "\n";
    std::cout << II.insert(&S2,"b",&S3) << "\n";
    std::cout << II.insert(&S0,"b",&S2) << "\n";//Shouldn't be inserted

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

    II.erase("S1", "b", "S2");
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase S1 by_initial--\n\n";

    std::cout << II.erase_by_initial("S1");
    for(auto it : II)//prints them all with different syntax
        std::cout << it << "\n";

    std::cout << "\n--Erase S2 by_final--\n\n";

    std::cout << II.erase_by_final("S2");
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