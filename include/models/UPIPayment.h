#ifndef UPI_PAYMENT_H
#define UPI_PAYMENT_H

#include "Payment.h"

class UPIPayment : public Payment
{
public:
    UPIPayment(double amount);

    void processPayment() override;
};

#endif