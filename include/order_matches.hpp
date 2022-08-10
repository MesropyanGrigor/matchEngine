#include <deque>
#include "order_book.hpp"

#pragma once

class OrderSort{
    public:
        bool operator()(const Order& lhs, const Order& rhs) const;
};

class OrderMatches{

    private:
        typedef myPriorityQueue<Order, std::deque<Order>, OrderSort> Container;
        std::deque<Container> _data;

    // insert a new match
    public:
        void addMatch(const Order& agressorOrder, const Order& restingOrder, bool previousAddition=false);

        // Adding an order into the current match
        void addOrder();

        void showMatches() const;

};