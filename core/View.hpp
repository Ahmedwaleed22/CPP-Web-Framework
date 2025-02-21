#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace mvc {

class View {
public:
    View(const std::string& templatePath);
    
    void setVariable(const std::string& key, const std::string& value);
    std::string render() const;

private:
    std::string loadTemplate(const std::string& path) const;
    std::string replaceVariables(const std::string& content) const;

    std::string templatePath_;
    std::unordered_map<std::string, std::string> variables_;
};

} // namespace mvc