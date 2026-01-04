#pragma once
#include <string>
#include <optional>
#include <vector>
#include <iostream>
#include <storage/column_schema.hpp>
#include <iomanip>
#include "common/types.hpp"
#include <functional>

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

    // Query operations
    bool insert_row(std::vector<Value> row);

    // SELECT * FROM TABLE
    const std::vector<std::vector<Value>>& select_all() const; 

    /** Predicate pushdown
     * Filters rows based on a predicate function: SELECT * FROM table WHERE predicate(row)
     * function will be a lambda
     *  */ 
    std::vector<std::vector<Value>> filter(
        std::function<bool(const std::vector<Value>&)> predicate) const;
        
    /** Predicate pushdown
     *  Simple column comparison filter: SELECT * FROM table WHERE column_name operation value
     */
    std::vector<std::vector<Value>> filter_column(
        const std::string& column_name,
        std::function<bool(const Value&)> predicate) const;
    
    /** Projection pushdown
     * SELECT column FROM table
     */
    std::vector<std::vector<Value>> select_columns(
        const std::vector<std::string>& column_names) const;

    // Get row by index
    std::optional<std::vector<Value>> get_row(size_t index) const;

    // Fin col index by name
    std::optional<size_t> find_column_index(const std::string& column_name) const;

    void display() const;  
    // Display filtered results
    static void display_results(
        const std::vector<std::vector<Value>>& results,
        const std::vector<std::string>& column_names
    );

    // getters
    const std::string& get_name() const { return name_; }
    size_t row_count() const { return rows_.size(); }
    size_t column_count() const { return schema_.size(); }
    const std::vector<ColumnSchema>& schema() const { return schema_; }
    const std::vector<std::vector<Value>>& rows() const { return rows_; }
};

} // namespace sqlengine