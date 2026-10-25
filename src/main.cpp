#include <iostream>
#include <memory>
#include <utility>

#include "../include/models/Customer.h"
#include "../include/models/MenuItem.h"
#include "../include/models/OrderItem.h"
#include "../include/models/Order.h"

#include "../include/models/Payment.h"
#include "../include/models/CashPayment.h"
#include "../include/models/CardPayment.h"
#include "../include/models/UPIPayment.h"

#include "../include/services/MenuService.h"
#include "../include/services/OrderService.h"

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

    menuService.loadFromFile("data/menu.json");

    menuService.displayMenu();

    cout << endl;

    // Find menu items
    MenuItem* pizza = menuService.findItemById(1);
    MenuItem* burger = menuService.findItemById(2);

    // Order Items
    OrderItem pizzaOrder(*pizza, 2);
    OrderItem burgerOrder(*burger, 1);

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
        
    OrderService orderService;

    orderService.addOrder(move(order));

    orderService.saveToFile("data/orders.json");

    cout << endl;

    orderService.displayOrders();

    return 0;
}