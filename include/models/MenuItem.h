#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

using namespace std;

class MenuItem
{
private:
    int id;
    string name;
    string category;
    double price;

public:
    MenuItem(int id, string name, string category, double price);

    int getId() const;
    string getName() const;
    string getCategory() const;
    double getPrice() const;

    void display() const;
};

#endif