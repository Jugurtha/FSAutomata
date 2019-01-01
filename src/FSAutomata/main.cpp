
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include "../FSAutomataLib/Word.h"
#include "../FSAutomataLib/Alphabet.h"
#include "../FSAutomataLib/Transitions.h"
#include "../FSAutomataLib/States.h"
#include "../FSAutomataLib/Automaton.h"

#define EPSILON 'e'
#define PARTIALLY_GENERALISED 'p'
#define SIMPLE 's'
#define DETERMINISTIC 'd'
#define COMPLETE 'c'
#define COMPLEMENTARY 'b'
#define REDUCED 'r'

const std::string allowedOptions("epsdcbr");
std::deque<std::string> parseLine(std::string line, std::string separators);

int main(int argc, char* argv[]) {

    if(argc<3 || argc>4)
    {
        std::cout << "Parameters error.";
        exit(EXIT_FAILURE);
    }

    std::map<char,bool> options;
    for(auto letter : allowedOptions)
        options[letter] = false;

    if(argv[1][0]=='-')
    {
        std::string paramStr(argv[1]+1);
        for(auto letter : paramStr) {
            if (allowedOptions.find(letter) != std::string::npos)
                options[letter] = true;
            else
            {
                std::cout << "Unknown option.";
                exit(EXIT_FAILURE);
            }
        }
    } else if(argc!=3)
    {
        std::cout << "Parameters error.";
        exit(EXIT_FAILURE);
    } else
    {
        for(auto letter : allowedOptions)
            options[letter] = true;
    }

    std::ifstream fileIn(argv[argc==3?1:2]);
    std::ofstream fileOut(argv[argc==3?2:3]);

    if(!fileIn)
    {
        std::cout << "Couldn't open input file.";
        exit(EXIT_FAILURE);
    }
    if(!fileOut)
    {
        std::cout << "Couldn't open output file.";
        exit(EXIT_FAILURE);
    }

    std::string line;
    unsigned int actualAutomaton = 1;

    while(std::getline(fileIn, line) && line[0]!='\n' && !std::all_of(line.begin(),line.end(),isspace))
    {
        std::cout << "Processing automaton number " << actualAutomaton << "\n";
        std::string automatonId(parseLine(line,"< \n\t\r").front());

        if(!std::getline(fileIn, line))//retreve alphabet
        {
            std::cout << "Parssing error while retreving alphabet of automaton " << actualAutomaton << "\n";
            exit(EXIT_FAILURE);
        }
        auto alphabetList = parseLine(line," \n\t\r={},");
        alphabetList.pop_front();//Disgards X
        std::unordered_set<char> alphabet;
        for (auto letter : alphabetList) {
            alphabet.insert(letter[0]);
        }

        Automaton automaton(automatonId,Alphabet(alphabet));

        if(!std::getline(fileIn, line))//retreve states
        {
            std::cout << "Parssing error while retreving states of automaton " << actualAutomaton << "\n";
            exit(EXIT_FAILURE);
        }
        auto statesList = parseLine(line," \n\t\r={},");
        statesList.pop_front();//Disgards S
        automaton.insertNewStates(std::unordered_set<std::string>(statesList.begin(),statesList.end()));

        if(!std::getline(fileIn, line))//retreve initial states
        {
            std::cout << "Parssing error while retreving inital states of automaton " << actualAutomaton << "\n";
            exit(EXIT_FAILURE);
        }
        auto initialStatesList = parseLine(line," \n\t\r={},");
        initialStatesList.pop_front();//Disgards Sinit
        automaton.setInitial(std::unordered_set<std::string>(initialStatesList.begin(),initialStatesList.end()));

        std::string IIStr;
        while(std::getline(fileIn, line) && line.rfind('}')==std::string::npos)
            IIStr.append(line);

        auto transitionsList(parseLine(IIStr," \n\t\r={},()"));
        transitionsList.pop_front();//Disgards II

        for (int i = 0; i < transitionsList.size(); i+=3)
            automaton.insertTransition(transitionsList[i],transitionsList[i+1],transitionsList[i+2]);

        if(!std::getline(fileIn, line))//retreve final states
        {
            std::cout << "Parssing error while retreving final states of automaton " << actualAutomaton << "\n";
            exit(EXIT_FAILURE);
        }
        auto finalStatesList = parseLine(line," \n\t\r={},");
        finalStatesList.pop_front();//Disgards Sfinal
        automaton.setFinal(std::unordered_set<std::string>(finalStatesList.begin(),finalStatesList.end()));

        //Print the Automaton in output file
        fileOut << automaton << "\n----------";

        if(options[EPSILON])
            fileOut << "\n"<< "REMOVE EPSILON TRANSITIONS" << "\n" << automaton.removeEpsilonTransitions() << "\n----------";

        if(options[PARTIALLY_GENERALISED])
            fileOut << "\n" << "PARTIALLY GENERALISED" << "\n" << automaton.toPartiallyGeneralized() << "\n----------";

        if(options[SIMPLE])
            fileOut << "\n" << "SIMPLE" << "\n" << automaton.toSimple() << "\n----------";

        if(options[COMPLETE])
            fileOut << "\n" << "COMPLETE" << "\n" << automaton.toComplete() << "\n----------";

        if(options[DETERMINISTIC])
            fileOut << "\n" << "DETERMINISTIC" << "\n" << automaton.toDeterministic() << "\n----------";

        if(options[COMPLEMENTARY])
            fileOut << "\n" << "COMPLEMENTARY" <<"\n" << automaton.toComplementary() << "\n----------";

        //if(options[REDUCED])//Not implemented yet..
          //  fileOut << "\n" << "REDUCED" << "\n" << automaton.toReduced() << "\n----------";

        fileOut << "----------------------------\n";


        if(!std::getline(fileIn, line) && line.find('>')==std::string::npos)//retreve >
        {
            std::cout << "Error while parsing automaton " << actualAutomaton << " .";
            exit(EXIT_FAILURE);
        }
        actualAutomaton++;
    }

    std::cout << "Finished processing file.";

    return EXIT_SUCCESS;
}


std::deque<std::string> parseLine(std::string line, std::string separators)
{
    boost::tokenizer<boost::char_separator<char> > tok(line,boost::char_separator<char>(separators.c_str()));
    return std::deque<std::string>(tok.begin(),tok.end());
}


