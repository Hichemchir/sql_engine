#include "parser/lexer.hpp"

namespace sqlengine {

// Constructor
Lexer::Lexer(std::string input)
    : input_(std::move(input)), position_(0) {
        current_char_ = input_.empty() ? '\0' : input_[0];
    }

void Lexer::advance() {
    position_++;
    if (position_ < input_.length()) {
        current_char_ = input_[position_];
    }
    // Else, we are at the end
    current_char_ = '\0';
}

char Lexer::peek() const {
    if ((position_ + 1) < input_.length()) {
        return input_[position_ + 1];
    }
    return '\0'; 
}

void Lexer::skip_whitespace() {
    // Need to detect ' ' but also \n, \t,
    while (!is_at_end() && std::isspace(current_char_)) {
        advance();
    }
}

bool Lexer::is_at_end() const {
    return (position_ >= input_.length());
}

// starts with a letter or a number, "my_table" should work -> include '_'
Token Lexer::read_identifier() {
    std::string word;
    while (!is_at_end()  && (std::isalnum(current_char_) || current_char_ == '_')) {
        word += current_char_;
        advance();
    }
    if (is_keyword(word)) {
        return Token(keyword_to_token_type(word), word);
    }
    return Token(TokenType::IDENTIFIER, word);
}

Token Lexer::read_number() {
    std::string word;
    while (!is_at_end() && (std::isdigit(current_char_) || current_char_ == '.')) {
        word += current_char_;
        advance();
    }
    if (!word.empty()) return Token(TokenType::NUMBER, word);
    return Token(TokenType::NUMBER, word);
}

Token Lexer::read_string() {
    std::string word;
    // pass the first '
    advance();

    while (!is_at_end() || current_char_ == '\'') {
        word += current_char_;
        advance();
    }
    if (is_at_end()) return Token(TokenType::UNKNOWN, word);

    // skip the last '
    advance();
    return Token(TokenType::STRING, word);
}

bool Lexer::is_keyword(const std::string& word) const {
    // convert string to UPPER
    [](auto word) { return std::toupper(word)};

    const auto& keywords = Token::get_keywords();
    auto it = keywords.find(word);
    return it != keywords.end();
}

TokenType Lexer::keyword_to_token_type(const std::string& keyword) const {
    const auto& keywords = Token::get_keywords();
    auto it = keywords.find(keyword);

    if (it != keywords.end()) return keywords[keyword];
    return TokenType::UNKNOWN;
    return is_keyword(keyword) ? keywords[keyword] : TokenType::UNKNOWN;
}

// Ex: SELECT * FROM users --> we are at ' ' after 'T'
Token Lexer::get_next_token() {
    skip_whitespace();
    if (is_at_end()) return Token(TokenType::END_OF_FILE, "");
    
    if (std::isalpha(current_char_) || current_char_ == '_') return read_identifier();
    if (std::isdigit(current_char_)) return read_number();
    if (current_char_ == '*') return Token(TokenType::ASTERISK, "*");
    if ()
}

} // namespace sqlengine