#include "Application.hpp"
#include <stdexcept>
#include <iostream>

namespace mvc {

Application::Application() : router_(std::make_unique<Router>()) {}

void Application::initialize() {
    // Initialize components
    if (!router_) {
        router_ = std::make_unique<Router>();
    }

    // Add any additional initialization here
    std::cout << "MVC Application initialized successfully" << std::endl;
}

void Application::run(int port) {
    // Ensure the application is initialized
    if (!router_) {
        throw std::runtime_error("Application not initialized");
    }

    std::cout << "Server starting on port " << port << std::endl;

    // Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        throw std::runtime_error("Failed to set socket options");
    }

    // Configure server address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error("Failed to bind to port");
    }

    // Listen for connections
    if (listen(server_fd, 10) < 0) {
        throw std::runtime_error("Failed to listen");
    }

    // Server loop
    while (true) {
        // Accept connection
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        
        if (client_fd < 0) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }

        // Read request
        char buffer[4096] = {0};
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer));
        if (bytes_read <= 0) {
            close(client_fd);
            continue;
        }

        // Parse and handle request
        Request request = Request::parse(std::string(buffer));
        Response response = handleRequest(request);

        // Send response
        std::string response_str = response.toString();
        send(client_fd, response_str.c_str(), response_str.length(), 0);

        // Close connection
        close(client_fd);
    }
}

Response Application::handleRequest(const Request& request) {
    // Validate request
    if (request.getPath().empty()) {
        return Response::badRequest("Invalid request path");
    }

    try {
        // Route the request to appropriate handler
        return router_->route(request);
    } catch (const std::exception& e) {
        return Response::serverError(e.what());
    }
}

} // namespace mvc