from tokens import *

BLOCKS = {
    KeyWordType.Create : [PunctType.Semicolon], 
    KeyWordType.Select : [PunctType.Semicolon],
    KeyWordType.Update : [PunctType.Semicolon],
    KeyWordType.Insert : [PunctType.Semicolon],
    KeyWordType.Delete : [PunctType.Semicolon, KeyWordType.Cascade],
    PunctType.RoundBracket_Open : [PunctType.RoundBracket_Close],
}

ENUMERAION = {
    KeyWordType.Set : PunctType.Semicolon,
    KeyWordType.Select: KeyWordType.From,
    KeyWordType.From: KeyWordType.Where,
    PunctType.RoundBracket_Open : PunctType.RoundBracket_Close
}

ENUMERAION_ENDING_SKIP = [KeyWordType.Select, KeyWordType.From] # , PunctType.RoundBracket_Open ??

# we suppose that we can insert round_brackets anywhere
CONNECTED_TOKENS = {
    KeyWordType.Create: [KeyWordType.Table, TokenType.Identifier],
    KeyWordType.Select: [TokenType.Identifier, KeyWordType.Max, KeyWordType.Min, KeyWordType.Case],
    KeyWordType.Update: [TokenType.Identifier],
    KeyWordType.Insert: [TokenType.Identifier, KeyWordType.Into , KeyWordType.Values, PunctType.RoundBracket_Open],
    PunctType.RoundBracket_Open: [TokenType.Identifier, TokenType.Value, KeyWordType.Constraint, PunctType.Coma, KeyWordType.Primary, KeyWordType.Key],
    TokenType.Identifier: [TokenType.VarType, KeyWordType.Not, KeyWordType.Null, 
                            TokenType.Value, TokenType.Operations, KeyWordType.Constraint,
                            KeyWordType.As],
    TokenType.Operations: [TokenType.Identifier, TokenType.Value],
    KeyWordType.Not: [KeyWordType.Null, KeyWordType.Exist],
    KeyWordType.Foreign: [KeyWordType.Key, KeyWordType.References, KeyWordType.On],
    KeyWordType.Primary: [KeyWordType.Key, KeyWordType.References, KeyWordType.On],
    KeyWordType.On: [KeyWordType.Delete, KeyWordType.Cascade],
    KeyWordType.Join: [TokenType.Identifier, KeyWordType.On],
    KeyWordType.Case: [KeyWordType.When, KeyWordType.Else, KeyWordType.End],
    KeyWordType.When: [KeyWordType.Then, TokenType.Identifier, TokenType.Value],
    KeyWordType.As: [TokenType.Identifier],
    KeyWordType.Constraint: [KeyWordType.Foreign, KeyWordType.Check, KeyWordType.Primary],
    KeyWordType.Max: [KeyWordType.As],
    KeyWordType.Min: [KeyWordType.As],
    KeyWordType.From: [KeyWordType.Natural, KeyWordType.Join, KeyWordType.Left, KeyWordType.Inner, KeyWordType.Outer, KeyWordType.Cross]
}

PSEUDONONNECTED_TOKENS = {
    PunctType.RoundBracket_Open: [PunctType.RoundBracket_Close],
    TokenType.Identifier: [TokenType.Identifier]
}

DEVIDED_TOKENS = [
    KeyWordType.Create,
    KeyWordType.Select,
    KeyWordType.Update,
    KeyWordType.Insert,
    KeyWordType.Delete
]

ALIGNED_TOKENS_DEVIDERS = [
    KeyWordType.From,
    KeyWordType.Where
]

ALIGNED_TOKENS = [
    ([[TokenType.VarType]], [0]),
    ([[KeyWordType.Join], [TokenType.Identifier]], [1]),
    ([[SpecialType.Optional, -1, KeyWordType.Not], [KeyWordType.Null]], [0, 1]),
    ([[SpecialType.Optional, -1, TokenType.Identifier], [SpecialType.Optional, 0, PunctType.Dot], [TokenType.Identifier], [OperationType.Eq]], [0, 2]),
    ([[OperationType.Eq]], [0])
    
]

TOKEN_RULES = [
    [TokenType.Identifier, TokenType.Identifier],
    [KeyWordType.From, TokenType.Identifier],
    [KeyWordType.Select, TokenType.Identifier],
    [KeyWordType.Select, KeyWordType.Star],
    [KeyWordType.Select, KeyWordType.Max],
    [KeyWordType.Where, TokenType.Identifier],
    [KeyWordType.Create, KeyWordType.View],
   # [PunctType.RoundBracket_Open, ValuesType.String, PunctType.RoundBracket_Close],
    [PunctType.RoundBracket_Open, ValuesType.Integer, PunctType.RoundBracket_Close],
    [PunctType.RoundBracket_Open, ValuesType.Real, PunctType.RoundBracket_Close],
    [KeyWordType.Left, KeyWordType.Join],
    [KeyWordType.Outer, KeyWordType.Join],
    [KeyWordType.Left, KeyWordType.Outer],
    [KeyWordType.Inner, KeyWordType.Join],
    [KeyWordType.Natural, KeyWordType.Join],
    [KeyWordType.Cross, KeyWordType.Join],
    [KeyWordType.Group, KeyWordType.By],
    [KeyWordType.Order, KeyWordType.By],
    [KeyWordType.By, TokenType.Identifier],
    [KeyWordType.Having, TokenType.Identifier],
    [KeyWordType.Max, TokenType.Identifier],
    [KeyWordType.Max, KeyWordType.As],
    [KeyWordType.Min, TokenType.Identifier],
    [KeyWordType.Min, KeyWordType.As],
    [KeyWordType.Not, KeyWordType.Null],
    [KeyWordType.Not, KeyWordType.In]
]

DEVIDED_TOKEN_RULES = [
    [KeyWordType.Create, TokenType.Identifier, PunctType.RoundBracket_Open]
]