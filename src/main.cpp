#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <istream>
#include <fstream>
#include "engine.hpp"
#include "order_book.hpp"

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

void printOrders(std::deque<std::deque<Order>>& outMarketMatches)
{
    auto _print = [](auto& it){it.printOutputFormat(); std::cout<<"     ";};
    std::cout<<std::endl<<"Outputing the final results"<<std::endl;
    for (auto matches : outMarketMatches)
    {
        std::for_each(matches.begin(), matches.end(), _print);
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
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
    std::deque<std::deque<Order>> outMarketMatches;
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
            //std::cout<<cmdInput<<std::endl;
            printOrders(outMarketMatches);
        }
        else
        {
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