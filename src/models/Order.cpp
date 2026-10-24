#include "../../include/models/Order.h"
#include <iostream>

using namespace std;

Order::Order(int orderId, Customer customer)
    : orderId(orderId), customer(customer), status("Pending")
{
}

void Order::addItem(OrderItem item)
{
    items.push_back(item);
}

double Order::calculateTotal() const
{
    double total = 0;

    for (const OrderItem& item : items)
    {
        total += item.getSubtotal();
    }

    return total;
}

int Order::getOrderId() const
{
    return orderId;
}

Customer Order::getCustomer() const
{
    return customer;
}

vector<OrderItem> Order::getItems() const
{
    return items;
}

string Order::getStatus() const
{
    return status;
}

void Order::setStatus(string status)
{
    this->status = status;
}

void Order::display() const
{
    cout << "Order ID: " << orderId << endl;
    cout << "Customer: " << customer.getName() << endl;
    cout << "Status: " << status << endl;

    cout << endl;
    cout << "Items:" << endl;

    for (const OrderItem& item : items)
    {
        item.display();
    }

    cout << endl;
    cout << "Total: Rs." << calculateTotal() << endl;
}