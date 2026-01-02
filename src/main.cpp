#include <iostream>
#include <string>
#include "storage/table.hpp"

int main() {
    std::cout << "Minimal SQL engine\n" << std::endl;
    
    Table users("users", {"name", "age"});

    users.insert_row({"Alice", "25"});
    users.insert_row({"Bob", "30"});
    users.insert_row({"Charlie", "35"});

    users.display();
    return 0;
}