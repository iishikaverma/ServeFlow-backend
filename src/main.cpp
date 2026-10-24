#include <iostream>

#include "../include/models/Customer.h"
#include "../include/models/MenuItem.h"
#include "../include/models/OrderItem.h"

using namespace std;

int main()
{
    cout << "===== SERVEFLOW =====" << endl;
    cout << "Restaurant Order Management System" << endl;
    cout << endl;

    // Customer
    Customer customer(
        101,
        "Rahul Sharma",
        "9876543210",
        "rahul@example.com"
    );

    cout << "----- CUSTOMER -----" << endl;
    customer.display();

    cout << endl;

    // Menu Items
    MenuItem pizza(
        1,
        "Margherita Pizza",
        "Pizza",
        249.00
    );

    MenuItem burger(
        2,
        "Classic Burger",
        "Burgers",
        199.00
    );

    cout << "----- MENU -----" << endl;

    pizza.display();
    burger.display();

    cout << endl;

    // Order Items
    OrderItem pizzaOrder(pizza, 2);
    OrderItem burgerOrder(burger, 1);

    cout << "----- ORDER ITEMS -----" << endl;

    pizzaOrder.display();
    burgerOrder.display();

    return 0;
}