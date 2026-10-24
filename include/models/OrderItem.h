#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include "MenuItem.h"

class OrderItem
{
private:
    MenuItem menuItem;
    int quantity;

public:
    OrderItem(MenuItem menuItem, int quantity);

    MenuItem getMenuItem() const;
    int getQuantity() const;

    double getSubtotal() const;

    void display() const;
};

#endif