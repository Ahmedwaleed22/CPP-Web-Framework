#include "../core/Application.hpp"
#include "../core/Request.hpp"
#include "../core/Response.hpp"
#include "../core/View.hpp"
#include <iostream>

using namespace mvc;

// Example handler functions
Response handleHome(const Request& req) {
    View view("views/home.html");
    view.setVariable("title", "Better Web Search");
    view.setVariable("heading", "Better Web Search");
    view.setVariable("content", "Welcome to our advanced web search platform");
    return Response::ok(view.render(), "text/html");
}

Response handleSearch(const Request& req) {
    if (!req.hasParam("q")) {
        return Response::badRequest("Missing search query parameter");
    }
    
    std::string query = req.getParam("q");
    // In a real application, you would perform the search here
    return Response::ok("Search results for: " + query);
}

Response handleSubmit(const Request& req) {
    if (req.getBody().empty()) {
        return Response::badRequest("Empty request body");
    }
    
    // In a real application, you would process the submitted data here
    return Response::created("Data submitted successfully");
}

int main() {
    try {
        // Create and initialize the application
        Application app;
        app.initialize();
        
        // Get router instance
        Router& router = app.getRouter();
        
        // Register routes
        router.get("/", handleHome);
        router.get("/search", handleSearch);
        router.post("/submit", handleSubmit);
        
        // Start the server on port 8080
        app.run(8080);
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}