#ifndef ORDER_SERVICE_H
#define ORDER_SERVICE_H

#include <vector>
#include "../models/Order.h"

using namespace std;

class OrderService
{
private:
    vector<Order> orders;

public:
    void addOrder(Order&& order);

    const vector<Order>& getAllOrders() const;

    Order* findOrderById(int orderId);

    void displayOrders() const;
};

#endif