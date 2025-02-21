#include "Response.hpp"
#include <sstream>

namespace mvc {

Response::Response(int status) : status_(status) {}

void Response::setContentType(const std::string& contentType) {
    addHeader("Content-Type", contentType);
}

bool Response::hasHeader(const std::string& key) const {
    return headers_.find(key) != headers_.end();
}

std::string Response::getHeader(const std::string& key) const {
    auto it = headers_.find(key);
    return it != headers_.end() ? it->second : "";
}

std::string Response::toString() const {
    std::stringstream ss;

    // Add status line
    ss << "HTTP/1.1 " << status_ << " ";
    switch (status_) {
        case 200: ss << "OK"; break;
        case 201: ss << "Created"; break;
        case 400: ss << "Bad Request"; break;
        case 404: ss << "Not Found"; break;
        case 500: ss << "Internal Server Error"; break;
        default: ss << "Unknown"; break;
    }
    ss << "\r\n";

    // Add Content-Length header if not present
    if (!hasHeader("Content-Length")) {
        const_cast<Response*>(this)->addHeader("Content-Length", std::to_string(body_.length()));
    }

    // Add Content-Type header if not present
    if (!hasHeader("Content-Type")) {
        const_cast<Response*>(this)->addHeader("Content-Type", "text/plain");
    }

    // Add headers
    for (const auto& header : headers_) {
        ss << header.first << ": " << header.second << "\r\n";
    }

    // Add empty line to separate headers from body
    ss << "\r\n";

    // Add body
    ss << body_;

    return ss.str();
}

Response Response::ok(const std::string& body) {
    Response response(200);
    response.setBody(body);
    return response;
}

Response Response::created(const std::string& body) {
    Response response(201);
    response.setBody(body);
    return response;
}

Response Response::badRequest(const std::string& message) {
    Response response(400);
    response.setBody(message);
    return response;
}

Response Response::notFound(const std::string& message) {
    Response response(404);
    response.setBody(message);
    return response;
}

Response Response::serverError(const std::string& message) {
    Response response(500);
    response.setBody(message);
    return response;
}

} // namespace mvc