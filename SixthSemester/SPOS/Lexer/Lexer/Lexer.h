#pragma once

#include "TokenType.h"
#include <string>
#include <string_view>
#include <set>
#include <vector>
#include <fstream>

struct Token
{
    Token() = default;
    Token(size_t row, size_t column, TokenType type, std::string_view symbol);
    Token(size_t row, size_t column, TokenType type);
    TokenType type = TokenType::Invalid;
    size_t row = 0;
    size_t column = 0;
    std::string_view symbol;
};

class Lexer
{
public:
    void parse(const std::string& file);
    void printTokens(std::ostream& fout);
    void printErrorTokens(std::ostream& fout);

private:
    bool nextChar();
    bool prevChar();
    bool nextLineAndChar();
    bool nextLine();

    static bool isCorrectIdentifierChar(char inChar);
    static bool isCorrectIdentifierStart(char inChar);
    static TokenType isDefaultToken(const std::string& tokenString);

    void getNextComment(TokenType commentType, size_t startRow, size_t startColumn);
    TokenType getNextIdentifier();

    void invalidError(const std::string& text, size_t inRow, size_t inColumn);
    void expectedError(const std::string& text, size_t inRow, size_t inColumn);

    std::set<std::string> symbols;
    std::vector<Token> tokens;
    std::vector<std::pair<Token, std::string>> errorTokens;
    std::ifstream fin;

    char c = ' ';
    size_t position = 0;
    size_t row = 0;
    size_t column = 0;
    bool openedComment = false;
};
