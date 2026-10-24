#ifndef CASH_PAYMENT_H
#define CASH_PAYMENT_H

#include "Payment.h"

class CashPayment : public Payment
{
public:
    CashPayment(double amount);

    void processPayment() override;
};

#endif