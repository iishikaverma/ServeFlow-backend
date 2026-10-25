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

    void loadFromFile(const string& filePath);

    void saveToFile(const string& filePath);

    void displayOrders() const;
};

#endif