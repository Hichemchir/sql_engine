#include <iostream>
#include <string>
#include "storage/table.hpp"
#include "storage/catalog.hpp"

int main() {
    std::cout << "Minimal SQL engine\n" << std::endl;
    
    // Table users("users", {"name", "age"});

    // users.insert_row({"Alice", "25"});
    // users.insert_row({"Bob", "30"});
    // users.insert_row({"Charlie", "35"});

    // users.display();

    Catalog catalog;
    catalog.create_table("users", {"name", "age"});
    catalog.create_table("product", {"id", "product_name"});
    catalog.display_catalog();
    
    return 0;
}