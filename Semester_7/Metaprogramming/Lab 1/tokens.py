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
    Minus = 12,
    Devide = 13

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
        KeyWordType.Having: 'having',
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
        PunctType.Minus               :'-',
        PunctType.Devide              :'/'
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
    category_type = TokenType.Invalid
    token_type = None
    value = ''

    def __init__(self, in_type, in_value = ''):
        self.category_type = in_type
        self.value = in_value
    def __str__(self):
        return '{0:20} {1:20} {2:20}'.format(str(self.category_type), str(self.value), str(self.token_type))
    def set_type(self):
        new_category_type, new_token_type = Token.get_info(self.value)
        if new_category_type != None:
            self.category_type = new_category_type
            self.token_type = new_token_type

    @staticmethod
    def get_info(token):
        for kw_type in KEY_WORDS:
            for specific_type in KEY_WORDS[kw_type]:
                token_array = KEY_WORDS[kw_type][specific_type]
                if token == token_array:
                    return kw_type, specific_type
        for space_type in SPACES:
            if token == SPACES[space_type]:
                return TokenType.Spaces, space_type
        return None, None
