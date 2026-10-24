#include "../../include/models/UPIPayment.h"
#include <iostream>

using namespace std;

UPIPayment::UPIPayment(double amount)
    : Payment(amount)
{
}

void UPIPayment::processPayment()
{
    cout << "UPI payment of Rs." << amount
         << " processed successfully." << endl;
}