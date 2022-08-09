#include "order_book.hpp"

// Order class implementation

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

bool Order::isMatch(const Order& rhs)
{
    if (isBuy())
    {
        return this->price >= rhs.getPrice();
    }
    else
    {
        return this->price <= rhs.getPrice();
    }

}

void Order::setPrice(std::uint32_t value)
{
    price = value;
}

void Order::setQuantity(std::uint32_t value)
{
    quantity = value;
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

OrderBook::buyersType& OrderBook::getBuyersOrders()
{
    return buyersOrders;
}

OrderBook::sellersType& OrderBook::getSellersOrders()
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
        sellersOrders.push(newOrder);
    }
    else if(newOrder.getSide() == 'B')
    {
        buyersOrders.push(newOrder);
    }
}

// Implementation of comparision functor classes

bool orderLess::operator()(const Order& lhs, const Order& rhs) const
{
    return lhs.getPrice() > rhs.getPrice();
}

bool orderGreater::operator()(const Order& lhs, const Order& rhs) const
{
    return lhs.getPrice() < rhs.getPrice();
}