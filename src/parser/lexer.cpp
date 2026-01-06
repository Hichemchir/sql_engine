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
}

char Lexer::peek() const {
    if ((position_ + 1) < input_.length()) {
        return input_[position_+ 1];
    }
    return '\0'; 
}

void Lexer::skip_whitespace() {
    while (!is_at_end() && current_char_ == ' ') {
        advance();
    }
}

bool Lexer::is_at_end() const {
    return (position_ >= input_.length());
}

// starts with a letter or a number
Token Lexer::read_identifier() {
    std::string word;
    while (std::isalnum(current_char_)) {
        word += current_char_;
        advance();
    }
    if (is_keyword(word)) {
        TokenType token = KEYWORD[word];
        return token;
    }
    return TokenType::UNKNOWN;
}

Token Lexer::read_number() {
    
}

bool Lexer::is_keyword(const std::string& word) const {
    auto it = KEYWORD.find(word);
    if (it != KEYWORD.end()) {
        return true;
    }
    return false;
}

} // namespace sqlengine