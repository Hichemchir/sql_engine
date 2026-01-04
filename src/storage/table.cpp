#include "storage/table.hpp"
#include <iomanip>
#include "storage/column_schema.hpp"
#include "common/types.hpp"

namespace sqlengine { 

// Constructor
Table::Table(std::string table_name, std::vector<ColumnSchema> schema)
    : name_(std::move(table_name)), schema_(std::move(schema)) {}

bool Table::insert_row(std::vector<Value> row) {
    // Check if right number of col:
    if (row.size() != schema_.size()) {
        std::cerr << "Error: row has " << row.size()
                  << " values but table has " << schema_.size()
                  << " columns" << std::endl;
        return false;
    }
    // Validate each column's type and constraints:
    for (size_t i = 0; i < row.size(); ++i) {
        const auto& value = row[i];
        const auto& col_schema = schema_[i];

        // check if null constraint
        if (value.is_null() && !col_schema.nullable) {
            std::cerr << "Error: column " << col_schema.name << "cannot be NULL" << std::endl;
            return false;
        }

        // check type match between Col schema and row
        if (!value.is_null() && value.type() != col_schema.type) {
            std::cerr << "Error: column " << col_schema.name << " expects " 
                      << data_type_to_string(col_schema.type) << " but got " 
                      << data_type_to_string(value.type()) << std::endl;
            return false;
        }
    }
    // If all validation passed:
    rows_.push_back(std::move(row));
    return true;
}

// Query Operations

const std::vector<std::vector<Value>>& Table::select_all() const {
    return rows_;
}

std::vector<std::vector<Value>> Table::filter(
    std::function<bool(const std::vector<Value>&)> predicate) const {
        std::vector<std::vector<Value>> results;
        
        for (const auto& row : rows_) {
            if (predicate(row)) {
                results.push_back(row);
            }
        }
        return results;
    }

std::vector<std::vector<Value>> Table::filter_column(
    const std::string& column_name,
    std::function<bool(const Value&)> predicate) const {
        std::vector<std::vector<Value>> results;

        
    }


// Display functions

void Table::display() const {
    // Fixed col width
    const int col_width = 20;

    std::cout << "\nTable: " << name_ << std::endl;

    // Calculate separator
    int total_width = (col_width + 3) * schema_.size() - 3;
    std::string separator(total_width, '-');

    std::cout << separator << std::endl;

    for (const auto& col : schema_) {
        std::string header = col.name + " (" + data_type_to_string(col.type) + ")";
        std::cout << std::setw(col_width) << header << " | ";
    }
    std::cout << std::endl;
    std::cout << separator << std::endl;

    // display data rows
    for (const auto& row: rows_) {
        for (const auto& value : row) {
            std::cout << std::setw(col_width) << value.to_string() << " | ";
        }
        std::cout << std::endl;
    }

    std::cout << separator << std::endl;
    std::cout << "\nTotal rows: " << rows_.size() << std::endl;
}

} // namespace sqlengine