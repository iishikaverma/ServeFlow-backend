#include <iostream>
#include <memory>

#include "../include/models/Customer.h"
#include "../include/models/MenuItem.h"
#include "../include/models/OrderItem.h"
#include "../include/models/Order.h"

#include "../include/models/Payment.h"
#include "../include/models/CashPayment.h"
#include "../include/models/CardPayment.h"
#include "../include/models/UPIPayment.h"

#include "../include/services/MenuService.h"

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

    // Menu Service
    MenuService menuService;

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

    menuService.addMenuItem(pizza);
    menuService.addMenuItem(burger);

    menuService.displayMenu();

    cout << endl;

    // Order Items
    OrderItem pizzaOrder(pizza, 2);
    OrderItem burgerOrder(burger, 1);

    // Order
    Order order(5001, customer);

    order.addItem(pizzaOrder);
    order.addItem(burgerOrder);

    cout << "----- ORDER -----" << endl;

    order.display();

    cout << endl;
    cout << "----- PAYMENT -----" << endl;

    order.setPayment(
        make_unique<UPIPayment>(order.calculateTotal())
    );

    order.processPayment();

    cout << endl;

    cout << "Final Order Status: "
        << order.getStatus()
        << endl;

    return 0;
}