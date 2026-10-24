#include "../../include/services/MenuService.h"
#include <iostream>
#include "../../include/utils/FileManager.h"
#include <nlohmann/json.hpp>

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

void MenuService::loadFromFile(const string& filePath)
{
    auto data = FileManager::readJson(filePath);

    menuItems.clear();

    for (const auto& item : data)
    {
        MenuItem menuItem(
            item["id"],
            item["name"],
            item["category"],
            item["price"]
        );

        menuItems.push_back(menuItem);
    }
}

void MenuService::displayMenu() const
{
    cout << "----- MENU -----" << endl;

    for (const MenuItem& item : menuItems)
    {
        item.display();
    }
}