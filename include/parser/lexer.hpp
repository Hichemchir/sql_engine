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
    // current position in input    
    size_t position_;       
    char current_char_;   
    
    // Move to next character
    void advance();

    // Look at next character without advancing
    char peek() const;

    // skip ' ' characters
    void skip_whitespace();

    // check if current position is at the end
    bool is_at_end() const;

    // Read keywords
    Token read_identifier();
    Token read_number();
    Token read_string();    // text in quotes --> "name"

    Token get_next_token();

    bool is_keyword(const std::string& word) const;     // check if a string is a SQL keyword

    TokenType keyword_to_token_type(const std::string& keyword) const;
 
};

} // namespace sqlengine