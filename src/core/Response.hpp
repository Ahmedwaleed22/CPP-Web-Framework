#pragma once

#include <string>
#include <map>

namespace mvc {

class Response {
public:
    Response(int status = 200);
    ~Response() = default;

    // Getters
    int getStatus() const { return status_; }
    const std::string& getBody() const { return body_; }
    const std::map<std::string, std::string>& getHeaders() const { return headers_; }

    // Setters
    void setStatus(int status) { status_ = status; }
    void setBody(const std::string& body) { body_ = body; }
    void addHeader(const std::string& key, const std::string& value) { headers_[key] = value; }

    // Helper methods
    void setContentType(const std::string& contentType);
    bool hasHeader(const std::string& key) const;
    std::string getHeader(const std::string& key) const;
    std::string toString() const;

    // Static response creators
    static Response ok(const std::string& body = "");
    static Response created(const std::string& body = "");
    static Response badRequest(const std::string& message = "Bad Request");
    static Response notFound(const std::string& message = "Not Found");
    static Response serverError(const std::string& message = "Internal Server Error");

private:
    int status_;
    std::string body_;
    std::map<std::string, std::string> headers_;
};

} // namespace mvc