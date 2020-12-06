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
    Char = 4

class IdentifierType(Enum):
    Default = 0
    IncludePath = 1

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
    Define = 9
    Ifndef = 10
    Pragma = 11
    Once = 12
    Endif = 13 
    Struct = 14
    Inline = 15
    Virtual = 16
    Override = 17
    Operator = 18
    Template = 19
    Typename = 20
    Using = 21
    Namespace = 22
    Sizeof = 23
    Nullptr = 24
    Public = 25
    Private = 26
    Protected = 27
    Final = 28
    Include = 29

class VarTypeType(Enum):
    Int = 0
    Char = 1
    Long = 2
    Bool = 3
    Void = 4
    Double = 5

class PunctType(Enum):
    RoundBracket_Open = 2
    RoundBracket_Close = 3
    SquareBracket_Open = 4
    SquareBracket_Close = 5
    BraceBracket_Open = 4
    BraceBracket_Close = 5
    Semicolon = 6
    SingleQuotes = 7
    DoubleQuotes = 8
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
    Mode = 10
    And = 11
    Not = 12
    Or = 13
    BitwiseAnd = 14
    BitwiseOr = 15
    BitwiseXor = 16
    BitwiseNot = 17
    BitwiseShistLeft = 18
    BitwiseShiftRight = 19
    Assigne = 20
    PlusAssign = 21
    MinusAssign = 22
    MultiplyAssinge = 23
    DevideAssigne = 24
    ModeAssigne = 25
    ShiftRightAssigne = 26
    ShiftLeftAssigne = 27
    AndAssigne = 28
    XorAssigne = 29
    OrAssigne = 30
    Dot = 31
    Coma = 32
    Arrow = 33
    PlusInc = 34
    MinusInc = 35
    Colon = 36
    Question = 37
    DoubleColon = 38

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
        KeyWordType.Return            : 'return',
        KeyWordType.Define            : 'define',
        KeyWordType.Ifndef            : 'ifndef',
        KeyWordType.Pragma            : 'pragma',
        KeyWordType.Once              : 'once',
        KeyWordType.Endif             : 'endif',
        KeyWordType.Struct            : 'strcut',
        KeyWordType.Inline            : 'inline',
        KeyWordType.Virtual           : 'virtual',
        KeyWordType.Override          : 'override',
        KeyWordType.Operator          : 'operator',
        KeyWordType.Template          : 'template',
        KeyWordType.Typename          : 'typename',
        KeyWordType.Using             : 'using',
        KeyWordType.Namespace         : 'namespace',
        KeyWordType.Sizeof            : 'sizeof',
        KeyWordType.Nullptr           : 'nullptr',
        KeyWordType.Public            : 'public',
        KeyWordType.Private           : 'private',
        KeyWordType.Protected         : 'protected',
        KeyWordType.Final             : 'final',
        KeyWordType.Include           : 'include'
    },
    TokenType.VarType: {
        VarTypeType.Int               : 'int',
        VarTypeType.Char              : 'char',
        VarTypeType.Long              : 'long',
        VarTypeType.Bool              : 'bool',
        VarTypeType.Void              : 'void',
        VarTypeType.Double            : 'double'
    },
    TokenType.Punctuaition: {
        PunctType.RoundBracket_Open   :'(',
        PunctType.RoundBracket_Close  :')',
        PunctType.SquareBracket_Open  :'[',
        PunctType.SquareBracket_Close :']',
        PunctType.BraceBracket_Open   :'{',
        PunctType.BraceBracket_Close  :'}',
        PunctType.Semicolon           :';',
        PunctType.SingleQuotes        :"'",
        PunctType.DoubleQuotes        :'"',
        PunctType.BackSlash           :'\\'
    },
    TokenType.Operations: {
        OperationType.NotEq             :'!=',
        OperationType.Plus              :'+',
        OperationType.Minus             :'-',
        OperationType.Devide            :'/',
        OperationType.Multiply          :'*',
        OperationType.More              :'>',
        OperationType.Less              :'<',
        OperationType.Eq                :'==',
        OperationType.LessEq            :'<=',
        OperationType.MoreEq            :'>=',
        OperationType.Mode              :'%',
        OperationType.And               :'&&',
        OperationType.Not               :'!',
        OperationType.Or                :'||',
        OperationType.BitwiseAnd        :'&',
        OperationType.BitwiseOr         :'|',
        OperationType.BitwiseXor        :'^',
        OperationType.BitwiseNot        :'~',
        OperationType.BitwiseShistLeft  :'<<',
        OperationType.BitwiseShiftRight :'>>',
        OperationType.Assigne           :'=',
        OperationType.PlusAssign        :'+=',
        OperationType.MinusAssign       :'-=',
        OperationType.MultiplyAssinge   :'*=',
        OperationType.DevideAssigne     :'/=', 
        OperationType.ModeAssigne       :'%=',
        OperationType.ShiftRightAssigne :'<<=',
        OperationType.ShiftLeftAssigne  :'>>=',
        OperationType.AndAssigne        :'&=',
        OperationType.XorAssigne        :'^=',
        OperationType.OrAssigne         :'|=',
        OperationType.Dot               :'.',
        OperationType.Coma              :',',
        OperationType.Arrow             :'->',
        OperationType.PlusInc           :'++',
        OperationType.MinusInc          :'--',
        OperationType.Colon             :':',
        OperationType.Question          :'?',
        OperationType.DoubleColon       :'::'
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
    orig_value = ''
    def __init__(self, in_pos, in_value, in_type = None, in_subtype = None):
        self.value = in_value
        self.orig_value = in_value
        if in_type is not None:
            self.token_type = in_type  
        if in_subtype is not None:
            self.token_subtype = in_subtype
        if in_subtype is None and in_type is None:
            self.set_type()
        self.pos = in_pos
    def __str__(self):
        return '{0:30} {1:30} {2:30} {3:4} {4:4}'.format(str(self.token_type), str(self.value), str(self.token_subtype), str(self.row), str(self.column))
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
