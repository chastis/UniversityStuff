#pragma once

#include <string>

enum class TokenType
{
    // Error
    Invalid,

    // Common
    Identifier,

    // Values
    StringValue,

    // Comments
    OneLineComment, // //
    MultiLineBraceComment, // { }
    MultiLineParenthesesComment, // (* *)
    MultiLineSlashComment, // /* */

    // key words
    Var, // var
    Const, // const
    Begin,
    End,
    Program,

    // Variables Types
    Integer, // Integer

    // Punctuation
    Semicolon,
    Period,

    // Preprocessor
    StartPreprocessorCommand, // {$
    EndPreprocessorCommand, // }

    Count
};

const std::string TokenValue[static_cast<size_t>(TokenType::Count)] = 
{
    "Invalid",
    "Identifier",
    "String value",
    "One line comment",
    "Multi line brace comment",
    "Multi line parentheses comment",
    "Multi line slash comment",
    "var",
    "const",
    "begin",
    "end",
    "program",
    "Integer",
    ";",
    ".",
    "{$",
    "}"
};