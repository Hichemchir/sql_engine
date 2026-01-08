#include <gtest/gtest.h>
#include "parser/lexer.hpp"

using namespace sqlengine;

// Test 1
TEST(LexerTest, EmptyString) {
    Lexer lexer("");
    auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::END_OF_FILE);
}

// Test 2
TEST(LexerTest, selectAll) {
    std::string sql = "SELECT * FROM users";
    Lexer lexer(sql);
    auto tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << token.type_to_string() << std::endl;
    }

    ASSERT_EQ(tokens.size(), 5);
}