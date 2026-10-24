#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>

#include "Customer.h"
#include "OrderItem.h"

using namespace std;

class Order
{
private:
    int orderId;
    Customer customer;
    vector<OrderItem> items;
    string status;

public:
    Order(int orderId, Customer customer);

    void addItem(OrderItem item);

    double calculateTotal() const;

    int getOrderId() const;
    Customer getCustomer() const;
    vector<OrderItem> getItems() const;
    string getStatus() const;

    void setStatus(string status);

    void display() const;
};

#endif