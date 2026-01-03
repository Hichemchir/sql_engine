#include <iostream>
#include <string>
#include "storage/table.hpp"
#include "storage/catalog.hpp"
#include "common/types.hpp"
#include "storage/column_schema.hpp"

int main() {
    std::cout << "Minimal SQL engine with typed values\n" << std::endl;
    
    // Test 1
    // Table users("users", {"name", "age"});
    // users.insert_row({"Alice", "25"});
    // users.insert_row({"Bob", "30"});
    // users.insert_row({"Charlie", "35"});
    // users.display();

    // Test 2
    // Catalog catalog;
    // catalog.create_table("users", {"name", "age"});
    // catalog.create_table("product", {"id", "product_name"});
    // catalog.display_catalog();

    // Test 3
    Catalog catalog;
    
    return 0;
}