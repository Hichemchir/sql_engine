#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <storage/column_schema.hpp>
#include <iomanip>
#include "common/types.hpp"

namespace sqlengine {
/**
 * in memory table with typed cols (row oriented)
 */


class Table {
private:
    std::string name_;
    std::vector<ColumnSchema> schema_;
    std::vector<std::vector<Value>> rows_;

public:
    // Constructor
    Table(std::string table_name, std::vector<ColumnSchema> schema);

    void insert_row(std::vector<Value> row);

    void display() const;  

    // getters
    const std::string& get_name() const { return name_; }
    size_t row_count() const { return rows_.size(); }
    size_t column_count() const { return schema_.size(); }
    const std::vector<ColumnSchema>& schema() const { return schema_; }
    const std::vector<std::vector<Value>>& rows() const { return rows_; }
};

}