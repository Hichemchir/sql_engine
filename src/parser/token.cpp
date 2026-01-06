#include <parser/token.hpp>
#include <string>

std::string Token::type_to_string() const {
    switch(type) {
        case TokenType::SELECT: return "SELECT";
        case TokenType::FROM: return "FROM";
        case TokenType::WHERE: return "WHERE";
        case TokenType::INSERT: return "INSERT";
        case TokenType::INTO: return "INTO";
        
    }
	return "";
}