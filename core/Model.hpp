#pragma once

#include "Database.hpp"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace mvc {

class Model {
public:
    Model(std::shared_ptr<Database> db);
    virtual ~Model() = default;

    // Save the model to the database
    virtual bool save() = 0;

    // Load model by ID
    virtual bool load(int id) = 0;

    // Delete model from database
    virtual bool remove() = 0;

    // Set a field value
    void setValue(const std::string& field, const std::string& value);

    // Get a field value
    std::string getValue(const std::string& field) const;

protected:
    std::shared_ptr<Database> db_;
    std::unordered_map<std::string, std::string> fields_;
    virtual std::string getTableName() const = 0;
};

} // namespace mvc