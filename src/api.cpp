#include <crow.h>
#include <vector>
#include <utility>
#include <memory>
#include <string>

#include "../include/services/MenuService.h"
#include "../include/services/OrderService.h"
#include "../include/models/CashPayment.h"
#include "../include/models/CardPayment.h"
#include "../include/models/UPIPayment.h"

using namespace std;

int main()
{
    crow::SimpleApp app;

    // GET /api/menu
    CROW_ROUTE(app, "/api/menu")
    ([]()
    {
        MenuService menuService;

        menuService.loadFromFile("data/menu.json");

        vector<crow::json::wvalue> menuList;

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

        vector<crow::json::wvalue> orderList;

        for (const Order& order : orderService.getAllOrders())
        {
            crow::json::wvalue orderData;

            orderData["orderId"] = order.getOrderId();
            orderData["status"] = order.getStatus();
            orderData["total"] = order.calculateTotal();

            orderData["customer"]["id"] =
                order.getCustomer().getId();

            orderData["customer"]["name"] =
                order.getCustomer().getName();

            orderData["customer"]["phone"] =
                order.getCustomer().getPhone();

            orderData["customer"]["email"] =
                order.getCustomer().getEmail();

            orderList.push_back(std::move(orderData));
        }

        return crow::json::wvalue(orderList);
    });


    // POST /api/orders
    CROW_ROUTE(app, "/api/orders")
        .methods(crow::HTTPMethod::POST)
    ([](const crow::request& req)
    {
        auto body = crow::json::load(req.body);

        if (!body)
        {
            return crow::response(400, "Invalid JSON");
        }

        // Validate required fields
        if (!body.has("orderId") ||
            !body.has("customer") ||
            !body.has("items"))
        {
            return crow::response(
                400,
                "Missing required fields: orderId, customer or items"
            );
        }

        // Validate customer
        if (!body["customer"].has("id") ||
            !body["customer"].has("name") ||
            !body["customer"].has("phone") ||
            !body["customer"].has("email"))
        {
            return crow::response(
                400,
                "Incomplete customer information"
            );
        }

        // Validate items
        if (body["items"].size() == 0)
        {
            return crow::response(
                400,
                "Order must contain at least one item"
            );
        }

        try
        {
            int orderId = body["orderId"].i();

            auto customerData = body["customer"];

            Customer customer(
                customerData["id"].i(),
                customerData["name"].s(),
                customerData["phone"].s(),
                customerData["email"].s()
            );

            Order order(orderId, customer);

            // Add items
            for (const auto& itemData : body["items"])
            {
                // Validate item fields
                if (!itemData.has("id") ||
                    !itemData.has("name") ||
                    !itemData.has("category") ||
                    !itemData.has("price") ||
                    !itemData.has("quantity"))
                {
                    return crow::response(
                        400,
                        "Incomplete item information"
                    );
                }

                // Validate quantity
                if (itemData["quantity"].i() <= 0)
                {
                    return crow::response(
                        400,
                        "Item quantity must be greater than zero"
                    );
                }

                // Validate price
                if (itemData["price"].d() < 0)
                {
                    return crow::response(
                        400,
                        "Item price cannot be negative"
                    );
                }

                MenuItem menuItem(
                    itemData["id"].i(),
                    itemData["name"].s(),
                    itemData["category"].s(),
                    itemData["price"].d()
                );

                OrderItem orderItem(
                    menuItem,
                    itemData["quantity"].i()
                );

                order.addItem(orderItem);
            }

            // Save order
            OrderService orderService;

            orderService.loadFromFile("data/orders.json");

            orderService.addOrder(std::move(order));

            orderService.saveToFile("data/orders.json");

            // Find saved order
            Order* savedOrder =
                orderService.findOrderById(orderId);

            crow::json::wvalue response;

            response["message"] =
                "Order created successfully";

            response["orderId"] =
                orderId;

            response["total"] =
                savedOrder->calculateTotal();

            return crow::response(201, response);
        }
        catch (...)
        {
            return crow::response(
                400,
                "Invalid order data"
            );
        }
    });


    // POST /api/orders/<orderId>/payment
    CROW_ROUTE(app, "/api/orders/<int>/payment")
        .methods(crow::HTTPMethod::POST)
    ([](const crow::request& req, int orderId)
    {
        auto body = crow::json::load(req.body);

        if (!body)
        {
            return crow::response(
                400,
                "Invalid JSON"
            );
        }

        try
        {
            // Payment only needs the payment method
            if (!body.has("method"))
            {
                return crow::response(
                    400,
                    "Payment method is required"
                );
            }

            string method = body["method"].s();

            OrderService orderService;

            orderService.loadFromFile("data/orders.json");

            Order* order =
                orderService.findOrderById(orderId);

            if (order == nullptr)
            {
                return crow::response(
                    404,
                    "Order not found"
                );
            }

            double amount =
                order->calculateTotal();

            unique_ptr<Payment> payment;

            // Runtime polymorphism
            if (method == "cash")
            {
                payment =
                    make_unique<CashPayment>(amount);
            }
            else if (method == "card")
            {
                payment =
                    make_unique<CardPayment>(amount);
            }
            else if (method == "upi")
            {
                payment =
                    make_unique<UPIPayment>(amount);
            }
            else
            {
                return crow::response(
                    400,
                    "Invalid payment method. Use cash, card or upi."
                );
            }

            order->setPayment(
                std::move(payment)
            );

            order->processPayment();

            orderService.saveToFile(
                "data/orders.json"
            );

            crow::json::wvalue response;

            response["message"] =
                "Payment processed successfully";

            response["orderId"] =
                orderId;

            response["paymentMethod"] =
                method;

            response["amount"] =
                amount;

            response["status"] =
                order->getStatus();

            return crow::response(
                200,
                response
            );
        }
        catch (...)
        {
            return crow::response(
                400,
                "Invalid payment data"
            );
        }
    });


    // Start server
    app.port(18080)
       .multithreaded()
       .run();

    return 0;
}