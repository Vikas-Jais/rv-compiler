#include "LexerError.hpp"

#include <utility>

namespace rv {

LexerError::LexerError(
    std::string message,
    std::size_t line,
    std::size_t column
)
    : std::runtime_error(std::move(message)),
      line_(line),
      column_(column) {
}

std::size_t LexerError::line() const noexcept {
    return line_;
}

std::size_t LexerError::column() const noexcept {
    return column_;
}

} // namespace rv