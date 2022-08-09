#include <deque>
#include "order_book.hpp"

#pragma once

class OrderMatches{

    private:
    std::deque<std::deque<Order>> _data;

    // insert a new match
    public:
        void addMatch(const Order& agressorOrder, const Order& restingOrder, bool previousAddition=false);

        // Adding an order into the current match
        void addOrder();

        void showMatches() const;

};