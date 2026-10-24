#include "../../include/models/MenuItem.h"
#include <iostream>

using namespace std;

MenuItem::MenuItem(int id, string name, string category, double price)
{
    this->id = id;
    this->name = name;
    this->category = category;
    this->price = price;
}

int MenuItem::getId() const
{
    return id;
}

string MenuItem::getName() const
{
    return name;
}

string MenuItem::getCategory() const
{
    return category;
}

double MenuItem::getPrice() const
{
    return price;
}

void MenuItem::display() const
{
    cout << id << ". "
         << name << " | "
         << category << " | Rs."
         << price << endl;
}