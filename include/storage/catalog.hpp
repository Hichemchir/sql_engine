#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <optional>
#include <vector>
#include "storage/table.hpp"

/**
 * Catalog: register all the tables
 * Responsabilities:
 * - create & del tables
 * - retrieve table by its name
 * - list tables
 */

class Catalog {
private:
    // Map table name --> unique ptr
    std::unordered_map<std::string, std::unique_ptr<Table>> tables_;

public:
    bool create_table(const std::string& table_name,
                      const std::vector<std::string>& column_names);
    bool drop_table(const std::string& table_name);
    bool table_exists(const std::string& table_name) const;


    std::vector<std::string> list_tables() const;
    void display_catalog() const;

    // Getter
    Table* get_table(const std::string& table_name);
    size_t table_count() const { return tables_.size(); }
};