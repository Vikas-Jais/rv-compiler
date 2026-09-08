#include "Lexer.hpp"
#include "LexerError.hpp"

#include <utility>

namespace rv {

Lexer::Lexer(std::string source)
    : source_(std::move(source)) {
}

//Helper functions

bool Lexer::isAtEnd() const {
    return current_ >= source_.size();
}

char Lexer::advance() {
    char character = source_[current_];
    ++current_;
    if (character == '\n') {
        ++line_;
        column_ = 1;
    } else {
        ++column_;
    }
    return character;
}

char Lexer::peek() const {
    if (isAtEnd()) {
        return '\0';
    }

    return source_[current_];
}

char Lexer::peekNext() const {
    if (current_ + 1 >= source_.size()) {
        return '\0';
    }

    return source_[current_ + 1];
}

bool Lexer::match(char expected) {
    if (isAtEnd()) {
        return false;
    }

    if (source_[current_] != expected) {
        return false;
    }

    advance();
    return true;
}

//------------------------------------------------------------------------ */

// Token scanning functions

Token Lexer::scanIdentifier() {
    const std::size_t start = current_;
    const std::size_t startColumn = column_;

    while (true) {
        const char c = peek();

        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') ||
            c == '_') {
            advance();
        } else {
            break;
        }
    }

    const std::string lexeme =
        source_.substr(start, current_ - start);

    TokenKind kind = TokenKind::Identifier;

    if (lexeme == "fn") {
        kind = TokenKind::Fn;
    } else if (lexeme == "let") {
        kind = TokenKind::Let;
    } else if (lexeme == "if") {
        kind = TokenKind::If;
    } else if (lexeme == "else") {
        kind = TokenKind::Else;
    } else if (lexeme == "while") {
        kind = TokenKind::While;
    } else if (lexeme == "return") {
        kind = TokenKind::Return;
    } else if (lexeme == "true") {
        kind = TokenKind::True;
    } else if (lexeme == "false") {
        kind = TokenKind::False;
    }

    return Token{
        kind,
        lexeme,
        line_,
        startColumn
    };
}

Token Lexer::scanNumber() {
    const std::size_t start = current_;
    const std::size_t startColumn = column_;
    const std::size_t startLine = line_;

    // Consume the integer part.
    while (peek() >= '0' && peek() <= '9') {
        advance();
    }

    if ((peek() >= 'a' && peek() <= 'z') ||
        (peek() >= 'A' && peek() <= 'Z') ||
        peek() == '_') {
        throw LexerError(
            "invalid numeric literal",
            startLine,
            startColumn
        );
    }

    bool isFloat = false;

    // Check for a decimal point followed by a digit.
    if (peek() == '.' &&
        peekNext() >= '0' &&
        peekNext() <= '9') {
        isFloat = true;
        advance(); // Consume '.'

        while (peek() >= '0' && peek() <= '9') {
            advance();
        }
    }

    if (peek() == '.') {
        throw LexerError(
            "invalid numeric literal",
            startLine,
            startColumn
        );
    }

    const std::string lexeme =
        source_.substr(start, current_ - start);

    return Token{
        isFloat ? TokenKind::FloatLiteral
                : TokenKind::IntegerLiteral,
        lexeme,
        startLine,
        startColumn
    };
}

//------------------------------------------------------------------------ */

// Main tokenization function

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        const char c = peek();

        // Skip whitespace.
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            advance();
            continue;
        }

        // Identifier or keyword.
        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_') {
            tokens.push_back(scanIdentifier());
            continue;
        }

        // Number literal.
        if (c >= '0' && c <= '9') {
            tokens.push_back(scanNumber());
            continue;
        }

        // Unknown character for now.
        advance();
    }

    tokens.push_back(Token{
        TokenKind::Eof,
        "",
        line_,
        column_
    });

    return tokens;
}

} // namespace rv