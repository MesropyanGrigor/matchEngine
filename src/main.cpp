#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <istream>
#include <fstream>
#include "engine.hpp"
#include "order_book.hpp"
#include "order_matches.hpp"
#include <regex>

void fillVector(const std::string& line, std::vector<std::string>& attributes)
{
    std::string word = "";

    std::size_t length = line.length();


    for(std::size_t i=0; i < length; i++)
    {
        if (line[i] == ' ' or i == (length-1))
        {
            if (i == (length-1))
                attributes.push_back(word + line[i]);
            else
                attributes.push_back(word);
            word.clear();
        }
        else{
            word += line[i];
        }
    }

}

bool isValidInputLine(std::string& line)
{
    // Checking the input order string validity
    // This is a heavy operation and can be improved using a simple iterration
    return std::regex_match(line, std::regex("T[0-9]+ *(B|S) *[0-9]+ *[0-9]+[ \n]*"));
}

void printHelpMessage()
{
    std::cout<<"There are the following commands"<<std::endl;
    std::cout<<"\tYou can provide inputs of orders directly."<<std::endl;
    std::cout<<"\tOther keywords which program understands are"<<std::endl;
    std::cout<<"\t\tshow - will show the result"<<std::endl;
    std::cout<<"\t\texit - will finish the program"<<std::endl;
    std::cout<<"\t\tfile - will read inputs from ../inputs.txt file"<<std::endl;
}

template <typename T>
void startProcessing(std::string& cmdInput, T& stream)
{
    OrderBook myOrderBook;
    OrderMatches outMarketMatches;
    std::vector<std::string> attributes;

    do {
        if (cmdInput == "exit")
        {
            // Show the market state and return
            std::cout<<"exited"<<std::endl;
            return ;
        }
        else if (cmdInput == "show")
        {
            outMarketMatches.showMatches();
        }
        else
        {
            if (!isValidInputLine(cmdInput)) continue;
            fillVector(cmdInput, attributes);
            Order newOrder(attributes);
            matchEngine(myOrderBook, newOrder, outMarketMatches);
            attributes.clear();
        }
    } while (std::getline(stream, cmdInput));
}

int main()
{
    printHelpMessage();

    std::string cmdInput;

    std::getline(std::cin, cmdInput);

    if(cmdInput == "file")
    {
        std::ifstream inputFile;
        inputFile.open("../input.txt", std::ios::in);
        std::getline(inputFile, cmdInput);
        startProcessing<std::ifstream>(cmdInput, inputFile);
    }
    else{
        startProcessing<std::istream>(cmdInput, std::cin);
    }

    return 0;
}