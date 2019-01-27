
#include <boost/tokenizer.hpp>
#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "../FSAutomataLib/Automaton.h"

#define EPSILON_S "e"
#define EPSILON "remove-epsilon"
#define PARTIALLY_GENERALISED "partially-generalised"
#define PARTIALLY_GENERALISED_S "p"
#define SIMPLE "simple"
#define SIMPLE_S "s"
#define DETERMINISTIC "deterministic"
#define DETERMINISTIC_S "d"
#define COMPLETE "complete"
#define COMPLETE_S "c"
#define COMPLEMENTARY "complementary"
#define COMPLEMENTARY_S "b"
#define REDUCED "reduced"
#define REDUCED_S "r"
#define RECOGNIZE "recognize"
#define RECOGNIZE_S "i"
#define INPUTFILE "inputfile"
#define OUTPUTFILE "outputfile"


const std::string allowedOptions("epsdcbr");
std::deque<std::string> parseLine(std::string line, std::string separators);


int main(int argc, char* argv[]) {
 //*
    namespace po = boost::program_options;
    po::options_description desc("FSAutomaton's Allowed Options");
    desc.add_options()
            ("help,h","Displas a description of the available options.")
            (EPSILON  ","  EPSILON_S, "Remove epsilon transitions.")
            (PARTIALLY_GENERALISED  ","  PARTIALLY_GENERALISED_S, "Make the automaton partially generalised.")
            (SIMPLE  ","  SIMPLE_S,"Make the automaton simple")
            (DETERMINISTIC "," DETERMINISTIC_S,"Make the automaton deterministic")
            (COMPLETE "," COMPLETE_S,"Make the automaton complete")
            (COMPLEMENTARY "," COMPLEMENTARY_S,"Make the automaton complementary")
            (REDUCED "," REDUCED_S,"Make the automaton reduced")
            (RECOGNIZE "," RECOGNIZE_S, po::value<std::string>(),"Check whether the automata in the file recognize the set of words")
            (INPUTFILE, po::value<std::string>()->required(),"Input file path containing automata discriptions")
            (OUTPUTFILE, po::value<std::string>()->required(),"Outout file path that will containin the results");
    po::positional_options_description positionalOptionsDescription;
    positionalOptionsDescription.add("inputfile",1);
    positionalOptionsDescription.add("outputfile",1);
    po::variables_map optionsMap;
    try {
        po::store(po::command_line_parser(argc,argv).options(desc).positional(positionalOptionsDescription).run(),optionsMap);
        po::notify(optionsMap);

        if(optionsMap.count("help"))
        {
            std::cout << desc << '\n';
        }else
        {
            std::ifstream fileIn(optionsMap[INPUTFILE].as<std::string>());
            std::ofstream fileOut(optionsMap[OUTPUTFILE].as<std::string>());

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

            std::map<std::string,std::deque<std::string>> wordsMap;
            std::ifstream wordsFileIn;
            std::ofstream wordsFileOut;
            if(optionsMap.count(RECOGNIZE))
            {
                wordsFileIn.open(optionsMap[RECOGNIZE].as<std::string>());
                wordsFileOut.open(optionsMap[RECOGNIZE].as<std::string>()+".result");
                if(!wordsFileIn)
                {
                    std::cout << "Couldn't open words input file.";
                    exit(EXIT_FAILURE);
                }
                if(!wordsFileOut)
                {
                    std::cout << "Couldn't open words output file.";
                    exit(EXIT_FAILURE);
                }

                std::string line;
                while(std::getline(wordsFileIn,line))
                {
                    auto list = parseLine(line, ":,\t");
                    auto it = list.begin();
                    for(it++;it!=list.end();it++)
                        wordsMap[*(list.begin())].push_back(*it);
                }

            }



            std::string line;
            unsigned int actualAutomaton = 1;

            bool allSet = false;
            if(!optionsMap.count(EPSILON) && !optionsMap.count(PARTIALLY_GENERALISED) && !optionsMap.count(SIMPLE) &&
                    !optionsMap.count(COMPLETE) &&  !optionsMap.count(COMPLEMENTARY) &&  !optionsMap.count(DETERMINISTIC))// &&  !optionsMap.count(REDUCED))
                allSet = true;

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

                std::getline(fileIn, line);//Skip II =  {
                while(std::getline(fileIn, line))
                {
                    auto transition(parseLine(line," \n\t\r={},()"));
                    if(transition.size()<3)
                        automaton.insertTransition(transition[0]," ",transition[1]);
                    else
                        automaton.insertTransition(transition[0],transition[1],transition[2]);

                    if(line.rfind('}')!=std::string::npos)
                        break;
                }

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

                if(allSet || optionsMap.count(EPSILON))
                    fileOut << "\n"<< "REMOVE EPSILON TRANSITIONS" << "\n" << automaton.removeEpsilonTransitions() << "\n----------";

                if(allSet || optionsMap.count(PARTIALLY_GENERALISED))
                    fileOut << "\n" << "PARTIALLY GENERALISED" << "\n" << automaton.toPartiallyGeneralized() << "\n----------";

                if(allSet || optionsMap.count(SIMPLE))
                    fileOut << "\n" << "SIMPLE" << "\n" << automaton.toSimple() << "\n----------";

                if(allSet || optionsMap.count(COMPLETE))
                    fileOut << "\n" << "COMPLETE" << "\n" << automaton.toComplete() << "\n----------";

                if(allSet || optionsMap.count(DETERMINISTIC))
                    fileOut << "\n" << "DETERMINISTIC" << "\n" << automaton.toDeterministic() << "\n----------";

                if(allSet || optionsMap.count(COMPLEMENTARY))
                    fileOut << "\n" << "COMPLEMENTARY" <<"\n" << automaton.toComplementary() << "\n----------";

                if(allSet || optionsMap.count(REDUCED))//Not implemented yet..
                  fileOut << "\n" << "REDUCED" << "\n" << automaton.toReduced() << "\n----------";

                if(optionsMap.count(RECOGNIZE))
                {
                    if(wordsMap.count(automatonId))
                    {
                        wordsFileOut << "\n" << automatonId << " : \n";
                        for(auto word : wordsMap[automatonId])
                            wordsFileOut << "\t" << word << " -> "  << ((automaton.recognizes(word))?("Recognized."):("Not Recognized.")) << "\n";

                        wordsFileOut << "\n----------------------------\n";
                    }
                }

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

    }catch(const po::error exception)
    {
        std::cout << exception.what() << '\n' ;
    }
    return EXIT_SUCCESS;
}


std::deque<std::string> parseLine(std::string line, std::string separators)
{
    boost::tokenizer<boost::char_separator<char> > tok(line,boost::char_separator<char>(separators.c_str()));
    return std::deque<std::string>(tok.begin(),tok.end());
}


