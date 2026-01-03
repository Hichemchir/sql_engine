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
    for (size_t i; i < row.size(); ++i) {
        const auto& value = row[i];
        const auto& col_schema = schema_[i];

        // check if null constraint
        if (value.is_null() && !col_schema.nullable) {
            std::cerr << "Error: column " << col_schema.name << "cannot be NULL" << std::endl;
            return false;
        }

        // check type match between Col schema and row
        if (!value.is_null() && value.type() != col_schema.type) {
            std::cerr << "Error: column " << col_schema.name << "expects " 
                      << data_type_to_string(col_schema.type) << " but got " 
                      << data_type_to_string(value.type()) << std::endl;
            return false;
        }
    }
    // If all validation passed:
    rows_.push_back(std::move(row));
    return true;
}

void Table::display() const {
    std::cout << "\nTable: " << name_ << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl; 

    for (const auto& col : schema_) {
        std::string header = col.name + " (" + data_type_to_string(col.type) + ")";
        std::cout << std::setw(20) << header << " | ";
    }
    std::cout << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;

    // display data rows
    for (const auto& row: rows_) {
        for (const auto& value : row) {
            std::cout << std::setw(15) << value.to_string() << " | ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nTotal rows: " << rows_.size() << std::endl;
}

}