#include "../../include/models/CardPayment.h"
#include <iostream>

using namespace std;

CardPayment::CardPayment(double amount)
    : Payment(amount)
{
}

void CardPayment::processPayment()
{
    cout << "Card payment of Rs." << amount
         << " processed successfully." << endl;
}