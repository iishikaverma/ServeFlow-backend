#include "../../include/services/OrderService.h"
#include <iostream>
#include <utility>

#include "../../include/utils/FileManager.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void OrderService::addOrder(Order&& order)
{
    orders.push_back(move(order));
}

const vector<Order>& OrderService::getAllOrders() const
{
    return orders;
}

Order* OrderService::findOrderById(int orderId)
{
    for (Order& order : orders)
    {
        if (order.getOrderId() == orderId)
        {
            return &order;
        }
    }

    return nullptr;
}

void OrderService::loadFromFile(const string& filePath)
{
    auto data = FileManager::readJson(filePath);

    orders.clear();

    for (const auto& orderData : data)
    {
        Customer customer(
            orderData["customer"]["id"],
            orderData["customer"]["name"],
            orderData["customer"]["phone"],
            orderData["customer"]["email"]
        );

        Order order(
            orderData["orderId"],
            customer
        );

        order.setStatus(orderData["status"]);

        for (const auto& itemData : orderData["items"])
        {
            MenuItem menuItem(
                0,
                itemData["name"],
                "Unknown",
                itemData["price"]
            );

            OrderItem orderItem(
                menuItem,
                itemData["quantity"]
            );

            order.addItem(orderItem);
        }

        orders.push_back(std::move(order));
    }
}

void OrderService::saveToFile(const string& filePath)
{
    json data = json::array();

    for (const Order& order : orders)
    {
        json orderData;

        orderData["orderId"] = order.getOrderId();

        orderData["customer"]["id"] = order.getCustomer().getId();
        orderData["customer"]["name"] = order.getCustomer().getName();
        orderData["customer"]["phone"] = order.getCustomer().getPhone();
        orderData["customer"]["email"] = order.getCustomer().getEmail();

        orderData["status"] = order.getStatus();
        orderData["total"] = order.calculateTotal();

        json items = json::array();

        for (const OrderItem& item : order.getItems())
        {
            json itemData;

            itemData["name"] = item.getMenuItem().getName();
            itemData["quantity"] = item.getQuantity();
            itemData["price"] = item.getMenuItem().getPrice();
            itemData["subtotal"] = item.getSubtotal();

            items.push_back(itemData);
        }

        orderData["items"] = items;

        data.push_back(orderData);
    }

    FileManager::writeJson(filePath, data);
}

void OrderService::displayOrders() const
{
    cout << "===== ALL ORDERS =====" << endl;

    for (const Order& order : orders)
    {
        order.display();
        cout << "----------------------" << endl;
    }
}