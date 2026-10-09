
#include "Lexer.hpp"
#include "LexerError.hpp"

#include <cassert>
#include <string>

int main() {
    // 1. Keywords, identifiers, numbers and operators
    {
        rv::Lexer lexer(
            "fn calculate let x = 25 + 3.14 * 2 == 8 && true"
        );

        const auto tokens = lexer.tokenize();

        assert(tokens[0].kind == rv::TokenKind::Fn);
        assert(tokens[1].kind == rv::TokenKind::Identifier);
        assert(tokens[2].kind == rv::TokenKind::Let);
        assert(tokens[4].kind == rv::TokenKind::Equal);
        assert(tokens[5].kind == rv::TokenKind::IntegerLiteral);
        assert(tokens[6].kind == rv::TokenKind::Plus);
        assert(tokens[7].kind == rv::TokenKind::FloatLiteral);
        assert(tokens[8].kind == rv::TokenKind::Star);
        assert(tokens[10].kind == rv::TokenKind::EqualEqual);
        assert(tokens[12].kind == rv::TokenKind::AndAnd);
        assert(tokens[13].kind == rv::TokenKind::True);
        assert(tokens.back().kind == rv::TokenKind::Eof);
    }

    // 2. All delimiters
    {
        rv::Lexer lexer("( ) { } [ ] , ; :");
        const auto tokens = lexer.tokenize();

        assert(tokens.size() == 10);
        assert(tokens[0].kind == rv::TokenKind::LParen);
        assert(tokens[1].kind == rv::TokenKind::RParen);
        assert(tokens[2].kind == rv::TokenKind::LBrace);
        assert(tokens[3].kind == rv::TokenKind::RBrace);
        assert(tokens[4].kind == rv::TokenKind::LBracket);
        assert(tokens[5].kind == rv::TokenKind::RBracket);
        assert(tokens[6].kind == rv::TokenKind::Comma);
        assert(tokens[7].kind == rv::TokenKind::Semicolon);
        assert(tokens[8].kind == rv::TokenKind::Colon);
        assert(tokens[9].kind == rv::TokenKind::Eof);
    }

    // 3. Comments are skipped
    {
        rv::Lexer lexer("let x = 10; // comment\nlet y = 20;");
        const auto tokens = lexer.tokenize();

        assert(tokens.size() == 11);
        assert(tokens[0].kind == rv::TokenKind::Let);
        assert(tokens[5].kind == rv::TokenKind::Let);
        assert(tokens.back().kind == rv::TokenKind::Eof);
    }

    // 4. Strings and escapes
    {
        rv::Lexer lexer(R"("hello" "say \"Hi\"" "line\nbreak")");
        const auto tokens = lexer.tokenize();

        assert(tokens.size() == 4);
        assert(tokens[0].kind == rv::TokenKind::StringLiteral);
        assert(tokens[0].lexeme == R"("hello")");
        assert(tokens[1].kind == rv::TokenKind::StringLiteral);
        assert(tokens[2].kind == rv::TokenKind::StringLiteral);
        assert(tokens.back().kind == rv::TokenKind::Eof);
    }

    // 5. Invalid numeric literal
    {
        bool errorThrown = false;

        try {
            rv::Lexer lexer("123abc");
            lexer.tokenize();
        }
        catch (const rv::LexerError&) {
            errorThrown = true;
        }

        assert(errorThrown);
    }

    // 6. Invalid escape sequence
    {
        bool errorThrown = false;

        try {
            rv::Lexer lexer(R"("hello\q")");
            lexer.tokenize();
        }
        catch (const rv::LexerError&) {
            errorThrown = true;
        }

        assert(errorThrown);
    }

    // 7. Unterminated string
    {
        bool errorThrown = false;

        try {
            rv::Lexer lexer(R"("hello)");
            lexer.tokenize();
        }
        catch (const rv::LexerError&) {
            errorThrown = true;
        }

        assert(errorThrown);
    }

    // 8. Invalid single &
    {
        bool errorThrown = false;

        try {
            rv::Lexer lexer("&");
            lexer.tokenize();
        }
        catch (const rv::LexerError&) {
            errorThrown = true;
        }

        assert(errorThrown);
    }

    // 9. Invalid single |
    {
        bool errorThrown = false;

        try {
            rv::Lexer lexer("|");
            lexer.tokenize();
        }
        catch (const rv::LexerError&) {
            errorThrown = true;
        }

        assert(errorThrown);
    }

    return 0;
}
