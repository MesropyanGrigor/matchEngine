 #include <stdexcept>
 #include <deque>
 #include "order_book.hpp"
 #include "order_matches.hpp"

//#pragma once;

void checkOrder(const Order& newOrder);

void matchEngine(OrderBook& myOrderBook, Order& newOrder, OrderMatches& marketMatches, bool pa=false);

