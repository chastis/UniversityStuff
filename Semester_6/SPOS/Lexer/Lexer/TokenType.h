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
    IntegerValue,
    RealValue,


    // Comments
    OneLineComment, // //
    MultiLineBraceComment, // { }
    MultiLineParenthesesComment, // (* *)
    MultiLineSlashComment, // /* */

    // boolean
    TrueValue,
    FalseValue,

    // key words
    Var,
    Const, 
    Begin,
    End,
    Program,
    If,
    And,
    Or,
    Not,
    Then,
    Else,
    While,
    Do,
    For,

    // Variables Types
    String,
    Integer,
    Real,

    // Operators
    Assign,
    Plus,
    Minus,
    Multiply,
    Divide,
    Mod,
    Equal,
    NotEqual,
    More,
    Less,
    EqualMore,
    EqualLess,
    BitAnd,
    BitOr_Stick,
    BitOr_Exclamation,
    BitXor,
    BitLeft,
    BitRight,



    // Punctuation
    Semicolon,
    Period,
    Comma,
    Colon,
    ParenthesesL,
    ParenthesesR,
    BracketL,
    BracketR,

    // Preprocessor
    StartPreprocessorCommand, // {$
    EndPreprocessorCommand, // }

    Count
};

const std::string TokenValue[static_cast<size_t>(TokenType::Count)] = 
{
    "invalid",
    "identifier",
    "string value",
    "integer value",
    "real value",
    "one line comment",
    "multi line brace comment",
    "multi line parentheses comment",
    "multi line slash comment",
    "true",
    "false",
    "var",
    "const",
    "begin",
    "end",
    "program",
    "if",
    "and",
    "or",
    "not",
    "then",
    "else",
    "while",
    "do",
    "for",
    "string",
    "integer",
    "real",

    ":=",
    "+",
    "-",
    "*",
    "/",
    "%",
    "=",
    "<>",
    ">",
    "<",
    ">=",
    "<=",
    "&",
    "|",
    "!",
    "~",
    "<<",
    ">>",

    ";",
    ".",
    ",",
    ":",
    "(",
    ")",
    "[",
    "]",
    "{$",
    "}"
};