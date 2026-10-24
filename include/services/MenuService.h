#ifndef MENU_SERVICE_H
#define MENU_SERVICE_H

#include <vector>
#include "../models/MenuItem.h"

using namespace std;

class MenuService
{
private:
    vector<MenuItem> menuItems;

public:
    void addMenuItem(MenuItem item);

    vector<MenuItem> getAllItems() const;

    MenuItem* findItemById(int id);

    void loadFromFile(const string& filePath);

    void displayMenu() const;
};

#endif