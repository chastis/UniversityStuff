from enum import Enum

class TokenType(Enum):
    Invalid = 0
    Identifier = 1
    String = 2
    Integer = 3
    Real = 4
    Comment = 5
    KeyWord = 6
    Type = 7
    Punctuaition = 8
    Spaces = 9
    Other = 999


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

class VarTypeType(Enum):
    Int = 0,
    Varchar = 1

class PunctType(Enum):
    Dot = 0,
    Coma = 1,
    RoundBracket_Open = 2,
    RoundBracket_Close = 3,
    Semicolon = 4,
    More = 5,
    Less = 6,
    Eq = 7,
    LessEq = 8,
    MoreEq = 9,
    NotEq = 10,
    Plus = 11,
    Minus = 12

class CommentType(Enum):
    MultiComment_Open = 0,
    MultiComment_Close = 1,
    SingleComment = 2

class SpacesType(Enum):
    Space = 0,
    Sym_n = 1,
    Syn_t = 2,

KEY_WORDS = {
    TokenType.KeyWord: {
        KeyWordType.Create: 'create',
        KeyWordType.Table : 'table',
        KeyWordType.Select: 'select',
        KeyWordType.From  : 'from',
        KeyWordType.Where : 'where',
        KeyWordType.Group : 'group',
        KeyWordType.By    : 'by',
        KeyWordType.Having : 'having',
        KeyWordType.Order : 'order',
        KeyWordType.Desc  : 'desc',
        KeyWordType.As    : 'as',
        KeyWordType.Not   : 'not',
        KeyWordType.Null  : 'null',
        KeyWordType.Star  : '*'
    },
    TokenType.Type: {
        VarTypeType.Int    : 'int',
        VarTypeType.Varchar: 'varchar'
    },
    TokenType.Punctuaition: {
        PunctType.Dot                 :'.',
        PunctType.Coma                :',',
        PunctType.RoundBracket_Open   :'(',
        PunctType.RoundBracket_Close  :')',
        PunctType.Semicolon           :';',
        PunctType.More                :'>',
        PunctType.Less                :'<',
        PunctType.Eq                  :'=',
        PunctType.LessEq              :'<=',
        PunctType.MoreEq              :'>=',
        PunctType.NotEq               :'<>',
        PunctType.Plus                :'+',
        PunctType.Minus               :'-'
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
    SpacesType.Syn_t: '\t'
}

ALL_KW = []
for a in KEY_WORDS.values(): ALL_KW += a.values()



class Token:
    type = TokenType.Invalid
    value = ''

    def __init__(self, in_type):
        self.type = in_type

    @staticmethod
    def get_info(token):
        for token_dict in KEY_WORDS:
            if token in token:
                pass # todo
