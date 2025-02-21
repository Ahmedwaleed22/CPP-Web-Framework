#include "View.hpp"
#include <unistd.h>

namespace mvc {

View::View(const std::string& templatePath) {
    // Convert relative path to absolute path
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::string projectRoot(cwd);
        templatePath_ = projectRoot + "/src/" + templatePath;
    } else {
        throw std::runtime_error("Failed to get current working directory");
    }
}

void View::setVariable(const std::string& key, const std::string& value) {
    variables_[key] = value;
}

std::string View::loadTemplate(const std::string& path) const {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open template file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string View::replaceVariables(const std::string& content) const {
    std::string result = content;
    for (const auto& [key, value] : variables_) {
        std::string placeholder = "{{" + key + "}}";
        size_t pos = 0;
        while ((pos = result.find(placeholder, pos)) != std::string::npos) {
            result.replace(pos, placeholder.length(), value);
            pos += value.length();
        }
    }
    return result;
}

std::string View::render() const {
    std::string content = loadTemplate(templatePath_);
    return replaceVariables(content);
}

} // namespace mvc