#pragma once

#include "Token.hpp"

#include <string>
#include <vector>

namespace rv {

class Lexer {
public:
    explicit Lexer(std::string source);

    std::vector<Token> tokenize();

private:

    Token makeToken(
        TokenKind kind,
        std::size_t start,
        std::size_t startLine,
        std::size_t startColumn
    );

    char advance();
    bool isAtEnd() const;
    char peek() const;
    char peekNext() const;
    bool match(char expected);

    Token scanIdentifier();
    Token scanNumber();
    Token scanOperator();
    Token scanDelimiter();
    Token scanString();

    std::string source_;
    std::size_t current_ = 0;
    std::size_t line_ = 1;
    std::size_t column_ = 1;
};

} // namespace rv