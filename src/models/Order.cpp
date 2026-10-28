#include "../../include/models/Order.h"
#include <iostream>
#include <utility>

using namespace std;

Order::Order(int orderId, Customer customer)
    : orderId(orderId),
      customer(customer),
      status("Received"),
      paid(false),
      payment(nullptr)
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

void Order::setPayment(unique_ptr<Payment> payment)
{
    this->payment = move(payment);
}

void Order::processPayment()
{
    if (payment)
    {
        payment->processPayment();
        paid = true;
    }
    else
    {
        cout << "No payment method selected." << endl;
    }
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

bool Order::isPaid() const
{
    return paid;
}

void Order::setPaid(bool paid)
{
    this->paid = paid;
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