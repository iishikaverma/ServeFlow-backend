#include "../../include/models/Payment.h"

Payment::Payment(double amount)
{
    this->amount = amount;
}

double Payment::getAmount() const
{
    return amount;
}

Payment::~Payment()
{
}