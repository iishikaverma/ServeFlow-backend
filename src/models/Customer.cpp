#include "../../include/models/Customer.h"
#include <iostream>

using namespace std;

Customer::Customer(int id, string name, string phone, string email)
{
    this->id = id;
    this->name = name;
    this->phone = phone;
    this->email = email;
}

int Customer::getId() const
{
    return id;
}

string Customer::getName() const
{
    return name;
}

string Customer::getPhone() const
{
    return phone;
}

string Customer::getEmail() const
{
    return email;
}

void Customer::display() const
{
    cout << "Customer ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Phone: " << phone << endl;
    cout << "Email: " << email << endl;
}