#pragma once
#include <string>
#include <unordered_map>

namespace sqlengine {

// Token types for SQL parser

enum class TokenType {
    // SQL keywords
    SELECT,
    FROM,
    WHERE,
    INSERT,
    INTO,
    VALUES,
    CREATE,
    TABLE,
    DROP,
    AND,
    OR,
    NOT,

    // Literals
    IDENTIFIER, // table names & col_names (ex: "users")
    NUMBER,     // int & float
    STRING,     // text in quotes (ex: "Hichem")

    // Operators
    ASTERISK,   // *
    COMMA,
    SEMICOLON,
    LEFT_PAREN,
    RIGHT_PAREN,

    // Comparison operators
    EQUAL,          // =
    NOT_EQUAL,      // !=
    LESS_THAN,      // <
    LESS_EQUAL,     // <=
    GREATER_THAN,   // >
    GREATER_EQUAL,  // >=

    // special
    END_OF_FILE,
    UNKNOWN     // invalid token
};

/**
 * ex of Token struct: 
 *  Token{TokenType::SELECT, "SELECT"}
 *  Token{TokenType::NUMBER, "42"}
 */

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, std::string v) 
        : type(t), value(std::move(v)) {}
    
    // helper method to convert to string
    std::string type_to_string() const;

    // Static keyword MAP for lexer
    static const std::unordered_map<std::string, TokenType>& KEYWORD;
};

} // namespace sqlengine