#include "storage/table.hpp"
#include <iomanip>

// Constructor
Table::Table(std::string table_name, std::vector<std::string> column_names)
    : name_(table_name), columns_(column_names) {}

void Table::insert_row(std::vector<std::string> row) {
}

void Table::display() const {
    std::cout << "Table: " << name_ << std::endl;
    std::cout << "Cols: ";
    for (const auto& col : columns_) {
        std::cout << col << "\t";
    }
    std::cout << std::endl;

    for (const auto& line: rows_) {
        for (const auto& value : line) {
            std::cout << value << "\t";
        }
        std::cout << std::endl;
    }
}   