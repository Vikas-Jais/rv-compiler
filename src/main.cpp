
#include "Lexer.hpp"
#include "LexerError.hpp"

#include <iostream>
#include <string>

int main() {
    const std::string source = R"(
fn calculate(a, b) {
    let x = 25;
    let y = 3.14;

    // Calculate a result
    if x >= 10 && y != 0 {
        return x + y * 2;
    }

    return 0;
}
)";

    try {
        rv::Lexer lexer(source);
        const auto tokens = lexer.tokenize();

        for (const auto& token : tokens) {
            std::cout
                << "Line " << token.line
                << ", Column " << token.column
                << " | Kind: "
                << static_cast<int>(token.kind)
                << " | Lexeme: \""
                << token.lexeme
                << "\"\n";
        }
    }
    catch (const rv::LexerError& error) {
        std::cerr
            << "Lexer error at line " << error.line()
            << ", column " << error.column()
            << ": " << error.what() << '\n';

        return 1;
    }

    return 0;
}
