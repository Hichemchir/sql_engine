#include "parser/lexer.hpp"

namespace sqlengine {

void Lexer::advance() {
    position_++;
    if (position_ < input_.length()) {
        current_char_ = input_[position_];
    }
}

char Lexer::peek() const {
    return input_[static_cast<int>(position_) + 1];
}

void Lexer::skip_whitespace() {
    while (current_char_ == ' ') {
        advance();
    }
}

bool Lexer::is_at_end() const {
    return (position_ >= input_.length());
}

} // namespace sqlengine