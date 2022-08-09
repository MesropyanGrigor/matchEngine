#include <string>
#include <queue>
#include <stdio.h>
#include <iostream>
#include <queue>
#include <deque>

#pragma once

class Order {
    private:
        std::string trader;
        char side;
        std::uint32_t quantity;
        std::uint32_t price;

    public:
        Order(std::string _trader, char _side, 
            std::uint32_t _quantity, std::uint32_t _price): trader(_trader), side(_side), quantity(_quantity), price(_price)
        {}
        Order(std::vector<std::string> inputData): trader(inputData[0]),
                                                side(*inputData[1].c_str()),
                                                quantity(atoi(inputData[2].c_str())),
                                                price(atoi(inputData[3].c_str()))
        {}

        bool isBuy() const;

        bool isMatch(const Order& rhs);

        void setPrice(std::uint32_t value);
        void setQuantity(std::uint32_t value);

        bool operator==(const Order& rhs) const;
        
        inline void operator-(const std::uint32_t value)
        {
            //std::cout<<"Removing"<<quantity<<"-"<<value<<std::endl;
            quantity = quantity - value;
        }

        std::string getTrader() const;
        char getSide() const;
        std::uint32_t getQuantity() const;
        std::uint32_t getPrice() const;


        void print() const;
        void printOutputFormat() const;
};

class orderLess
{
    public:
    bool operator()(const Order& lhs, const Order& rhs) const;
};

class orderGreater
{
    public:
    bool operator()(const Order& lhs, const Order& rhs) const;
};

template<class T, class Container, class Compare>
class myPriorityQueue: public std::priority_queue<T, Container, Compare>
{
    public:
        inline Container& getContainer()
        {
            return this->c;
        }
};

class OrderBook
{
    private:
        typedef myPriorityQueue<Order, std::deque<Order>, orderLess> sellersType;
        typedef myPriorityQueue<Order, std::deque<Order>, orderGreater> buyersType;


    private:
        sellersType sellersOrders;
        buyersType buyersOrders;

    public:
        OrderBook() = default;

        sellersType& getSellersOrders();

        buyersType& getBuyersOrders();

        void addOrder(const Order& newOrder);
};