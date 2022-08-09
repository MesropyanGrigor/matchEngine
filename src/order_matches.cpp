#include "order_matches.hpp"

void OrderMatches::addMatch(const Order& agressorOrder, const Order& restingOrder, bool previousAddition)
{
    if (!previousAddition)
    {
        _data.push_back(std::deque<Order>{agressorOrder, restingOrder});
        return;
    }    
    std::deque<Order>& lastMatch = _data.back();

    bool isAddedAgressor = false;
    bool isAddedResting = false;
    for (std::size_t i = 0; i < lastMatch.size(); i++)
    {
        if(agressorOrder.getTrader() == lastMatch[i].getTrader() &&
            agressorOrder.getPrice() == lastMatch[i].getPrice())
        {
            lastMatch[i].setQuantity(lastMatch[i].getQuantity() + agressorOrder.getQuantity());   
            isAddedAgressor = true;
        }

        if(restingOrder.getTrader() == lastMatch[i].getTrader() &&
            restingOrder.getPrice() == lastMatch[i].getPrice())
        {
            lastMatch[i].setQuantity(lastMatch[i].getQuantity() + restingOrder.getQuantity()); 
            isAddedResting = true;
        }

        // Will be usefull to define insertion order 
        if (!isAddedAgressor) lastMatch.push_back(agressorOrder);
        if (!isAddedResting) lastMatch.push_back(restingOrder);
    }
}

void printOrders( const std::deque<std::deque<Order>>& outMarketMatches)
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

void OrderMatches::showMatches() const
{
    printOrders(_data);
}