#include "parser/lexer.hpp"

namespace sqlengine {

void Lexer::advance() {
    position_++;
    if (position_ < input_.size()) {
        current_char_ = input_[position_];
    }
}

} // namespace sqlengine