from tokens import *

BLOCKS = {
    KeyWordType.Create : [PunctType.Semicolon], 
    KeyWordType.Select : [PunctType.Semicolon],
    KeyWordType.Update : [PunctType.Semicolon],
    KeyWordType.Insert : [PunctType.Semicolon],
    PunctType.RoundBracket_Open : [PunctType.RoundBracket_Close],
}

ENUMERAION = {
    KeyWordType.Set : PunctType.Semicolon,
    KeyWordType.Select: KeyWordType.From,
    KeyWordType.From: KeyWordType.Where,
    PunctType.RoundBracket_Open : PunctType.RoundBracket_Close
}

ENUMERAION_ENDING_SKIP = [KeyWordType.Select, PunctType.RoundBracket_Open, KeyWordType.From]

# we suppose that we can insert round_brackets anywhere
CONNECTED_TOKENS = {
    KeyWordType.Create: [TokenType.Identifier],
    KeyWordType.Select: [TokenType.Identifier],
    KeyWordType.Update: [TokenType.Identifier],
    KeyWordType.Insert: [TokenType.Identifier],
    PunctType.RoundBracket_Open: [TokenType.Identifier, TokenType.Value],
    TokenType.Identifier: [TokenType.VarType, KeyWordType.Not, KeyWordType.Null, TokenType.Value, TokenType.Operations, KeyWordType.Constraint],
    TokenType.Operations: [TokenType.Identifier, TokenType.Value],
    KeyWordType.Not: [KeyWordType.Null, KeyWordType.Exist],
    KeyWordType.Foreign: [KeyWordType.Key, KeyWordType.References, KeyWordType.On],
    KeyWordType.Primary: [KeyWordType.Key, KeyWordType.References, KeyWordType.On],
    KeyWordType.On: [KeyWordType.Delete, KeyWordType.Cascade],
    KeyWordType.Join: [TokenType.Identifier, KeyWordType.On],
    KeyWordType.Case: [KeyWordType.When, KeyWordType.Else, KeyWordType.End],
    KeyWordType.When: [KeyWordType.Then, TokenType.Identifier, TokenType.Value],
    KeyWordType.Constraint: [KeyWordType.Foreign, KeyWordType.Check, KeyWordType.Primary]
}

PSEUDONONNECTED_TOKENS = {
    PunctType.RoundBracket_Open: [PunctType.RoundBracket_Close]
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