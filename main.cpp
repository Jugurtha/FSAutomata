
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <string>
#include <iostream>
#include "Word.h"

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

    State S0("S0"), S1("S1"), S2("S2");

    Transitions II;
    II.container.get<Transitions::by_transition>().insert(Transition(&S0,"a",&S1));
    II.container.get<Transitions::by_transition>().insert(Transition(&S0,"b",&S2));
    II.container.get<Transitions::by_transition>().insert(Transition(&S0,"b",&S1));
    II.container.get<Transitions::by_transition>().insert(Transition(&S1,"b",&S1));
    II.container.get<Transitions::by_transition>().insert(Transition(&S1,"b",&S2));

    for(int i = 0;i< II.container.size();i++)
        std::cout << II.container[i] << "\n";

    std::cout << "\n" << *II.container.get<Transitions::by_transition>().find(TransitionKey("S1","b","S1"),TransitionHasher(),TransitionKeyEqual() ) << "\n\n" ;

    auto pairIt = II.container.get<Transitions::by_initial>().equal_range("S1");
    for(auto it = pairIt.first; it != pairIt.second; it++)
        std::cout << *it << "\n";
    std::cout << "\n\n";
    auto pairIt2 = II.container.get<Transitions::by_final>().equal_range("S1");
    for(auto it = pairIt2.first; it != pairIt2.second; it++)
        std::cout << *it << "\n";

    return 0;
}