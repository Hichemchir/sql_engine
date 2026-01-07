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
    // Read a number / Float
    Token read_number();
    // text in quotes --> "name"
    Token read_string();    
    // Get next single token
    Token get_next_token();

    // check if a string is a SQL keyword
    bool is_keyword(const std::string& word) const;     
    // Convert keyword string to TokenType
    TokenType keyword_to_token_type(const std::string& keyword) const;
 
};

} // namespace sqlengine