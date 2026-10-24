#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>

using namespace std;

class Payment
{
protected:
    double amount;

public:
    Payment(double amount);

    virtual void processPayment() = 0;

    double getAmount() const;

    virtual ~Payment();
};

#endif