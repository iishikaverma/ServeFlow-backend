#ifndef CARD_PAYMENT_H
#define CARD_PAYMENT_H

#include "Payment.h"

class CardPayment : public Payment
{
public:
    CardPayment(double amount);

    void processPayment() override;
};

#endif