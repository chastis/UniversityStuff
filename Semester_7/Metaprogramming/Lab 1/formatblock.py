from tokens import *

BLOCKS = {
    KeyWordType.Create : PunctType.Semicolon, 
    KeyWordType.Select : PunctType.Semicolon,
    KeyWordType.Update : PunctType.Semicolon,
    KeyWordType.Insert : PunctType.Semicolon,
    PunctType.RoundBracket_Open : PunctType.RoundBracket_Close
}

ENUMERAION = {
    KeyWordType.Set : PunctType.Semicolon,
    KeyWordType.Select: KeyWordType.From,
    PunctType.RoundBracket_Open : PunctType.RoundBracket_Close
}

# we suppose that we can insert round_brackets anywhere
CONNECTED_TOKENS = {
    None: [KeyWordType.Create, PunctType.Semicolon],
    None: [KeyWordType.Select, KeyWordType.From, KeyWordType.Where],
    None: [KeyWordType.Update, KeyWordType.Set],
    None: [KeyWordType.Insert, KeyWordType.Into, KeyWordType.Values],
    None: [TokenType.Identifier, KeyWordType.Constraint],
    TokenType.Identifier: [TokenType.VarType, KeyWordType.Not, KeyWordType.Null, TokenType.Value, TokenType.Operations],
    TokenType.Operations: [TokenType.Identifier, TokenType.Value],
    KeyWordType.Not: [KeyWordType.Null, KeyWordType.Exist],
    KeyWordType.Foreign: [KeyWordType.Key, KeyWordType.References, KeyWordType.On],
    KeyWordType.On: [KeyWordType.Delete, KeyWordType.Cascade],
    KeyWordType.Join: [TokenType.Identifier, KeyWordType.On],
    KeyWordType.Case: [KeyWordType.When, KeyWordType.Else, KeyWordType.End],
    KeyWordType.When: [KeyWordType.Then, TokenType.Identifier, TokenType.Value]

}

TOKEN_RULES = [
    [TokenType.Identifier, TokenType.Identifier],
    [KeyWordType.From, TokenType.Identifier],
    [KeyWordType.Select, TokenType.Identifier],
    [KeyWordType.Select, KeyWordType.Star],
    [KeyWordType.Select, KeyWordType.Max],
    [KeyWordType.Where, TokenType.Identifier],
    [KeyWordType.Create, KeyWordType.View],
    [PunctType.RoundBracket_Open, ValuesType.String, PunctType.RoundBracket_Close],
    [PunctType.RoundBracket_Open, ValuesType.Integer, PunctType.RoundBracket_Close],
    [PunctType.RoundBracket_Open, ValuesType.Real, PunctType.RoundBracket_Close],
    [PunctType.RoundBracket_Open, TokenType.Identifier, PunctType.RoundBracket_Close],
    [KeyWordType.Left, KeyWordType.Join],
    [KeyWordType.Outer, KeyWordType.Join],
    [KeyWordType.Left, KeyWordType.Outer],
    [KeyWordType.Inner, KeyWordType.Join],
    [KeyWordType.Natural, KeyWordType.Join],
    [KeyWordType.Group, KeyWordType.By],
    [KeyWordType.Order, KeyWordType.By],
    [KeyWordType.By, TokenType.Identifier],
    [KeyWordType.Having, TokenType.Identifier],
    [KeyWordType.Max, TokenType.Identifier],
    [KeyWordType.Max, KeyWordType.As],
    [KeyWordType.Min, TokenType.Identifier],
    [KeyWordType.Min, KeyWordType.As]
]