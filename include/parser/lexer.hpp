#pragma once

#include "parser/token.hpp"
#include <string>
#include <vector>
namespace sqlengine {

/**
 * Lexer:
 *  - tokenize SQL queries (lexical analyzer)
 *  - detects tokens (no understanding of grammar)
 * 
 * Ex:
 * Input: "SELECT * FROM users WHERE age > 25"
 * Output: [SELECT, *, FROM, IDENTIFIER(users), WHERE, IDENTIFIER(age), >, NUMBER(25)]
 * 
 * Read character one by one, group into token, return vector of token
 */

class Lexer {
public:
    // Constructor: takes SQL query string
    explicit Lexer(std::string input);

    // Tokenize the entire input
    std::vector<Token> tokenize();

private:
    std::string input_;     
    size_t position_;       // current position in input
    char current_char_;   
    
    // Move to next character
    void advance();


};

} // namespace sqlengine