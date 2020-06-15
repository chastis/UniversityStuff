
#include "Lexer.h"
#include <iostream>

int main()
{
    Lexer lexer;
    lexer.parse("HelloWorld.pas");
    lexer.printTokens(std::cout);
    lexer.printErrorTokens(std::cout);
    return 0;
}