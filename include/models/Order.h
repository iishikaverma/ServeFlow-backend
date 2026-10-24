#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <memory>

#include "Customer.h"
#include "OrderItem.h"
#include "Payment.h"

using namespace std;

class Order
{
private:
    int orderId;
    Customer customer;
    vector<OrderItem> items;
    string status;

    unique_ptr<Payment> payment;

public:
    Order(int orderId, Customer customer);

    void addItem(OrderItem item);

    double calculateTotal() const;

    void setPayment(unique_ptr<Payment> payment);

    void processPayment();

    int getOrderId() const;
    Customer getCustomer() const;
    vector<OrderItem> getItems() const;
    string getStatus() const;

    void setStatus(string status);

    void display() const;
};

#endif