#include "../../include/models/OrderItem.h"
#include <iostream>

using namespace std;

OrderItem::OrderItem(MenuItem menuItem, int quantity)
    : menuItem(menuItem), quantity(quantity)
{
}

MenuItem OrderItem::getMenuItem() const
{
    return menuItem;
}

int OrderItem::getQuantity() const
{
    return quantity;
}

double OrderItem::getSubtotal() const
{
    return menuItem.getPrice() * quantity;
}

void OrderItem::display() const
{
    cout << menuItem.getName()
         << " x "
         << quantity
         << " = Rs."
         << getSubtotal()
         << endl;
}