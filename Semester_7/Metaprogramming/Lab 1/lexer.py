import errno
from tokens import *

class Lexer:
    pos = 0
    file_chars = ''
    tokens = []
    tokens_dict = {}
    error_token = []
    _shft_by_error = 0
    def reset(self):
        self.pos = 0
        self.file_chars = ''
        self.tokens = []
        self.tokens_dict = {}
        self.error_token = []
        self._shft_by_error = 0
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
    def calculate_column_and_row(self):
        column = 0
        row = 0
        cur_pos = 0
        cur_token = 0
        cur_error = 0
        for char in self.file_chars:
            if cur_token is not None and self.tokens[cur_token].pos == cur_pos:
                self.tokens[cur_token].row = row
                self.tokens[cur_token].column = column
                cur_token += 1
                if cur_token == len(self.tokens):
                    cur_token = None
            if cur_error is not None and self.error_token[cur_error].pos == cur_pos:
                self.error_token[cur_error].row = row
                self.error_token[cur_error].column = column
                cur_error += 1
                if cur_error == len(self.error_token):
                    cur_error = None
            column += 1
            if char == SPACES[SpacesType.Sym_n]:
                column = 0
                row += 1
            cur_pos += 1
    def is_start_of_identifier(self, char):
        return char == '_' or char.isalpha()
    def can_be_in_identifier(self, char):
        return self.is_start_of_identifier(char) or char.isdigit()
    def is_start_of_digit(self, char):
        return char.isdigit()
    def can_be_in_digit(self, i):
        correct_digit = False
        if self.file_chars[i] == '.':
            if self.is_correct_pos(i+1):
                if self.file_chars[i+1].isdigit():
                    correct_digit = True
                else:
                    if self.file_chars[i+1] in SPACES.values():
                        for sp_key, sp_value in SPACES.items():
                            if sp_value == self.file_chars[i+1]:
                                self.add_error(i, "Expected Digit after . but find " + str(sp_key))
                                break
                    else:
                        self.add_error(i, "Expected Digit after . but find " + self.file_chars[i+1])
            else:
                self.add_error(i, "Expected Digit after . but find EOF")
        else:
            correct_digit = self.is_start_of_digit(self.file_chars[i]) or self.file_chars[i].isdigit()      
        return correct_digit
  
    def is_eol(self, char):
        return char == SPACES[SpacesType.Sym_n]
    def insert_token(self, token_value, token_type):
        new_token = Token(self.pos, token_type, token_value)
        new_token.set_type()
        self.tokens.append(new_token)
        self.move_by_token(new_token)
        self.pos += self._shft_by_error
        self._shft_by_error = 0
        if token_type not in self.tokens_dict.keys():
            self.tokens_dict[token_type] = {}
        if token_value not in self.tokens_dict[token_type].keys():
            self.tokens_dict[token_type][token_value] = []
        self.tokens_dict[token_type][token_value].append(new_token)
        return new_token
    def add_error(self, pos, message, error_shift = 1):
        new_token = Token(pos, TokenType.Invalid, message)
        self.error_token.append(new_token)
        self._shft_by_error += error_shift

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
                self.add_error(i, 'Expected Quote ["] but find EOL')
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
                    self.add_error(i, "Expected End_Of_Comment [*/], but find EOF")
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
            print ("file is empty")
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
                    token_type, token_category =  Token.get_info(current_token)
                    if token_type is not None:
                        current_type = token_type
                self.insert_token(current_token, current_type)
                continue
            if self.is_start_of_digit(c):
                current_token = self.parse_next_digit()
                current_type = TokenType.Real if '.' in current_token else TokenType.Integer
                self.insert_token(current_token, current_type)
                continue
            if c == ALL_TOKEN_DICT[PunctType.Quotes]:
                current_token = self.parse_next_string()
                self.insert_token(current_token, TokenType.String)
                continue
            if c in TOKEN_DICT[TokenType.Punctuaition].values():
                if self.is_correct_pos(self.pos+1):
                    temp_c = c + self.file_chars[self.pos + 1]
                    if temp_c in TOKEN_DICT[TokenType.Punctuaition].values() \
                        or temp_c in TOKEN_DICT[TokenType.Comment].values():
                        c = temp_c
                if c in TOKEN_DICT[TokenType.Comment].values():
                    current_token, commentType = self.parse_next_comment()
                    self.insert_token(current_token, TokenType.Comment).subtype = commentType
                elif c in TOKEN_DICT[TokenType.Punctuaition].values():
                    self.insert_token(c, TokenType.Punctuaition)
                continue
            self.next_char()
        self.calculate_column_and_row()

    def change_token_value(self, old_value, new_value):
        for token_type in self.tokens_dict:
            if old_value in self.tokens_dict[token_type]:
                for token in self.tokens_dict[token_type][old_value]:
                    token.value = new_value
                self.tokens_dict[token_type][new_value] = self.tokens_dict[token_type].pop(old_value)
                return

