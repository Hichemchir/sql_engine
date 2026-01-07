#include "parser/token.hpp"

namespace sqlengine {

std::string Token::type_to_string() const {
    switch(type) {
        // Keywords
        case TokenType::SELECT: return "SELECT";
        case TokenType::FROM: return "FROM";
        case TokenType::WHERE: return "WHERE";
        case TokenType::INSERT: return "INSERT";
        case TokenType::INTO: return "INTO";
        case TokenType::VALUES: return "VALUES";
        case TokenType::CREATE: return "CREATE";
        case TokenType::TABLE: return "TABLE";
        case TokenType::DROP: return "DROP";
        case TokenType::AND: return "AND";
        case TokenType::OR: return "OR";
        case TokenType::NOT: return "NOT";
        
        // Literals
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::STRING: return "STRING";
        
        // Operators
        case TokenType::ASTERISK: return "*";
        case TokenType::COMMA: return ",";
        case TokenType::SEMICOLON: return ";";
        case TokenType::LEFT_PAREN: return "(";
        case TokenType::RIGHT_PAREN: return ")";
        
        // Comparison operators
        case TokenType::EQUAL: return "=";
        case TokenType::NOT_EQUAL: return "!=";
        case TokenType::LESS_THAN: return "<";
        case TokenType::LESS_EQUAL: return "<=";
        case TokenType::GREATER_THAN: return ">";
        case TokenType::GREATER_EQUAL: return ">=";
        
        // special
        case TokenType::END_OF_FILE: return "EOF";
        case TokenType::UNKNOWN: return "UNKNOWN";
        
        default: return "UNKNOWN";
    }
}

const std::unordered_map<std::string, TokenType>& Token::get_keywords() {
    static const std::unordered_map<std::string, TokenType> keywords = {
            {"SELECT", TokenType::SELECT},
            {"FROM", TokenType::FROM},
            {"WHERE", TokenType::WHERE},
            {"INSERT", TokenType::INSERT},
            {"INTO", TokenType::INTO},
            {"VALUES", TokenType::VALUES},
            {"CREATE", TokenType::CREATE},
            {"TABLE", TokenType::TABLE},
            {"DROP", TokenType::DROP},
            {"AND", TokenType::AND},
            {"OR", TokenType::OR},
            {"NOT", TokenType::NOT}
        };
    return keywords;
}

} // namespace sqlengine