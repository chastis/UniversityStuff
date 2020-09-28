#include "Lexer.h"
#include <iostream>
#include <functional>
#include <iomanip>

Token::Token(size_t row, size_t column, TokenType type, std::string_view symbol)
    : type(type), row(row), column(column), symbol(symbol)
{}

Token::Token(size_t row, size_t column, TokenType type)
    : type(type), row(row), column(column)
{
    symbol = TokenValue[static_cast<size_t>(type)];
}

Lexer::Lexer()
{
    FA.owner = this;
}

void Lexer::parse(const std::string& file)
{
    fin.open(file);

    while (nextChar())
    {
        if (c == ' ' || c == '\t')
        {
            continue;
        }
        if (c == '\n')
        {
            nextLine();
            continue;
        }
        if (c == '{')
        {
            if (nextChar())
            {
                if (c == '$')
                {
                    Token startToken(row, column - 2, TokenType::StartPreprocessorCommand);
                    tokens.push_back(std::forward<Token>(startToken));

                    while (nextChar())
                    {
                        if (c != ' ')
                        {
                            if (c == '\n')
                            {
                                expectedError("}", row, column);
                                break;
                            }
                            if (c == '}')
                            {
                                Token endToken(row, column, TokenType::EndPreprocessorCommand);
                                tokens.push_back(std::forward<Token>(endToken));
                                break;
                            }
                            if (isCorrectIdentifierStart(c))
                            {
                                prevChar();
                                const size_t startColumn = column;
                                const auto nextIdentifierType = getNextIdentifier();
                                if (static_cast<size_t>(nextIdentifierType) < static_cast<size_t>(TokenType::Identifier)
                                    || static_cast<size_t>(nextIdentifierType) > static_cast<size_t>(TokenType::FalseValue)
                                    || static_cast<size_t>(nextIdentifierType) == static_cast<size_t>(TokenType::OneLineComment))
                                {
                                    expectedError("}", row, startColumn);
                                    break;
                                }
                            }
                            else
                            {
                                expectedError("}", row, column);
                                break;
                            }
                        }
                    }
                    continue;
                }
                prevChar();
            }
            getNextComment(TokenType::MultiLineBraceComment, row, column);
            continue;
        }
        if (c == '(')
        {
            if (nextChar())
            {
                if (c == '*')
                {
                    getNextComment(TokenType::MultiLineParenthesesComment, row, column);
                    continue;
                }
                else
                {
                    prevChar();
                }
            }
            Token newToken(row, column - 1, TokenType::ParenthesesL);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (isCorrectIdentifierStart(c))
        {
            prevChar();
            getNextIdentifier();
            continue;
        }
        if (isdigit(c))
        {
            const size_t startColumn = column - 1;
            std::string tokenString(&c);
            bool bMetPeriod = false;
            while (nextChar())
            {
                if (isdigit(c))
                {
                    tokenString+=c;
                    continue;
                }
                if (c == '.')
                {
                    if (!bMetPeriod)
                    {
                        bMetPeriod = true;
                        tokenString+=c;
                        continue;
                    }
                    else
                    {
                        invalidError(".", row, column);
                        break;
                    }
                }
                prevChar();
                break;
            }
            const auto it = symbols.insert(tokenString);
            Token newToken(row, startColumn, bMetPeriod ? TokenType::RealValue : TokenType::IntegerValue, *it.first);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (c == '\'')
        {
            const size_t startColumn = column;
            std::string tokenString;
            while (nextChar())
            {
                if (c == '\n')
                {
                    expectedError("'", row, column);
                    break;
                }
                if (c == '\'')
                    break;
                tokenString += c;
            }

            const auto it = symbols.insert(tokenString);
            Token newToken(row, startColumn, TokenType::StringValue, *it.first);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (c == ';')
        {
            Token newToken(row, column - 1, TokenType::Semicolon);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (c == '.')
        {
            Token newToken(row, column - 1, TokenType::Period);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (c == '[')
        {
            Token newToken(row, column - 1, TokenType::BracketL);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (c == ']')
        {
            Token newToken(row, column - 1, TokenType::BracketR);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (c == ')')
        {
            Token newToken(row, column - 1, TokenType::ParenthesesR);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (c == ',')
        {
            Token newToken(row, column - 1, TokenType::Comma);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (c == '/')
        {
            if (nextChar())
            {
                if (c == '/')
                {
                    getNextComment(TokenType::OneLineComment, row, column);
                    continue;
                }
                else if (c == '*')
                {
                    getNextComment(TokenType::MultiLineSlashComment, row, column);
                    continue;
                }
                else
                {
                    prevChar();
                }
            }
            Token newToken(row, column - 1, TokenType::Divide);
            tokens.push_back(std::forward<Token>(newToken));
            continue;
        }
        if (FA.parse(c))
        {
            continue;
        }
        // We did not find any symbol
        invalidError(&c, row, column);
    }

    fin.close();
}

void Lexer::printTokens(std::ostream& fout)
{
    fout << "------------------Tokens------------------\n";
    for (const auto& token : tokens)
    {
        if (static_cast<size_t>(token.type) >= static_cast<size_t>(TokenType::Identifier) &&
            static_cast<size_t>(token.type) <= static_cast<size_t>(TokenType::MultiLineSlashComment))
        {
            fout << std::setw(16) << TokenValue[static_cast<size_t>(token.type)] << ": " << std::setw(16) << token.symbol << '\n';
        }
        else
        {
            fout << std::setw(16) << TokenValue[static_cast<size_t>(token.type)] << '\n';
        }
    }
    fout << "------------------------------------------\n";
}

void Lexer::printErrorTokens(std::ostream& fout)
{
    fout << "------------Error-Tokens------------------\n";
    for (const auto& token : errorTokens)
    {
        fout << std::setw(24) << token.second << '\n';
    }
    fout << "------------------------------------------\n";
}

bool Lexer::nextChar()
{
    if (fin.eof())
        return false;
    fin.seekg(position++);
    c = fin.peek();
    column++;
    return !fin.eof();
}

bool Lexer::prevChar()
{
    if (position == 0)
        return false;
    fin.seekg(--position);
    c = fin.peek();
    column--;
    return true;
}

bool Lexer::nextLineAndChar()
{
    if (nextLine())
    {
        nextChar();
        return true;
    }
    return false;
}

bool Lexer::nextLine()
{
    if (c == '\n')
    {
        row++;
        column = 0;
        return true;
    }
    return false;
}

bool Lexer::isCorrectIdentifierChar(char inChar)
{
    return isCorrectIdentifierStart(inChar) || std::isdigit(inChar);
}

bool Lexer::isCorrectIdentifierStart(char inChar)
{
    return std::isalpha(inChar) || inChar == '_';
}

TokenType Lexer::isKeyWord(const std::string& tokenString)
{
    for (size_t i = static_cast<size_t>(TokenType::TrueValue); i <= static_cast<size_t>(TokenType::Real); ++i)
    {
        if (TokenValue[i] == tokenString)
        {
            return static_cast<TokenType>(i);
        }
    }
    return TokenType::Identifier;
}

void Lexer::getNextComment(TokenType commentType, size_t startRow, size_t startColumn)
{
    switch (commentType)
    {
    case TokenType::OneLineComment:
    {
        std::string tokenString;
        while (nextChar() && c != '\n')
        {
            tokenString += c;
        }
        const auto it = symbols.insert(tokenString);
        Token newToken(row, column, TokenType::OneLineComment, *it.first);
        tokens.push_back(std::forward<Token>(newToken));
        break;
    }
    case TokenType::MultiLineBraceComment:
    {
        std::string tokenString;
        while (nextChar())
        {
            if (c == '\n')
            {
                tokenString += c;
                nextLineAndChar();
            }
            if (c == '}')
                break;
            tokenString += c;
        }
        const auto it = symbols.insert(tokenString);
        Token newToken(startRow, startColumn, TokenType::MultiLineBraceComment, *it.first);
        tokens.push_back(std::forward<Token>(newToken));
        if (c != '}')
            expectedError("}", row, column);
        break;
    }
    case TokenType::MultiLineSlashComment:
    {
        std::string tokenString;
        while (nextChar())
        {
            if (c == '\n')
            {
                tokenString += c;
                nextLineAndChar();
            }
            if (c == '*')
            {
                if (nextChar())
                {
                    if (c == '/')
                        break;
                    prevChar();
                }
            }
            tokenString += c;
        }
        const auto it = symbols.insert(tokenString);
        Token newToken(startRow, startColumn, TokenType::MultiLineSlashComment, *it.first);
        tokens.push_back(std::forward<Token>(newToken));
        if (c != '/')
            expectedError("*/", row, column);
        break;
    }
    case TokenType::MultiLineParenthesesComment:
    {
        std::string tokenString;
        while (nextChar())
        {
            if (c == '\n')
            {
                tokenString += c;
                nextLineAndChar();
            }
            if (c == '*')
            {
                if (nextChar())
                {
                    if (c == ')')
                        break;
                    prevChar();
                }
            }
            tokenString += c;
        }
        const auto it = symbols.insert(tokenString);
        Token newToken(startRow, startColumn, TokenType::MultiLineParenthesesComment, *it.first);
        tokens.push_back(std::forward<Token>(newToken));
        if (c != ')')
            expectedError("*)", row, column);
        break;
    }
    default:
        std::cerr << "this is not comment, little foolish\n";
    }
}

TokenType Lexer::getNextIdentifier()
{
    const size_t startRow = row;
    const size_t startColumn = column;
    std::string tokenString;
    while (nextChar())
    {
        if (isCorrectIdentifierChar(c))
        {
            tokenString += static_cast<char>(tolower(c));
        }
        else
        {
            prevChar();
            break;
        }
    }
    if (!tokenString.empty())
    {
        const TokenType tokenType = isKeyWord(tokenString);
        if (tokenType != TokenType::Identifier)
        {
            Token newToken(startRow, startColumn, tokenType);
            tokens.push_back(std::forward<Token>(newToken));
            return tokenType;
        }
        else
        {
            const auto it = symbols.insert(tokenString);
            Token newToken(startRow, startColumn, TokenType::Identifier, *it.first);
            tokens.push_back(std::forward<Token>(newToken));
            return TokenType::Identifier;
        }
    }
    return TokenType::Invalid;
}

void Lexer::invalidError(const std::string& text, size_t inRow, size_t inColumn)
{
    std::pair<Token, std::string> error;
    error.second = "Invalid symbol " + text + " at " + std::to_string(inRow) + " " + std::to_string(inColumn);
    error.first = Token(inRow, inColumn, TokenType::Invalid, error.second);
    errorTokens.push_back(std::forward<std::pair<Token, std::string>>(error));
}

void Lexer::expectedError(const std::string& text, size_t inRow, size_t inColumn)
{
    std::pair<Token, std::string> error;
    error.second = "Expected " + text + " at " + std::to_string(inRow) + " " + std::to_string(inColumn);
    error.first = Token(inRow, inColumn, TokenType::Invalid, error.second);
    errorTokens.push_back(std::forward<std::pair<Token, std::string>>(error));
}


