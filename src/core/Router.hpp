#pragma once

#include <functional>
#include <map>
#include <string>
#include "Request.hpp"
#include "Response.hpp"

namespace mvc {

class Router {
public:
    Router() = default;
    ~Router() = default;

    // Define handler function type
    using HandlerFunction = std::function<Response(const Request&)>;

    // Register a route with its handler
    void addRoute(const std::string& path, HandlerFunction handler);

    // Match and execute the appropriate handler for a request
    Response route(const Request& request);

    // HTTP method-specific route registration
    void get(const std::string& path, HandlerFunction handler);
    void post(const std::string& path, HandlerFunction handler);
    void put(const std::string& path, HandlerFunction handler);
    void del(const std::string& path, HandlerFunction handler);

private:
    // Route storage: path -> handler mapping
    std::map<std::string, HandlerFunction> routes_;

    // Helper to create the full route key (method + path)
    std::string createRouteKey(const std::string& method, const std::string& path);
};

} // namespace mvc