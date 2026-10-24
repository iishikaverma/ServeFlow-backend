#include "../../include/services/MenuService.h"
#include <iostream>

using namespace std;

void MenuService::addMenuItem(MenuItem item)
{
    menuItems.push_back(item);
}

vector<MenuItem> MenuService::getAllItems() const
{
    return menuItems;
}

MenuItem* MenuService::findItemById(int id)
{
    for (MenuItem& item : menuItems)
    {
        if (item.getId() == id)
        {
            return &item;
        }
    }

    return nullptr;
}

void MenuService::displayMenu() const
{
    cout << "----- MENU -----" << endl;

    for (const MenuItem& item : menuItems)
    {
        item.display();
    }
}