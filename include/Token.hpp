#pragma once

#include <cstddef>
#include <string>

namespace rv {

enum class TokenKind {
    // Keywords
    Fn,
    Let,
    If,
    Else,
    While,
    Return,
    True,
    False,

    // Identifiers and literals
    Identifier,
    IntegerLiteral,
    FloatLiteral,
    StringLiteral,

    // Operators
    Plus,
    Minus,
    Star,
    Slash,
    Percent,

    Equal,
    EqualEqual,
    Bang,
    BangEqual,

    Less,
    LessEqual,
    Greater,
    GreaterEqual,

    AndAnd,
    OrOr,

    // Delimiters
    LParen,
    RParen,
    LBrace,
    RBrace,
    LBracket,
    RBracket,

    Comma,
    Semicolon,
    Colon,

    // Special
    Eof
};

struct Token {
    TokenKind kind;
    std::string lexeme;
    std::size_t line;
    std::size_t column;
};

} // namespace rv