#include "order_matches.hpp"


bool OrderSort::operator()(const Order& lhs, const Order& rhs) const
{

    std::string str1 = lhs.getTrader() + lhs.getSide() + std::to_string(lhs.getPrice());
    std::string str2 = rhs.getTrader() + rhs.getSide() + std::to_string(rhs.getPrice());
    return str1 > str2;
}

void OrderMatches::addMatch(const Order& agressorOrder, const Order& restingOrder, bool previousAddition)
{
    if (!previousAddition)
    {
        OrderMatches::Container firstMatches;
        firstMatches.push(agressorOrder);
        firstMatches.push(restingOrder);
        _data.push_back(std::move(firstMatches));
        return;
    }   
    OrderMatches::Container& lastElement = _data.back();
    std::deque<Order>& lastMatch = lastElement.getContainer();

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
    }
    if (!isAddedResting) lastElement.push(restingOrder);
    if (!isAddedAgressor) lastElement.push(agressorOrder);
}


void printOrders(const auto& outMarketMatches)
{
    auto _print = [](auto& it){it.printOutputFormat(); std::cout<<"     ";};
    std::cout<<std::endl<<"Outputing the final results"<<std::endl;
    for (auto matches : outMarketMatches)
    {
        std::for_each(matches.getContainer().begin(), matches.getContainer().end(), _print);
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void OrderMatches::showMatches() const
{
    printOrders(_data);
}