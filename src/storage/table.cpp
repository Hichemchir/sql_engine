#include <string>
#include <vector>
#include <iostream>
#include "storage/table.hpp"

class Table {
public:
    std::string name;
    std::vector<std::string> columns;
    std::vector<std::vector<std::string>> lines;

    void add_line(std::vector<std::string> line) {
        lines.push_back(line);
    }
    
    void display() {
        std::cout << "Table: " << name << std::endl;
        std::cout << "Cols: ";
        for (const auto& col : columns) {
            std::cout << col << "\t";
        }
        std::cout << std::endl;

        for (const auto& line: lines) {
            for (const auto& value : line) {
                std::cout << value << "\t";
            }
            std::cout << std::endl;
        }
    }   
};