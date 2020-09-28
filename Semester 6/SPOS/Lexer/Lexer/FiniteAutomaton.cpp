#include "FiniteAutomaton.h"
#include "Lexer.h"
#include <iostream>

bool FiniteAutomaton::parse(char c)
{
    size_t state = 0;
    while (true)
    {
        switch (state)
        {
            case 0:
            {
                switch (c)
                {
                    case '+':
                    {
                        Token newToken(owner->row, owner->column - 1, TokenType::Plus);
                        owner->tokens.push_back(std::forward<Token>(newToken));
                        return true;
                    }
                    case '-':
                    {
                        Token newToken(owner->row, owner->column - 1, TokenType::Minus);
                        owner->tokens.push_back(std::forward<Token>(newToken));
                        return true;
                    }
                    case '*':
                    {
                        Token newToken(owner->row, owner->column - 1, TokenType::Multiply);
                        owner->tokens.push_back(std::forward<Token>(newToken));
                        return true;
                    }
                    case '%':
                    {
                        Token newToken(owner->row, owner->column - 1, TokenType::Mod);
                        owner->tokens.push_back(std::forward<Token>(newToken));
                        return true;
                    }
                    case '=':
                    {
                        Token newToken(owner->row, owner->column - 1, TokenType::Equal);
                        owner->tokens.push_back(std::forward<Token>(newToken));
                        return true;
                    }
                    case '&':
                    {
                        Token newToken(owner->row, owner->column - 1, TokenType::BitAnd);
                        owner->tokens.push_back(std::forward<Token>(newToken));
                        return true;
                    }
                    case '|':
                    {
                        Token newToken(owner->row, owner->column - 1, TokenType::BitOr_Stick);
                        owner->tokens.push_back(std::forward<Token>(newToken));
                        return true;
                    }
                    case '!':
                    {
                        Token newToken(owner->row, owner->column - 1, TokenType::BitOr_Exclamation);
                        owner->tokens.push_back(std::forward<Token>(newToken));
                        return true;
                    }
                    case '~':
                    {
                        Token newToken(owner->row, owner->column - 1, TokenType::BitXor);
                        owner->tokens.push_back(std::forward<Token>(newToken));
                        return true;
                    }
                    case ':':
                    {
                        if (owner->nextChar())
                        {
                            c = owner->c;
                            state = 2;
                        }
                        else
                        {
                            Token newToken(owner->row, owner->column - 1, TokenType::Colon);
                            owner->tokens.push_back(std::forward<Token>(newToken));
                            return true;
                        }
                        break;
                    }
                    case '<':
                    {
                        if (owner->nextChar())
                        {
                            c = owner->c;
                            state = 3;
                        }
                        else
                        {
                            Token newToken(owner->row, owner->column - 1, TokenType::Less);
                            owner->tokens.push_back(std::forward<Token>(newToken));
                            return true;
                        }
                        break;
                    }
                    case '>':
                    {
                        if (owner->nextChar())
                        {
                            c = owner->c;
                            state = 4;
                        }
                        else
                        {
                            Token newToken(owner->row, owner->column - 1, TokenType::More);
                            owner->tokens.push_back(std::forward<Token>(newToken));
                            return true;
                        }
                        break;
                    }
                    default:
                    {
                        state = 1;
                        break;
                    }
                }
                break;
            }
            case 1:
            {
                // there is no symbol determinated in automa
                return false;
            }
            case 2:
            {
                if (c == '=')
                {
                    Token newToken(owner->row, owner->column - 2, TokenType::Assign);
                    owner->tokens.push_back(std::forward<Token>(newToken));
                }
                else
                {
                    owner->prevChar();
                    Token newToken(owner->row, owner->column - 1, TokenType::Colon);
                    owner->tokens.push_back(std::forward<Token>(newToken));
                }
                return true;
            }
            case 3:
            {
                if (c == '>')
                {
                    Token newToken(owner->row, owner->column - 2, TokenType::NotEqual);
                    owner->tokens.push_back(std::forward<Token>(newToken));
                }
                else if (c == '=')
                {
                    Token newToken(owner->row, owner->column - 2, TokenType::EqualLess);
                    owner->tokens.push_back(std::forward<Token>(newToken));
                }
                else if (c == '<')
                {
                    Token newToken(owner->row, owner->column - 2, TokenType::BitLeft);
                    owner->tokens.push_back(std::forward<Token>(newToken));
                }
                else
                {
                    owner->prevChar();
                    Token newToken(owner->row, owner->column - 1, TokenType::Less);
                    owner->tokens.push_back(std::forward<Token>(newToken));
                }
                return true;
            }
            case 4:
            {
                if (c == '>')
                {
                    Token newToken(owner->row, owner->column - 2, TokenType::BitRight);
                    owner->tokens.push_back(std::forward<Token>(newToken));
                }
                else if (c == '=')
                {
                    Token newToken(owner->row, owner->column - 2, TokenType::EqualMore);
                    owner->tokens.push_back(std::forward<Token>(newToken));
                }
                else
                {
                    owner->prevChar();
                    Token newToken(owner->row, owner->column - 1, TokenType::More);
                    owner->tokens.push_back(std::forward<Token>(newToken));
                }
                return true;
            }
            default:
            {
                std::cerr << "error not correct state\n";
                state = 1;
            }
        }
    }
    return false;
}
