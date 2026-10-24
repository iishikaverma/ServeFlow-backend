#include "../../include/services/OrderService.h"
#include <iostream>
#include <utility>

using namespace std;

void OrderService::addOrder(Order&& order)
{
    orders.push_back(move(order));
}

const vector<Order>& OrderService::getAllOrders() const
{
    return orders;
}

Order* OrderService::findOrderById(int orderId)
{
    for (Order& order : orders)
    {
        if (order.getOrderId() == orderId)
        {
            return &order;
        }
    }

    return nullptr;
}

void OrderService::displayOrders() const
{
    cout << "===== ALL ORDERS =====" << endl;

    for (const Order& order : orders)
    {
        order.display();
        cout << "----------------------" << endl;
    }
}