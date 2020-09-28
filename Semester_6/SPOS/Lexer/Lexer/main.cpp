
#include "Lexer.h"
#include <iostream>
#include <fstream>

int main()
{
    Lexer lexer;
    lexer.parse("HelloWorld.pas");

    constexpr bool toFile = true;
    if (toFile)
    {
         std::ofstream fout("Tokens.out");
        lexer.printTokens(fout);
        lexer.printErrorTokens(fout);
        fout.close();
    }
    else
    {
        lexer.printTokens(std::cout);
        lexer.printErrorTokens(std::cout);
    }
    
    return 0;
}