#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

using namespace std;

class Customer
{
private:
    int id;
    string name;
    string phone;
    string email;

public:
    Customer(int id, string name, string phone, string email);

    int getId() const;
    string getName() const;
    string getPhone() const;
    string getEmail() const;

    void display() const;
};

#endif