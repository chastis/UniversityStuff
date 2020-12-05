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
    Bool = 3

class IdentifierType(Enum):
    Default = 0

class KeyWordType(Enum):
    Class = 0
    Case = 1
    Break = 2
    Catch = 3
    Const = 4
    For = 5
    While = 6
    Union = 7
    Return = 8

class VarTypeType(Enum):
    Int = 0
    Char = 1
    Long = 2
    Bool = 3

class PunctType(Enum):
    Dot = 0
    Coma = 1
    RoundBracket_Open = 2
    RoundBracket_Close = 3
    SquareBracket_Open = 4
    SquareBracket_Close = 5
    BraceBracket_Open = 4
    BraceBracket_Close = 5
    Semicolon = 6
    SingleQuotes = 7
    DoubleQuotes = 8
    Arrow = 9
    BackSlash = 10

class OperationType(Enum):
    NotEq = 0
    Plus = 1
    Minus = 2
    Devide = 3
    Multiply = 4
    More = 5
    Less = 6
    Eq = 7
    LessEq = 8
    MoreEq = 9

class CommentType(Enum):
    MultiComment = 0
    SingleComment = 1
    MultiComment_Open = 2
    MultiComment_Close = 3

class SpacesType(Enum):
    Space = 0,
    Sym_n = 1,
    Sym_t = 2

TOKEN_DICT = {
    TokenType.KeyWord: {
        KeyWordType.Class             : 'class',
        KeyWordType.Case              : 'case',
        KeyWordType.Break             : 'break',
        KeyWordType.Catch             : 'catch',
        KeyWordType.Const             : 'const',
        KeyWordType.For               : 'for',
        KeyWordType.While             : 'while',
        KeyWordType.Union             : 'union',
        KeyWordType.Return            : 'return'
    },
    TokenType.VarType: {
        VarTypeType.Int               : 'int',
        VarTypeType.Char              : 'char',
        VarTypeType.Long              : 'long',
        VarTypeType.Bool              : 'bool'
    },
    TokenType.Punctuaition: {
        PunctType.Dot                 :'.',
        PunctType.Coma                :',',
        PunctType.RoundBracket_Open   :'(',
        PunctType.RoundBracket_Close  :')',
        PunctType.SquareBracket_Open  :'[',
        PunctType.SquareBracket_Close :']',
        PunctType.BraceBracket_Open   :'{',
        PunctType.BraceBracket_Close  :'}',
        PunctType.Semicolon           :';',
        PunctType.SingleQuotes        :"'",
        PunctType.DoubleQuotes        :'"',
        PunctType.Arrow               :'->',
        PunctType.BackSlash           :'\\'
    },
    TokenType.Operations: {
        OperationType.NotEq           :'<>',
        OperationType.Plus            :'+',
        OperationType.Minus           :'-',
        OperationType.Devide          :'/',
        OperationType.Multiply        :'*',
        OperationType.More            :'>',
        OperationType.Less            :'<',
        OperationType.Eq              :'=',
        OperationType.LessEq          :'<=',
        OperationType.MoreEq          :'>='
    },
    TokenType.Comment: {
        CommentType.SingleComment     : '//',
        CommentType.MultiComment_Open : '/*',
        CommentType.MultiComment_Close: '*/'
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
    token_subtype = None
    pos = 0
    column = 0
    row = 0
    value = ''
    def __init__(self, in_pos, in_value, in_type = None, in_subtype = None):
        if in_type is None:
            self.token_type = in_type  
        if in_subtype is None:
            self.token_subtype = in_subtype
        if in_subtype is None and in_type is None:
            self.set_type()
        self.value = in_value
        self.pos = in_pos
    def __str__(self):
        return '{0:30} {1:30} {2:30} {3:4} {4:4}'.format(str(self.token_type), str(self.value), str(self.subtype), str(self.row), str(self.column))
    def set_type(self):
        new_token_type, new_subtype = Token.get_info(self.value.lower())
        self.token_subtype = new_subtype
        self.token_type = new_token_type

    @staticmethod
    def get_info(token_value):
        if token_value == "true" or token_value == "false":
            return TokenType.Value, ValuesType.Bool
        for token_type in TOKEN_DICT:
            for subtype in TOKEN_DICT[token_type]:
                token_dict_value = TOKEN_DICT[token_type][subtype]
                if token_value == token_dict_value:
                    return token_type, subtype
        for space_type in SPACES:
            if token_value == SPACES[space_type]:
                return TokenType.Spaces, space_type
        return None, None
