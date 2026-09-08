#include "Lexer.hpp"
#include "LexerError.hpp"

#include <cassert>

int main() {
    {
        rv::Lexer lexer("123abc");

        bool threw = false;

        try {
            lexer.tokenize();
        } catch (const rv::LexerError& error) {
            threw = true;

            assert(error.line() == 1);
            assert(error.column() == 1);
        }

        assert(threw);
    }

    {
        rv::Lexer lexer("1.");

        bool threw = false;

        try {
            lexer.tokenize();
        } catch (const rv::LexerError& error) {
            threw = true;

            assert(error.line() == 1);
            assert(error.column() == 1);
        }

        assert(threw);
    }

    return 0;
}