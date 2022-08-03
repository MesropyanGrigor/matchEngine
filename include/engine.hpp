 #include <stdexcept>
 #include <deque>
 #include "order_book.hpp"

//#pragma once;

void checkOrder(const Order& newOrder);

void matchEngine(OrderBook& myOrderBook, Order& newOrder, std::deque<std::deque<Order>>& marketMatches);

