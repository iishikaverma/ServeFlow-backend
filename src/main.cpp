#include <iostream>

#include "../include/models/MenuItem.h"
#include "../include/models/Customer.h"

using namespace std;

int main()
{
    cout << "===== SERVEFLOW =====" << endl;
    cout << "Restaurant Order Management System" << endl;
    cout << endl;

    // Creating a MenuItem object
    MenuItem pizza(
        1,
        "Margherita Pizza",
        "Pizza",
        249
    );

    cout << "----- MENU ITEM -----" << endl;
    pizza.display();

    cout << endl;

    // Creating a Customer object
    Customer customer(
        101,
        "Rahul Sharma",
        "9876543210",
        "rahul@example.com"
    );

    cout << "----- CUSTOMER -----" << endl;
    customer.display();

    return 0;
}