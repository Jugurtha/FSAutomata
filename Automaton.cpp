//
// Created by LENOVO on 05/12/2018.
//

#include "Automaton.h"

Automaton::Automaton(const std::string &id, Alphabet X): id_(id), X(X) {}

Automaton::Automaton(const Automaton &automaton):Automaton(automaton.id(),automaton.X, automaton.S, automaton.Sinit, automaton.II, automaton.Sfinal)
{
}

Automaton::Automaton(const std::string &id, const Alphabet &X, const States &S,
                     const std::unordered_set<std::string> &Sinit, const Transitions &II,
                     const std::unordered_set<std::string> &Sfinal) : id_(id), X(X)
{
    for(auto s : S)
    {
        this->S.insert(s->id());
        if(Sinit.count(s->id())==1)
            this->Sinit.insert(s->id());
        if(Sfinal.count(s->id())==1)
            this->Sfinal.insert(s->id());
    }
    for(auto t : II)
        this->II.insert(S[t.source()],t.word(),S[t.destination()]);
}

bool Automaton::insertTransition(const std::string &source, const std::string &word, const std::string &destination) {
    if( !S.exist(source) || !S.exist(destination) )
        return false;
    return II.insert(S[source], word, S[destination]);
}

bool Automaton::insertNewState(const std::string &state) {
    if(state.find('_')!=state.npos || state.find("Sink")!=state.npos)
        return false;
    return S.insert(state);
}
bool Automaton::insertSinkState()
{
    return S.insert("Sink");
}

bool Automaton::insertNewStates(const std::unordered_set<std::string> &states)
{
    bool ret = true;
    for(auto state : states) {
        if (state.find('_') != state.npos || state.find("Sink")!=state.npos)
            ret = false;
        else
            ret &= S.insert(state);
    }
    return ret;
}

bool Automaton::setInitial(const std::string &state) {
    if(!S.exist(state))
        return false;

    auto p = Sinit.insert(state);
    return p.second;
}

bool Automaton::setFinal(const std::string &state) {
    if(!S.exist(state))
        return false;

    auto p = Sfinal.insert(state);
    return p.second;
}

const Alphabet &Automaton::getX() const {
    return X;
}

const std::unordered_set<std::string> Automaton::getStates(){
    std::unordered_set<std::string> set;
    for(auto s : S.getStates())
        set.insert(s);
    return set;
}

const std::unordered_set<std::string> &Automaton::getSinit() const {
    return Sinit;
}

const Transitions &Automaton::getII() const {
    return II;
}

const std::unordered_set<std::string> &Automaton::getSfinal() const {
    return Sfinal;
}

bool Automaton::setFinal(std::unordered_set<std::string> states) {
    for(auto s : states)
        if(!S.exist(s))
            return false;
    Sfinal.insert(states.begin(),states.end());
    return true;
}

bool Automaton::setInitial(std::unordered_set<std::string> states) {
    for(auto s : states)
        if(!S.exist(s))
            return false;
    Sinit.insert(states.begin(),states.end());
    return true;
}

bool Automaton::isInitial(const std::string state)const
{
    return Sinit.count(state)==1;
}
bool Automaton::isFinal(const std::string state)const
{
    return Sfinal.count(state)==1;;
}

std::ostream& operator<<(std::ostream& out, const Automaton &automaton)
{
    out << automaton.id() << "\t<" << "\n";
    out << "\tX = " << automaton.X << ",\n";
    out << "\tS = "  << automaton.S << ",\n";
    out << "\tSinit = "  << automaton.Sinit << ",\n";
    out << "\tII = "  << automaton.II << ",\n";
    out << "\tSfinal = "  << automaton.Sfinal << "\n\t>";
    return out;
}

const Automaton  Automaton::toSimple() const{
    return (this->toPartiallyGeneralized()).removeEpsilonTransitions();
}

const Automaton  Automaton::toDeterministic() const{
    //toSimple();
    //...
}

const Automaton  Automaton::toComplementary() const{

}

const Automaton  Automaton::toComplete() const{
    //At least simple
	//sink state
	Automaton temp(this->toSimple());

	temp.insertSinkState();

	auto states = temp.S.getStates();

	for(auto s : states)
    {
        for(auto c : temp.getX())
        {
            std::string word({c});
            auto pIt = temp.II.findAll_by_source_word(s,word);
            if(pIt.first==pIt.second)//if both are equal, then they are equal to end, which means no noed has been found.
                temp.insertTransition(s,word,"Sink");//inserts transition (s,c,sink)
        }
    }

	return temp;
}

const Automaton Automaton::toPartiallyGeneralized() const//-> |word|<=1
{
    Automaton temp(*this);
    static int index = 0;
    for(auto t : II)
    {
        if(t.word().size()>1)
        {
            Transition transition(t);//We make a copy...
            if(temp.II.erase(t)!=1)//We erase the transition with |word|>1
            {
                std::cout << "toPartiallyGeneralized failed on erasing transition : "+ t.transition() +".\n";
                return  temp;
            }
            State *ptrPreviousState = nullptr, *ptrNewState = nullptr;
            int i = 0;
            size_t size =  transition.word().size();
            auto source = transition.source();
            for(i=0;i<size-1;i++)
            {
                std::string newState(transition.source()+"_"+std::to_string(index+1));
                if(!temp.S.insert(newState))
                {
                    std::cout << "toPartiallyGeneralized failed on insertion of new state : " + newState + ".\n";
                    return  temp;
                } else
                    index++;
                ptrPreviousState = temp.S[source];
                ptrNewState =  temp.S[newState];
                if(ptrNewState == nullptr || ptrPreviousState == nullptr)
                {
                    std::cout << "toPartiallyGeneralized failed on retrieval of states : " + source + ", " + newState + ".\n";
                    return  temp;
                }
                temp.II.insert(ptrPreviousState,transition.getWord()[i],ptrNewState);
                source = newState;
            }
            temp.II.insert(ptrNewState,transition.getWord()[i],transition.destinationPtr());
        }
    }
    return temp;
}

const Automaton  Automaton::removeEpsilonTransitions() const{
    Automaton temp(id_,X);

    if(!temp.insertNewStates(Sinit))// temp.S = Sinit
    {
        std::cout << "removeEpsilonTransitions failed on states insertion" << "\n";
        return temp;
    }

    temp.setInitial(Sinit);

    for(auto s : Sinit) {//temp.Sfinal = Sinit inter Sfinal
        if (Sfinal.count(s) == 1)
            if(!temp.setFinal(s))
            {
                std::cout << "removeEpsilonTransitions failed on states insertion" << "\n";
                return temp;
            }
    }

    std::stack<Transition> bucket;
    for(auto s : Sinit)//Most of the time, there will only be one initial state.
    {
        auto pIt = II.findAll_by_source(s);//We retrieve the transitions that start from an initial state.
        for(auto it = pIt.first; it != pIt.second; it++ )
            bucket.push(*it);
    }

    Transitions IIepsilon;

    //IIepsilon = {}
    //temp.II = {}
    //bucket = {(q1,a,q2) | q1 in Sinit}
/*
    std::cout << "------------------------\n";
    std::cout << "bucket.size() = " << bucket.size() << " : bucket = \n" << bucket << "\n";
    std::cout << "\nIIepsilon = \n" << IIepsilon << "\n" << temp << "\n";
    std::cout << "----------------------\n";
//*/
    while (!bucket.empty())
    {
        auto transition = bucket.top(); bucket.pop();//top; pop == pick

        if(!transition.getWord().isEpsilon()) //w!=epsilon
        {
            temp.S.insert(transition.destination());

            temp.insertTransition(transition.source(),transition.word(),transition.destination());

            if(isFinal(transition.destination()))
                temp.setFinal(transition.destination());

            auto pIt = II.findAll_by_source(transition.destination());
            for(auto it = pIt.first;it != pIt.second;it++)
            {
                if(it->getWord().isEpsilon()) {
                    if (!temp.II.exist(transition.source(), transition.word(), it->destination()))
                        bucket.push(Transition(transition.sourcePtr(), transition.word(), it->destinationPtr()));
                }
                else {//There was a "dangling else" problem here. I put the else here without the {}, so there was anbiguity(https://en.wikipedia.org/wiki/Dangling_else). which is a strait forwad exemple of what we've seen in class(what lead to Chomsky and Greibach normal forms).
                        if (!temp.II.exist(transition.destination(), it->word(), it->destination()))
                            bucket.push(Transition(transition.destinationPtr(), it->word(), it->destinationPtr()));
                    }
            }
        }
        else //w==epsilon
        {
            IIepsilon.insert(transition.sourcePtr(),transition.word(),transition.destinationPtr());

            if(isFinal(transition.destination()))
                temp.setFinal(transition.source());//State already inserted with the first block of if close or with initial states

            auto pIt = II.findAll_by_source(transition.destination());
            for(auto it = pIt.first;it != pIt.second;it++)
            {
                if(!temp.II.exist(transition.source(),it->word(),it->destination()) && !IIepsilon.exist(transition.source(),it->word(),it->destination()))
                    bucket.push(Transition(transition.sourcePtr(),it->word(),it->destinationPtr()));
            }
        }
/*
        std::cout << "--------------\n";
        std::cout << "bucket.size() = " << bucket.size() << " : bucket = \n" << bucket << "\n";
        std::cout << "\nIIepsilon = \n" << IIepsilon << "\n" << temp << "\n";
//*/
    }
    return temp;
}


std::ostream& operator<<(std::ostream& out, const std::unordered_set<std::string> &str)
{
    out << "{ " ;
    const size_t size = str.size();
    auto it = str.cbegin();
    if(size>0)
    {
        out << *it;
        for(it++; it!=str.cend(); it++)
            out << ", " << *it;
    }
    out << " }";
    return out;
}

std::ostream& operator<<(std::ostream& out, std::stack<Transition> stack)
{

    const size_t size = stack.size();
    if(size>0)
    {
        out << "{ " ;
        if(size==1)
            out << stack.top() << " }";
        else
        {
            out << "\n\t" << stack.top();stack.pop();
            while(!stack.empty())
            {
                out << ", \n\t" << stack.top();
                stack.pop();
            }
            out << "\n }";
        }
    }
    return out;
}





