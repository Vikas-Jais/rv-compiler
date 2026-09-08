#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>

namespace rv {

class LexerError : public std::runtime_error {
public:
    LexerError(
        std::string message,
        std::size_t line,
        std::size_t column
    );

    std::size_t line() const noexcept;
    std::size_t column() const noexcept;

private:
    std::size_t line_;
    std::size_t column_;
};

} // namespace rv