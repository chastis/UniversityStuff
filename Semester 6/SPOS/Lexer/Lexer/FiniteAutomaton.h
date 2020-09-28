#pragma once

class Lexer;

class FiniteAutomaton
{
    friend class Lexer;
public:
    bool parse(char c);
private:
    Lexer* owner = nullptr;
};