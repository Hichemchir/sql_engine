#include <iostream>
#include <string>
#include "storage/table.hpp"

int main() {
    std::cout << "Minimal SQL engine" << std::endl;
    Table users;
    users.name = "users";
    users.columns = {"name", "age"};

    users.add_line({"Alice", "25"});
    users.add_line({"Bob", "30"});
    
    users.display();
    return 0;
}