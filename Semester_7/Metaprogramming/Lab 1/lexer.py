import errno
from tokens import *

class Lexer:
    pos = 0
    file_chars = ''
    tokens = []
    def reset(self):
        pos = 0
        file_chars = ''
    def __init__(self):
        self.reset()
    def is_correct_pos(self, i = None):
        if i is None:
            return self.pos < len(self.file_chars)
        return i < len(self.file_chars)
    def next_char(self):
        self.pos += 1
    def move_by_token(self, token):
        if isinstance(token, Token):
            self.pos += len(token.value)
        else:
            self.pos += len(token)
    def is_start_of_identifier(self, char):
        return char == '_' or char.isalpha()
    def can_be_in_identifier(self, char):
        return self.is_start_of_identifier(char) or char.isdigit()
    def is_start_of_digit(self, char):
        return char.isdigit()
    def can_be_in_digit(self, i):
        char = self.file_chars[i]
        if char == '.':
            if self.is_correct_pos(i+1):
                if self.file_chars[i+1].isdigit():
                    return True
            # error ?
            return False
        return self.is_start_of_digit(char) or char.isdigit()
    def is_eol(self, char):
        return char == SPACES[SpacesType.Sym_n] or char == SPACES[SpacesType.Sym_t]

    def parse_next_word(self):
        current_token = self.file_chars[self.pos]
        i = self.pos + 1
        while self.is_correct_pos(i):
            if self.can_be_in_identifier(self.file_chars[i]):
                current_token += self.file_chars[i]
                i += 1
            else:
                break
        return current_token
    def parse_next_digit(self):
        current_token = self.file_chars[self.pos]
        i = self.pos + 1
        while self.is_correct_pos(i):
            if self.can_be_in_digit(i):
                current_token += self.file_chars[i]
                i += 1
            else:
                break
        return current_token
    def parse_next_string(self):
        current_token = self.file_chars[self.pos]
        i = self.pos + 1
        while self.is_correct_pos(i):
            if self.file_chars[i] == ALL_TOKEN_DICT[PunctType.Quotes]:
                current_token += self.file_chars[i]
                break
            if not self.is_eol(self.file_chars[i]):
                current_token += self.file_chars[i]
                i += 1
            else:
                # error
                break
        return current_token
    def parse_next_comment(self):
        current_token = self.file_chars[self.pos] + self.file_chars[self.pos + 1]
        i = self.pos + 2
        if current_token == '--':
            # oneline
            while self.is_correct_pos(i):
                if self.file_chars[i] == SPACES[SpacesType.Sym_n]:
                    break
                current_token += self.file_chars[i]
                i += 1
            return current_token, CommentType.SingleComment
        else:
            # multiline
            while self.is_correct_pos(i):
                if self.is_correct_pos(i+1):
                    if self.file_chars[i] + self.file_chars[i+1] == ALL_TOKEN_DICT[CommentType.MultiComment_Close]:
                        current_token += self.file_chars[i] + self.file_chars[i+1]
                        break
                else:
                    pass # error
                current_token += self.file_chars[i]
                i += 1
            return current_token, CommentType.MultiComment
        return None

    def parse(self, file_name):
        self.reset()
        with open(file_name, "r") as file:
            for line in file:
                for char in line:
                    self.file_chars += char.lower()
        if len(self.file_chars) == 0:
            print ("you are loh, as your file btw")
            return
        while self.is_correct_pos():
            c = self.file_chars[self.pos]
            if c in SPACES.values():
                self.next_char()
                continue
            if self.is_start_of_identifier(c):
                current_token = self.parse_next_word()
                current_type = TokenType.Identifier
                if current_token in ALL_TOKEN:
                    token_category, token_type =  Token.get_info(current_token)
                    if token_type is not None:
                        current_type = token_type
                self.tokens.append(Token(current_type, current_token))
                self.move_by_token(current_token)
                continue
            if self.is_start_of_digit(c):
                current_token = self.parse_next_digit()
                current_type = TokenType.Real if '.' in current_token else TokenType.Integer
                self.tokens.append(Token(current_type, current_token))
                self.move_by_token(current_token)
                continue
            if c == ALL_TOKEN_DICT[PunctType.Quotes]:
                current_token = self.parse_next_string()
                self.tokens.append(Token(TokenType.String, current_token))
                self.move_by_token(current_token)
                continue
            if c in TOKEN_DICT[TokenType.Punctuaition].values():
                if self.is_correct_pos(self.pos+1):
                    temp_c = c + self.file_chars[self.pos + 1]
                    if temp_c in TOKEN_DICT[TokenType.Punctuaition].values() \
                        or temp_c in TOKEN_DICT[TokenType.Comment].values():
                        c = temp_c
                if c in TOKEN_DICT[TokenType.Comment].values():
                    current_token, commentType = self.parse_next_comment()
                    new_token = Token(TokenType.Comment, current_token)
                    new_token.category_type = commentType
                    self.tokens.append(new_token)
                    self.move_by_token(current_token)
                elif c in TOKEN_DICT[TokenType.Punctuaition].values():
                    self.tokens.append(Token(TokenType.Punctuaition, c))
                    self.move_by_token(c)
                continue
            self.next_char()
        
        for token in self.tokens:
            token.set_type()


