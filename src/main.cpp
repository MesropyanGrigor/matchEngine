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


int main()
{
    //std::ifstream inputFile;
    //inputFile.open("../input.txt", std::ios::in);

    OrderBook myOrderBook;
    std::deque<std::deque<Order>> outMarketMatches;
    std::string cmdInput;
    std::vector<std::string> words;
    std::vector<Order> inputData;
    std::vector<std::string> attributes;

    while (std::getline(std::cin, cmdInput))
    //while(std::getline(inputFile, cmdInput))
    {
        if (cmdInput == "exit")
        {
            // Show the market state and return
            std::cout<<"exited"<<std::endl;
            return 0;
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
    }
    return 0;
}