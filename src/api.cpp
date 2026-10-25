#include <crow.h>
#include <vector>
#include <utility>

#include "../include/services/MenuService.h"
#include "../include/services/OrderService.h"

int main()
{
    crow::SimpleApp app;

    // GET /api/menu
    CROW_ROUTE(app, "/api/menu")
    ([]()
    {
        MenuService menuService;

        menuService.loadFromFile("data/menu.json");

        std::vector<crow::json::wvalue> menuList;

        for (const MenuItem& item : menuService.getAllItems())
        {
            crow::json::wvalue menuItem;

            menuItem["id"] = item.getId();
            menuItem["name"] = item.getName();
            menuItem["category"] = item.getCategory();
            menuItem["price"] = item.getPrice();

            menuList.push_back(std::move(menuItem));
        }

        return crow::json::wvalue(menuList);
    });

    // GET /api/orders
    CROW_ROUTE(app, "/api/orders")
    ([]()
    {
        OrderService orderService;

        orderService.loadFromFile("data/orders.json");

        std::vector<crow::json::wvalue> orderList;

        for (const Order& order : orderService.getAllOrders())
        {
            crow::json::wvalue orderData;

            orderData["orderId"] = order.getOrderId();
            orderData["status"] = order.getStatus();
            orderData["total"] = order.calculateTotal();

            orderData["customer"]["id"] = order.getCustomer().getId();
            orderData["customer"]["name"] = order.getCustomer().getName();
            orderData["customer"]["phone"] = order.getCustomer().getPhone();
            orderData["customer"]["email"] = order.getCustomer().getEmail();

            orderList.push_back(std::move(orderData));
        }

        return crow::json::wvalue(orderList);
    });

    app.port(18080).multithreaded().run();

    return 0;
}