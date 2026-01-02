#include "storage/table.hpp"
#include <iomanip>

// Constructor
Table::Table(std::string table_name, std::vector<std::string> column_names)
    : name_(table_name), columns_(column_names) {}

void Table::insert_row(std::vector<std::string> row) {
    // Check if right number of col:
    if (row.size() != columns_.size()) {
        std::cerr << "Error: row has " << row.size()
                  << " values but table has " << columns_.size()
                  << " columns" << std::endl;
        return;
    }
    rows_.push_back(row);
}

void Table::display() const {
    std::cout << "\n Table: " << name_ << std::endl;
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