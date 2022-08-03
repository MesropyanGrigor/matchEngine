 #include <stdexcept>
 #include <deque>
 #include "order_book.hpp"
 #include "engine.hpp"

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
    //for(auto it : aa )
    //{
        //it.print();
        //std::cout<<"----";
    //}
    std::cout<<std::endl;
}

 void matchEngine(OrderBook& myOrderBook, Order& newOrder, std::deque<std::deque<Order>>& marketMatches)
 {
    std::cout<<"Processing Order: "; newOrder.print(); std::cout<<std::endl;
    checkOrder(newOrder); 

    std::deque<Order>& orders = newOrder.getSide() == 'B' ? myOrderBook.getSellersOrders() : myOrderBook.getBuyersOrders();

    for (std::size_t i=0; i < orders.size(); i++)
    {
        Order& tmpOrder = orders[i];

        if(newOrder.getPrice() == tmpOrder.getPrice())
        {
            if (newOrder.getQuantity() == tmpOrder.getQuantity())
            {
                marketMatches.push_back(std::deque<Order>({newOrder, orders[i]}));

                orders.erase(orders.begin()+i);
                return ;
            }
            else if(newOrder.getQuantity() < tmpOrder.getQuantity())
            {
                Order extarctedOrder(tmpOrder.getTrader(), tmpOrder.getSide(),
                                     newOrder.getQuantity(), tmpOrder.getPrice());

                marketMatches.push_back(std::deque<Order>({newOrder, extarctedOrder}));

                tmpOrder-newOrder.getQuantity();
                return;
            }
            else if(newOrder.getQuantity() > tmpOrder.getQuantity())
            {
                newOrder - tmpOrder.getQuantity();
                Order extarctedOrder(newOrder.getTrader(), newOrder.getSide(),
                                     tmpOrder.getQuantity(), newOrder.getPrice());
                marketMatches.push_back(std::deque<Order>({extarctedOrder, tmpOrder}));
                //output(orders);
                orders.erase(orders.begin()+i);

                matchEngine(myOrderBook, newOrder, marketMatches);
                return;
           //     break;
            }
        }
        
    }

    myOrderBook.addOrder(newOrder);
 }