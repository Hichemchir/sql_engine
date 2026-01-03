#include "storage/table.hpp"
#include <iomanip>
#include "storage/column_schema.hpp"
#include "common/types.hpp"

namespace sqlengine { 

// Constructor
Table::Table(std::string table_name, std::vector<ColumnSchema schema)
    : name_(std::move(table_name)), schema_(std::move(schema)) {}

bool Table::insert_row(std::vector<Value> row) {
    // Check if right number of col:
    if (row.size() != columns_.size()) {
        std::cerr << "Error: row has " << row.size()
                  << " values but table has " << columns_.size()
                  << " columns" << std::endl;
        return false;
    }
    rows_.push_back(row);
    return true;
}

void Table::display() const {
    std::cout << "\nTable: " << name_ << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl; 

    for (const auto& col : columns_) {
        std::cout << std::setw(15) << col << " | ";
    }
    std::cout << std::endl;

    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;

    for (const auto& row: rows_) {
        for (const auto& value : row) {
            std::cout << std::setw(15) << value << " | ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nTotal rows: " << rows_.size() << std::endl;
}

}