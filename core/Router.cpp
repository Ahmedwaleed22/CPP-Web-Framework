#include "Router.hpp"
#include <stdexcept>

namespace mvc {

void Router::addRoute(const std::string& path, HandlerFunction handler) {
    routes_[path] = std::move(handler);
}

Response Router::route(const Request& request) {
    // Create the route key from method and path
    std::string routeKey = createRouteKey(request.getMethod(), request.getPath());

    // Find the handler for this route
    auto it = routes_.find(routeKey);
    if (it == routes_.end()) {
        return Response::notFound("Route not found: " + routeKey);
    }

    // Execute the handler
    return it->second(request);
}

void Router::get(const std::string& path, HandlerFunction handler) {
    addRoute(createRouteKey("GET", path), std::move(handler));
}

void Router::post(const std::string& path, HandlerFunction handler) {
    addRoute(createRouteKey("POST", path), std::move(handler));
}

void Router::put(const std::string& path, HandlerFunction handler) {
    addRoute(createRouteKey("PUT", path), std::move(handler));
}

void Router::del(const std::string& path, HandlerFunction handler) {
    addRoute(createRouteKey("DELETE", path), std::move(handler));
}

std::string Router::createRouteKey(const std::string& method, const std::string& path) {
    return method + ":" + path;
}

} // namespace mvc