from enum import Enum

class TokenType(Enum):
    Invalid = 0
    Identifier = 1
    Value = 2
    Comment = 3
    KeyWord = 4
    VarType = 5
    Punctuaition = 6
    Spaces = 7
    Operations = 8
    Other = 999

class ValuesType(Enum):
    String = 0
    Integer = 1
    Real = 2

class IdentifierType(Enum):
    Default = 0
    Quoted = 1
    AliasDefault = 2
    AliasQuoted = 3

class KeyWordType(Enum):
    Create = 0
    Table = 1
    Select = 2
    From = 3
    Where = 4
    Group = 5
    By = 6
    Having = 7
    Order = 8
    Desc = 9
    As = 10
    Not = 11
    Null = 12
    Star = 13
    Left = 14
    Outer = 15
    Join = 16
    Natural = 17
    Inner = 18
    On = 19
    Using = 20
    Cross = 21
    Is = 22
    Foreign = 23
    Key = 24
    View = 25
    References = 26
    Delete = 27
    Cascade = 28
    Constraint = 29
    Unique = 30
    Case = 31
    Else = 32
    Then = 33
    Distinct = 34
    Primary = 35
    Exist = 36
    Insert = 37
    Into = 38
    Values = 39
    Update = 40
    Set = 41
    Max = 42
    Min = 43
    When = 44
    End = 45

class VarTypeType(Enum):
    Int = 0,
    Varchar = 1
    Char = 2
    Decimal = 3
    Integer = 4

class PunctType(Enum):
    Dot = 0,
    Coma = 1,
    RoundBracket_Open = 2,
    RoundBracket_Close = 3,
    Semicolon = 4,
    Quotes = 14,
    SingleQuotes = 15,
    DoubleQuotes = 16

class OperationType(Enum):
    More = 5,
    Less = 6,
    Eq = 7,
    LessEq = 8,
    MoreEq = 9,
    NotEq = 10,
    Plus = 11,
    Minus = 12,
    Devide = 13

class CommentType(Enum):
    MultiComment_Open = 0,
    MultiComment_Close = 1,
    MultiComment = 2, # for specific token
    SingleComment = 3

class SpacesType(Enum):
    Space = 0,
    Sym_n = 1,
    Sym_t = 2

TOKEN_DICT = {
    TokenType.KeyWord: {
        KeyWordType.Create            : 'create',
        KeyWordType.Table             : 'table',
        KeyWordType.Select            : 'select',
        KeyWordType.From              : 'from',
        KeyWordType.Where             : 'where',
        KeyWordType.Group             : 'group',
        KeyWordType.By                : 'by',
        KeyWordType.Having            : 'having',
        KeyWordType.Order             : 'order',
        KeyWordType.Desc              : 'desc',
        KeyWordType.As                : 'as',
        KeyWordType.Not               : 'not',
        KeyWordType.Null              : 'null',
        KeyWordType.Star              : '*',
        KeyWordType.Left              : "left",
        KeyWordType.Outer             : "outer",
        KeyWordType.Join              : "join",
        KeyWordType.Natural           : "natural",
        KeyWordType.Inner             : "inner",
        KeyWordType.On                : "on",
        KeyWordType.Using             : "using",
        KeyWordType.Cross             : "cross",
        KeyWordType.Is                : "is",
        KeyWordType.Foreign           : "foreign",
        KeyWordType.Key               : "key",
        KeyWordType.View              : "view",
        KeyWordType.References        : "references",
        KeyWordType.Delete            : "delete",
        KeyWordType.Cascade           : "cascade",
        KeyWordType.Constraint        : "constraint",
        KeyWordType.Unique            : "unique",
        KeyWordType.Case              : "case",
        KeyWordType.Else              : "else",
        KeyWordType.Then              : "then",
        KeyWordType.Distinct          : "distinct",
        KeyWordType.Primary           : "primary",
        KeyWordType.Exist             : "exist",
        KeyWordType.Insert            : "insert",
        KeyWordType.Into              : "into",
        KeyWordType.Values            : "values",
        KeyWordType.Update            : "update",
        KeyWordType.Set               : "set",
        KeyWordType.Max               : "max",
        KeyWordType.Min               : "min",
        KeyWordType.When              : "when",
        KeyWordType.End               : "End"
    },
    TokenType.VarType: {
        VarTypeType.Int               : 'int',
        VarTypeType.Varchar           : 'varchar',
        VarTypeType.Char              : 'char',
        VarTypeType.Decimal           : 'decimal',
        VarTypeType.Integer           : 'integer'
    },
    TokenType.Punctuaition: {
        PunctType.Dot                 :'.',
        PunctType.Coma                :',',
        PunctType.RoundBracket_Open   :'(',
        PunctType.RoundBracket_Close  :')',
        PunctType.Semicolon           :';',
        PunctType.SingleQuotes        :"'",
        PunctType.DoubleQuotes        :'"'
    },
    TokenType.Operations: {
        OperationType.More            :'>',
        OperationType.Less            :'<',
        OperationType.Eq              :'=',
        OperationType.LessEq          :'<=',
        OperationType.MoreEq          :'>=',
        OperationType.NotEq           :'<>',
        OperationType.Plus            :'+',
        OperationType.Minus           :'-',
        OperationType.Devide          :'/'
    },
    TokenType.Comment: {
        CommentType.MultiComment_Open : '/*',
        CommentType.MultiComment_Close: '*/',
        CommentType.SingleComment     : '--'
    }
}

SPACES = {
    SpacesType.Space: ' ',
    SpacesType.Sym_n: '\n',
    SpacesType.Sym_t: '\t'
}

ALL_TOKEN = []
ALL_TOKEN_DICT = {}
for a in TOKEN_DICT.values():
    ALL_TOKEN += a.values()
    ALL_TOKEN_DICT.update(a)

class Token:
    token_type = TokenType.Invalid
    subtype = None
    pos = 0
    column = 0
    row = 0
    value = ''
    old_value = ''
    orig_pos = 0
    orig_value = ''
    def __init__(self, in_pos, in_type, in_value):
        self.token_type = in_type
        self.value = in_value
        self.old_value = in_value
        self.orig_pos = in_pos
        self.orig_value = in_value
        self.pos = in_pos
    def __str__(self):
        return '{0:30} {1:30} {2:30} {3:4} {4:4}'.format(str(self.token_type), str(self.value), str(self.subtype), str(self.row), str(self.column))
    def set_type(self):
        new_token_type, new_subtype = Token.get_info(self.value.lower())
        if new_token_type != None:
            self.subtype = new_subtype
            self.token_type = new_token_type

    @staticmethod
    def get_info(token):
        for token_type in TOKEN_DICT:
            for subtype in TOKEN_DICT[token_type]:
                token_array = TOKEN_DICT[token_type][subtype]
                if token == token_array:
                    return token_type, subtype
        for space_type in SPACES:
            if token == SPACES[space_type]:
                return TokenType.Spaces, space_type
        return None, None
