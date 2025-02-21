#include "Request.hpp"
#include <sstream>
#include <algorithm>

namespace mvc {

Request Request::parse(const std::string& raw_request) {
    Request request;
    std::istringstream stream(raw_request);
    std::string line;

    // Parse request line (first line)
    if (std::getline(stream, line)) {
        std::istringstream request_line(line);
        std::string method, path, version;
        request_line >> method >> path >> version;
        
        // Set method and path
        request.setMethod(method);
        
        // Parse path and query parameters
        size_t query_start = path.find('?');
        if (query_start != std::string::npos) {
            std::string query = path.substr(query_start + 1);
            path = path.substr(0, query_start);
            
            // Parse query parameters
            std::istringstream query_stream(query);
            std::string param;
            while (std::getline(query_stream, param, '&')) {
                size_t eq_pos = param.find('=');
                if (eq_pos != std::string::npos) {
                    std::string key = param.substr(0, eq_pos);
                    std::string value = param.substr(eq_pos + 1);
                    request.addParam(key, value);
                }
            }
        }
        request.setPath(path);
    }

    // Parse headers
    while (std::getline(stream, line) && !line.empty() && line != "\r") {
        // Remove \r if present
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        size_t colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string key = line.substr(0, colon_pos);
            std::string value = line.substr(colon_pos + 1);
            
            // Trim leading/trailing whitespace from value
            value.erase(0, value.find_first_not_of(" "));
            value.erase(value.find_last_not_of(" ") + 1);
            
            request.addHeader(key, value);
        }
    }

    // Parse body
    std::string body;
    while (std::getline(stream, line)) {
        if (!body.empty()) {
            body += "\n";
        }
        body += line;
    }
    request.setBody(body);

    return request;
}

bool Request::hasParam(const std::string& key) const {
    return params_.find(key) != params_.end();
}

std::string Request::getParam(const std::string& key) const {
    auto it = params_.find(key);
    return it != params_.end() ? it->second : "";
}

} // namespace mvc