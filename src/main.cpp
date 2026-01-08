#include <iostream>
#include <string>
#include "storage/table.hpp"
#include "storage/catalog.hpp"
#include "common/types.hpp"
#include "storage/column_schema.hpp"
#include "parser/token.hpp"
#include "parser/lexer.hpp"

using namespace sqlengine;

void print_separator() {
    std::cout << "\n" << std::string(80, '=') << "\n" << std::endl;
}

int main() {
    std::cout << "SQL Engine -- Demo\n" << std::endl;

    std::string sql = "SELECT * FROM users WHERE age > 25";

    Lexer lexer(sql);
    auto tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << token.type_to_string() << " = \"" << token.value << "\"" << std::endl;
    }
    
    
    return 0;
}