from tokens import *

BLOCK_START = [
    KeyWordType.Create, 
    KeyWordType.Select, 
    PunctType.RoundBracket_Open
]

CONNECTED_TOKENS = {
    None: [KeyWordType.Create, PunctType.RoundBracket_Open, PunctType.Semicolon],
    None: [KeyWordType.Select, KeyWordType.From, KeyWordType.Where],
    TokenType.Identifier: [TokenType.Type, KeyWordType.Not, KeyWordType.Null]

}

TOKEN_RULES = [
    [TokenType.Identifier, TokenType.Identifier],
    [KeyWordType.From, TokenType.Identifier],
    [KeyWordType.Select, TokenType.Identifier],
    [KeyWordType.Select, KeyWordType.Star],
    [PunctType.RoundBracket_Open, TokenType.String, PunctType.RoundBracket_Close],
    [PunctType.RoundBracket_Open, TokenType.Integer, PunctType.RoundBracket_Close],
    [PunctType.RoundBracket_Open, TokenType.Real, PunctType.RoundBracket_Close],
    [PunctType.RoundBracket_Open, TokenType.Identifier, PunctType.RoundBracket_Close],
    [KeyWordType.Left, KeyWordType.Join],
    [KeyWordType.Outer, KeyWordType.Join],
    [KeyWordType.Left, KeyWordType.Outer],
    [KeyWordType.Inner, KeyWordType.Join],
    [KeyWordType.Natural, KeyWordType.Join],
    [KeyWordType.Group, KeyWordType.By],
    [KeyWordType.Order, KeyWordType.By],
    [KeyWordType.By, TokenType.Identifier]
]