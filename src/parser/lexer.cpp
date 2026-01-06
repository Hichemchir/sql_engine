#include "parser/lexer.hpp"

namespace sqlengine {

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
    return '/0'; 
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
    while (std::isalnum(current_char_))

}

} // namespace sqlengine