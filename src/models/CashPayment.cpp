#include "../../include/models/CashPayment.h"
#include <iostream>

using namespace std;

CashPayment::CashPayment(double amount)
    : Payment(amount)
{
}

void CashPayment::processPayment()
{
    cout << "Cash payment of Rs." << amount
         << " processed successfully." << endl;
}