#include "Database.hpp"

namespace mvc {

Database::Database(const std::string& host, const std::string& user,
                   const std::string& password, const std::string& database) {
    connect(host, user, password, database);
}

Database::~Database() {
    if (connection_) {
        mysql_close(connection_);
    }
}

void Database::connect(const std::string& host, const std::string& user,
                       const std::string& password, const std::string& database) {
    connection_ = mysql_init(nullptr);
    if (!connection_) {
        throw std::runtime_error("Failed to initialize MySQL connection");
    }

    if (!mysql_real_connect(connection_, host.c_str(), user.c_str(),
                           password.c_str(), database.c_str(), 0, nullptr, 0)) {
        std::string error = mysql_error(connection_);
        mysql_close(connection_);
        throw std::runtime_error("Failed to connect to database: " + error);
    }
}

bool Database::execute(const std::string& query) {
    return mysql_query(connection_, query.c_str()) == 0;
}

MYSQL_RES* Database::query(const std::string& query) {
    if (mysql_query(connection_, query.c_str()) != 0) {
        throw std::runtime_error("Query execution failed: " + 
                                std::string(mysql_error(connection_)));
    }
    
    MYSQL_RES* result = mysql_store_result(connection_);
    if (!result && mysql_field_count(connection_) > 0) {
        throw std::runtime_error("Failed to store query result: " +
                                std::string(mysql_error(connection_)));
    }
    
    return result;
}

unsigned long long Database::getLastInsertId() const {
    return mysql_insert_id(connection_);
}

unsigned long long Database::getAffectedRows() const {
    return mysql_affected_rows(connection_);
}

} // namespace mvc