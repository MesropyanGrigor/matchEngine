 #include <stdexcept>
 #include <deque>
 #include "order_book.hpp"
 #include "engine.hpp"
 #include "order_matches.hpp"

void checkOrder(const Order& newOrder)
{
    if (newOrder.getPrice() == 0 || 
        newOrder.getQuantity() == 0 ||
        (newOrder.getSide() != 'B' && newOrder.getSide() != 'S'))
    {
        newOrder.print();
        std::cout<<std::endl;
        throw std::logic_error("Order is not valid");
    }
}

void output(auto & aa)
{
    auto _outputing = [](auto& it){it.print(); std::cout<<"----";};
    std::for_each(aa.begin(), aa.end(), _outputing);
    std::cout<<std::endl;
}

 void matchEngine(OrderBook& myOrderBook, Order& newOrder, OrderMatches& marketMatches, bool pa)
 {
    std::cout<<"Processing Order: "; newOrder.print(); std::cout<<std::endl;
    checkOrder(newOrder); 

    auto& orders = newOrder.getSide() == 'B' ? myOrderBook.getSellersOrders().getContainer() : myOrderBook.getBuyersOrders().getContainer();
    output(orders);

    for (std::size_t i=0; i < orders.size(); i++)
    {
        Order& tmpOrder = orders[i];

        if(newOrder.isMatch(tmpOrder))
        {
            if (newOrder.getQuantity() == tmpOrder.getQuantity())
            {
                // updating newOrder price by resting order value

                newOrder.setPrice(tmpOrder.getPrice());

                marketMatches.addMatch(newOrder, orders[i], pa);

                orders.erase(orders.begin()+i);
                return ;
            }
            else if(newOrder.getQuantity() < tmpOrder.getQuantity())
            {

                newOrder.setPrice(tmpOrder.getPrice());

                Order extarctedOrder(tmpOrder.getTrader(), tmpOrder.getSide(),
                                     newOrder.getQuantity(), tmpOrder.getPrice());

                marketMatches.addMatch(newOrder, extarctedOrder, pa);

                tmpOrder-newOrder.getQuantity();
                return;
            }
            else if(newOrder.getQuantity() > tmpOrder.getQuantity())
            {
                newOrder - tmpOrder.getQuantity();

                Order extarctedOrder(newOrder.getTrader(), newOrder.getSide(),
                                     tmpOrder.getQuantity(), tmpOrder.getPrice());
                marketMatches.addMatch(extarctedOrder, tmpOrder, pa);
                orders.erase(orders.begin()+i);
                matchEngine(myOrderBook, newOrder, marketMatches, true);
                return;
            }
        }
        
    }

    myOrderBook.addOrder(newOrder);
 }