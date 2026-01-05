#include <iostream>
#include <string>
#include "storage/table.hpp"
#include "storage/catalog.hpp"
#include "common/types.hpp"
#include "storage/column_schema.hpp"

using namespace sqlengine;

void print_separator() {
    std::cout << "\n" << std::string(80, '=') << "\n" << std::endl;
}

int main() {
    std::cout << "SQL Engine -- Demo\n" << std::endl;
    
    Catalog catalog;

    catalog.create_table("users", {
        ColumnSchema("id", DataType::INTEGER, false, true),
        ColumnSchema("name", DataType::TEXT, false),
        ColumnSchema("age", DataType::INTEGER, true),
        ColumnSchema("salary", DataType::REAL, true)
    });
    
    Table* users = catalog.get_table("users");
    
    
    users->insert_row({
        Value::make_integer(1),
        Value::make_text("Alice"),
        Value::make_integer(25),
        Value::make_real(50000.00)
    });
    
    users->insert_row({
        Value::make_integer(2),
        Value::make_text("Bob"),
        Value::make_integer(30),
        Value::make_real(60000.00)
    });
    
    users->insert_row({
        Value::make_integer(3),
        Value::make_text("Charlie"),
        Value::make_integer(35),
        Value::make_real(75000.00)
    });
    
    users->insert_row({
        Value::make_integer(4),
        Value::make_text("Diana"),
        Value::make_integer(28),
        Value::make_null() 
    });
    
    users->insert_row({
        Value::make_integer(5),
        Value::make_text("Eve"),
        Value::make_integer(22),
        Value::make_real(45000.00)
    });
        
    // ========================================================================
    // TEST 1: Display full table (SELECT *)
    // ========================================================================
    print_separator();
    std::cout << "TEST 1: SELECT * FROM users" << std::endl;
    print_separator();
    
    users->display();
    
    // ========================================================================
    // TEST 2: Filter by age > 25
    // ========================================================================
    print_separator();
    std::cout << "TEST 2: SELECT * FROM users WHERE age > 25" << std::endl;
    print_separator();
    
    auto result1 = users->filter_column("age", [](const Value& v) {
        return !v.is_null() && v.as_integer() > 25;
    });
    
    Table::display_results(result1, {"id", "name", "age", "salary"});
    
    // ========================================================================
    // TEST 3: Filter by salary IS NOT NULL
    // ========================================================================
    print_separator();
    std::cout << "TEST 3: SELECT * FROM users WHERE salary IS NOT NULL" << std::endl;
    print_separator();
    
    auto result2 = users->filter_column("salary", [](const Value& v) {
        return !v.is_null();
    });
    
    Table::display_results(result2, {"id", "name", "age", "salary"});
    
    // ========================================================================
    // TEST 4: Select specific columns (projection)
    // ========================================================================
    print_separator();
    std::cout << "TEST 4: SELECT name, age FROM users" << std::endl;
    print_separator();
    
    auto result3 = users->select_columns({"name", "age"});
    
    Table::display_results(result3, {"name", "age"});
    
    // ========================================================================
    // TEST 5: Combined filter + projection
    // ========================================================================
    print_separator();
    std::cout << "TEST 5: SELECT name FROM users WHERE age < 30" << std::endl;
    print_separator();
    
    // First filter
    auto young_users = users->filter_column("age", [](const Value& v) {
        return !v.is_null() && v.as_integer() < 30;
    });
    
    // Then project (manual for now)
    std::vector<std::vector<Value>> names_only;
    auto name_idx = users->find_column_index("name");
    if (name_idx.has_value()) {
        for (const auto& row : young_users) {
            names_only.push_back({row[name_idx.value()]});
        }
    }
    
    Table::display_results(names_only, {"name"});
    
    // ========================================================================
    // TEST 6: Complex filter with multiple conditions
    // ========================================================================
    print_separator();
    std::cout << "TEST 6: SELECT * FROM users WHERE age >= 25 AND salary > 50000" << std::endl;
    print_separator();
    
    auto result4 = users->filter([](const std::vector<Value>& row) {
        // row[2] = age, row[3] = salary
        bool age_ok = !row[2].is_null() && row[2].as_integer() >= 25;
        bool salary_ok = !row[3].is_null() && row[3].as_real() > 50000.0;
        return age_ok && salary_ok;
    });
    
    Table::display_results(result4, {"id", "name", "age", "salary"});
    
    // ========================================================================
    // TEST 7: Get specific row by index
    // ========================================================================
    print_separator();
    std::cout << "TEST 7: Get row at index 2" << std::endl;
    print_separator();
    
    auto row = users->get_row(2);
    if (row.has_value()) {
        std::cout << "Row found:" << std::endl;
        std::cout << "  id: " << row->at(0).to_string() << std::endl;
        std::cout << "  name: " << row->at(1).to_string() << std::endl;
        std::cout << "  age: " << row->at(2).to_string() << std::endl;
        std::cout << "  salary: " << row->at(3).to_string() << std::endl;
    } else {
        std::cout << "Row not found" << std::endl;
    }
    
    // ========================================================================
    // TEST 8: Filter by name (TEXT comparison)
    // ========================================================================
    print_separator();
    std::cout << "TEST 8: SELECT * FROM users WHERE name = 'Bob'" << std::endl;
    print_separator();
    
    auto result5 = users->filter_column("name", [](const Value& v) {
        return !v.is_null() && v.as_text() == "Bob";
    });
    
    Table::display_results(result5, {"id", "name", "age", "salary"});
    
    // ========================================================================
    // TEST 9: Count rows (manual aggregation)
    // ========================================================================
    print_separator();
    std::cout << "TEST 9: SELECT COUNT(*) FROM users WHERE age > 25" << std::endl;
    print_separator();
    
    auto filtered_for_count = users->filter_column("age", [](const Value& v) {
        return !v.is_null() && v.as_integer() > 25;
    });
    
    std::cout << "Count: " << filtered_for_count.size() << " rows" << std::endl;
    
    // ========================================================================
    // TEST 10: Type validation (should fail)
    // ========================================================================
    print_separator();
    std::cout << "TEST 10: Type validation (inserting wrong type)" << std::endl;
    print_separator();
    
    std::cout << "Attempting to insert TEXT into INTEGER column..." << std::endl;
    bool result = users->insert_row({
        Value::make_text("INVALID"),  // Wrong type for id
        Value::make_text("Test"),
        Value::make_integer(99),
        Value::make_null()
    });
    
    if (!result) {
        std::cout << "Type validation works correctly" << std::endl;
    } else {
        std::cout << "Type validation failed" << std::endl;
    }
    
    // ========================================================================
    // TEST 11: Find column index
    // ========================================================================
    print_separator();
    std::cout << "TEST 11: Find column indices" << std::endl;
    print_separator();
    
    auto age_idx = users->find_column_index("age");
    auto invalid_idx = users->find_column_index("invalid_column");
    
    if (age_idx.has_value()) {
        std::cout << "Column 'age' found at index: " << age_idx.value() << std::endl;
    }
    
    if (!invalid_idx.has_value()) {
        std::cout << "Column 'invalid_column' not found (expected)" << std::endl;
    }
    
    
    return 0;
}