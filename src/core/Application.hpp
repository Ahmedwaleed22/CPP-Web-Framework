#pragma once

#include <memory>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Router.hpp"
#include "Request.hpp"
#include "Response.hpp"

namespace mvc {

class Application {
public:
    Application();
    ~Application() = default;

    // Delete copy constructor and assignment operator
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    // Initialize the application
    void initialize();

    // Run the application
    void run(int port = 8080);

    // Get the router instance
    Router& getRouter() { return *router_; }

    // Handle incoming request
    Response handleRequest(const Request& request);

private:
    std::unique_ptr<Router> router_;
};

} // namespace mvc