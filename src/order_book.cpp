#include "order_book.hpp"

 void Order::print() const
 {
    std::cout<<"Order("<<getTrader()<<", "<<getSide()<<", "<<getQuantity()<<", "<<getPrice()<<")";
 }

 void Order::printOutputFormat() const
 {
    char sign = getSide() == 'B'? '+' :  '-';
    
    std::cout<<getTrader()<<sign<<getQuantity()<<'@'<<getPrice();
 }

bool Order::isBuy() const
{
    return getSide() == 'B';
}

bool Order::operator==(const Order& rhs) const
{
    bool status = false;
    return this->price == rhs.price;
}

std::string Order::getTrader() const
{
    return trader;
}

char Order::getSide() const
{
    return side;
}

std::uint32_t Order::getQuantity() const
{
    return quantity;
}

std::uint32_t Order::getPrice() const
{
    return price;
}

std::deque<Order>& OrderBook::getBuyersOrders()
{
    return buyersOrders;
}

std::deque<Order>& OrderBook::getSellersOrders()
{
    return sellersOrders;
}

void OrderBook::addOrder(const Order& newOrder)
{
   // std::cout<<"Adding Order: ";
   // newOrder.print();
    //std::cout<<std::endl;

    if (newOrder.getSide() == 'S')
    {
        sellersOrders.push_back(newOrder);
    }
    else if(newOrder.getSide() == 'B')
    {
        buyersOrders.push_back(newOrder);
    }
}