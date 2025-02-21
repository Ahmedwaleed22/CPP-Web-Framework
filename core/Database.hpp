#pragma once

#include <string>
#include <memory>
#include <mysql/mysql.h>
#include <stdexcept>

namespace mvc {

class Database {
public:
    Database(const std::string& host, const std::string& user,
            const std::string& password, const std::string& database);
    ~Database();

    // Prevent copying
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    // Execute a query that doesn't return results (INSERT, UPDATE, DELETE)
    bool execute(const std::string& query);

    // Execute a query that returns results (SELECT)
    MYSQL_RES* query(const std::string& query);

    // Get the ID of the last inserted row
    unsigned long long getLastInsertId() const;

    // Get the number of affected rows from the last query
    unsigned long long getAffectedRows() const;

private:
    MYSQL* connection_;
    void connect(const std::string& host, const std::string& user,
                const std::string& password, const std::string& database);
};

} // namespace mvc