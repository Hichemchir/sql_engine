#include <iostream>
#include <string>
#include "storage/table.hpp"
#include "storage/catalog.hpp"
#include "common/types.hpp"
#include "storage/column_schema.hpp"

using namespace sqlengine;

int main() {
    std::cout << "SQL engine with typed values\n" << std::endl;
    
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

    catalog.create_table("users", 
        {
            ColumnSchema("id", DataType::INTEGER, false, true),
            ColumnSchema("name", DataType::TEXT, false),
            ColumnSchema("age", DataType::INTEGER, true),
            ColumnSchema("salary", DataType::REAL, true)
        });
    catalog.display_catalog();
    std::cout << std::endl;
    
    Table* users = catalog.get_table("users");
    if (users) {
        users->insert_row(
            {Value::make_integer(1),
             Value::make_text("Hichem"),
             Value::make_integer(27),
             Value::make_real(100.0)
            }
        );
        users->insert_row({
            Value::make_integer(2),
            Value::make_text("Bob"),
            Value::make_integer(30),
            Value::make_null()  
        });
        users->display();
    }

    // Test if wrong type
    bool result = users->insert_row({
        Value::make_text("INVALID"),
        Value::make_text("Test"),
        Value::make_integer(99),
        Value::make_null()
    });
    
    if (!result) {
        std::cout << "\n Type invalidation works well" << std::endl;
    }
    
    return 0;
}