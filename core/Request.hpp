#pragma once

#include <string>
#include <map>
#include <vector>

namespace mvc {

class Request {
public:
    Request() = default;
    ~Request() = default;

    // Parse raw HTTP request string into Request object
    static Request parse(const std::string& raw_request);

    // Getters
    const std::string& getMethod() const { return method_; }
    const std::string& getPath() const { return path_; }
    const std::string& getBody() const { return body_; }
    const std::map<std::string, std::string>& getHeaders() const { return headers_; }
    const std::map<std::string, std::string>& getParams() const { return params_; }

    // Setters
    void setMethod(const std::string& method) { method_ = method; }
    void setPath(const std::string& path) { path_ = path; }
    void setBody(const std::string& body) { body_ = body; }
    void addHeader(const std::string& key, const std::string& value) { headers_[key] = value; }
    void addParam(const std::string& key, const std::string& value) { params_[key] = value; }

    // Helper methods
    bool hasHeader(const std::string& key) const;
    std::string getHeader(const std::string& key) const;
    bool hasParam(const std::string& key) const;
    std::string getParam(const std::string& key) const;

private:
    std::string method_;
    std::string path_;
    std::string body_;
    std::map<std::string, std::string> headers_;
    std::map<std::string, std::string> params_;
};

} // namespace mvc