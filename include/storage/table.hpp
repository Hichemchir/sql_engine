#pragma once
#include <string>
#include <vector>
#include <iostream>

class Table {
private:
    std::string name_;
    std::vector<std::string> columns_;
    std::vector<std::vector<std::string>> rows_;

public:
    // Constructor
    Table(std::string table_name, std::vector<std::string> column_names);

    void insert_row(std::vector<std::string> row);

    void display() const;  

    // getters
    std::string get_name() const { return name_; }
    size_t row_count() const { return rows_.size(); }
    size_t column_count() const { return columns_.size(); }
};