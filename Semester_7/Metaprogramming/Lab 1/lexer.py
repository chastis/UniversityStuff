import errno
from tokens import *

class Lexer:
    pos = 0
    prev_chars = ''
    orig_chars = ''
    changed_chars = ''
    tokens = []
    tokens_dict = {}
    error_token = []
    _shft_by_error = 0
    def reset(self):
        self.pos = 0
        self.prev_chars = ''
        self.tokens = []
        self.tokens_dict = {}
        self.error_token = []
        self._shft_by_error = 0
    def __init__(self):
        self.reset()
    def is_correct_pos(self, i = None):
        if i is None:
            return self.pos < len(self.prev_chars)
        return i < len(self.prev_chars)
    def next_char(self):
        self.pos += 1
    def move_by_token(self, token):
        if isinstance(token, Token):
            self.pos += len(token.value)
        else:
            self.pos += len(token)
    def merge_token_and_spaces(self):
        cur_token = 0
        cur_error = 0
        i = 0
        self.changed_chars = self.prev_chars.lower()
        while i < len(self.changed_chars):
            if cur_token is not None:
                pos = i
                is_token = True
                for char in self.tokens[cur_token].old_value:
                    if pos >= len(self.changed_chars) or char.lower() != self.changed_chars[pos]:
                        is_token = False
                        break
                    pos += 1
                if is_token:
                    self.tokens[cur_token].pos = i
                    token_v  = self.tokens[cur_token].value
                    token_old_v  = self.tokens[cur_token].old_value
                    self.tokens[cur_token].old_value = token_v
                    self.changed_chars = self.changed_chars[0:i] + token_v + self.changed_chars[i+len(token_old_v):len(self.changed_chars)]
                    i += len(token_v) - 1
                    cur_token += 1
                    if cur_token == len(self.tokens):
                        cur_token = None
            if cur_error is not None:
                pos = i
                is_token = True
                for char in self.error_token[cur_error].orig_value:
                    if pos >= len(self.changed_chars) or char.lower() != self.changed_chars[pos]:
                        is_token = False
                        break
                    pos += 1
                if is_token:
                    self.error_token[cur_error].pos = i
                    token_v  = self.error_token[cur_error].orig_value
                    token_old_v  = self.tokens[cur_token].orig_value
                    self.changed_chars = self.changed_chars[0:i] + token_v + self.changed_chars[i+len(token_old_v):len(self.changed_chars)]
                    i += len(token_v) - 1
                    cur_error += 1
                    if cur_error == len(self.error_token):
                        cur_error = None
            i += 1
        self.prev_chars = self.changed_chars
        self.calculate_column_and_row()
    def calculate_column_and_row(self):
        column = 0
        row = 0
        cur_pos = 0
        cur_token = 0
        cur_error = 0
        for char in self.prev_chars:
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
    def get_row_and_column_for_position(self, in_pos):
        column = 0
        row = 0
        for i in range(len(self.prev_chars)):
            if i == in_pos:
                return row, column
            column += 1
            if self.prev_chars[i] == SPACES[SpacesType.Sym_n]:
                column = 0
                row += 1

    def is_start_of_identifier(self, char):
        return char == '_' or char.isalpha()
    def can_be_in_identifier(self, char):
        return self.is_start_of_identifier(char) or char.isdigit()
    def is_start_of_digit(self, char):
        return char.isdigit()
    def can_be_in_digit(self, i):
        correct_digit = False
        if self.prev_chars[i] == '.':
            if self.is_correct_pos(i+1):
                if self.prev_chars[i+1].isdigit():
                    correct_digit = True
                else:
                    if self.prev_chars[i+1] in SPACES.values():
                        for sp_key, sp_value in SPACES.items():
                            if sp_value == self.prev_chars[i+1]:
                                self.add_error(i, "Expected [Digit] after [.] but find [" + str(sp_key) + "]")
                                break
                    else:
                        self.add_error(i, "Expected [Digit] after [.] but find [" + self.prev_chars[i+1] + "]")
            else:
                self.add_error(i, "Expected [Digit] after [.] but find [EOF]")
        else:
            correct_digit = self.is_start_of_digit(self.prev_chars[i]) or self.prev_chars[i].isdigit()      
        return correct_digit
  
    def is_eol(self, char):
        return char == SPACES[SpacesType.Sym_n]
    def insert_token(self, token_value, token_type):
        token_value = self.orig_chars[self.pos:self.pos+len(token_value)]
        new_token = Token(self.pos, token_type, token_value)
        new_token.set_type()
        token_type = new_token.token_type # reinit type, it could change
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
        new_token.old_value = '' if pos+error_shift>=len(self.prev_chars) else self.prev_chars[pos:pos+error_shift]
        self._shft_by_error += error_shift

    def parse_next_word(self):
        current_token = self.prev_chars[self.pos]
        i = self.pos + 1
        while self.is_correct_pos(i):
            if self.can_be_in_identifier(self.prev_chars[i]):
                current_token += self.prev_chars[i]
                i += 1
            else:
                break
        return current_token
    def parse_next_digit(self):
        current_token = self.prev_chars[self.pos]
        i = self.pos + 1
        while self.is_correct_pos(i):
            if self.can_be_in_digit(i):
                current_token += self.prev_chars[i]
                i += 1
            else:
                break
        return current_token
    def parse_next_string(self, string_end):
        current_token = self.prev_chars[self.pos]
        i = self.pos + 1
        while self.is_correct_pos(i):
            if self.prev_chars[i] == ALL_TOKEN_DICT[string_end]:
                current_token += self.prev_chars[i]
                break
            if not self.is_eol(self.prev_chars[i]):
                current_token += self.prev_chars[i]
                i += 1
            else:
                self.add_error(i, "Expected [" + string_end.name + "], but find [EOL]")
                break
        if string_end == PunctType.DoubleQuotes and len(current_token) == 2:
            self.add_error(self.pos + 1, "Expected [String Identifier], but find [empty]")
        return current_token
    def parse_next_comment(self):
        current_token = self.prev_chars[self.pos] + self.prev_chars[self.pos + 1]
        i = self.pos + 2
        if current_token == '--':
            # oneline
            while self.is_correct_pos(i):
                if self.prev_chars[i] == SPACES[SpacesType.Sym_n]:
                    break
                current_token += self.prev_chars[i]
                i += 1
            return current_token, CommentType.SingleComment
        else:
            # multiline
            while self.is_correct_pos(i):
                if self.is_correct_pos(i+1):
                    if self.prev_chars[i] + self.prev_chars[i+1] == ALL_TOKEN_DICT[CommentType.MultiComment_Close]:
                        current_token += self.prev_chars[i] + self.prev_chars[i+1]
                        break
                else:
                    self.add_error(i, "Expected [*/], but find [EOF]")
                current_token += self.prev_chars[i]
                i += 1
            return current_token, CommentType.MultiComment
        return None

    def parse(self, file_name):
        self.reset()
        with open(file_name, "r") as file:
            for line in file:
                for char in line:
                    self.orig_chars += char
                    self.prev_chars += char #.lower()
        if len(self.prev_chars) == 0:
            print ("file is empty")
            return
        while self.is_correct_pos():
            c = self.prev_chars[self.pos]
            if c in SPACES.values():
                self.next_char()
                continue
            if self.is_start_of_identifier(c):
                current_token = self.parse_next_word()
                # if this not identifier, it will wkow about this inside at token.set_type()
                token = self.insert_token(current_token, TokenType.Identifier)
                if current_token not in ALL_TOKEN:
                    # if pre-previous token is AS, so we are find AliaS
                    if len(self.tokens) > 1 and self.tokens[-2].token_type == TokenType.KeyWord and self.tokens[-2].subtype == KeyWordType.As:
                        token.subtype = IdentifierType.AliasDefault
                    else:
                        token.subtype = IdentifierType.Default
                continue
            if self.is_start_of_digit(c):
                current_token = self.parse_next_digit()
                current_type = TokenType.Real if '.' in current_token else TokenType.Integer
                self.insert_token(current_token, current_type)
                continue
            if c == ALL_TOKEN_DICT[PunctType.SingleQuotes]:
                current_token = self.parse_next_string(PunctType.SingleQuotes)
                self.insert_token(current_token, TokenType.String)
                continue
            if c == ALL_TOKEN_DICT[PunctType.DoubleQuotes]:
                current_token = self.parse_next_string(PunctType.DoubleQuotes)
                token_subtype = IdentifierType.Quoted
                # if previous token is AS, so we are find AliaS
                if len(self.tokens) > 0 and self.tokens[-1].token_type == TokenType.KeyWord and self.tokens[-1].subtype == KeyWordType.As:
                    token_subtype = IdentifierType.AliasQuoted
                token = self.insert_token(current_token, TokenType.Identifier)
                token.subtype = token_subtype
                continue
            if c in TOKEN_DICT[TokenType.Punctuaition].values():
                if self.is_correct_pos(self.pos+1):
                    temp_c = c + self.prev_chars[self.pos + 1]
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
        changed_tokens = []
        for token_type in self.tokens_dict:
            if old_value in self.tokens_dict[token_type]:
                for token in self.tokens_dict[token_type][old_value]:
                    token.value = new_value
                    changed_tokens.append(token)
                self.tokens_dict[token_type][new_value] = self.tokens_dict[token_type].pop(old_value)
                return changed_tokens
        return changed_tokens
    def find_token_by_value(self, old_value):
        changed_tokens = []
        for token in self.tokens:
            if token.value == old_value:
                changed_tokens.append(token)
        return changed_tokens

    def change_token_type(self, old_type, new_type):
        changed_tokens = []
        if old_type in self.tokens_dict:
            for token_value in self.tokens_dict[old_type]:
                for token in self.tokens_dict[old_type][token_value]:
                    token.token_type = new_type
                    changed_tokens.append(token)
        if new_type in self.tokens_dict:
            self.tokens_dict[new_type].update(self.tokens_dict.pop(old_type))
        else:
            self.tokens_dict[new_type] = self.tokens_dict.pop(old_type)
        return changed_tokens
    def find_token_by_type(self, old_type):
        changed_tokens = []
        for token in self.tokens:
            if token.token_type == old_type:
                changed_tokens.append(token)
        return changed_tokens

    def change_token_subtype(self, old_type, new_type):
        changed_tokens = []
        for token in self.tokens:
            if token.subtype == old_type:
                token.subtype = new_type
                changed_tokens.append(token)
        return changed_tokens
    def find_token_by_subtype(self, old_type):
        changed_tokens = []
        for token in self.tokens:
            if token.subtype == old_type:
                changed_tokens.append(token)
        return changed_tokens

    def change_tab_to_space(self, tab_size):
        i = 0
        file_char_size = len(self.prev_chars)
        while i < file_char_size:
            if self.prev_chars[i] == SPACES[SpacesType.Sym_t]:
                self.prev_chars = self.prev_chars[0:i] + ' '*tab_size + self.prev_chars[i+1:file_char_size]
                file_char_size = len(self.prev_chars)
            i += 1
        self.merge_token_and_spaces()
    def find_tabs(self, tab_size):
        i = 0
        tabs_pos = []
        file_char_size = len(self.prev_chars)
        while i < file_char_size:
            if self.prev_chars[i] == SPACES[SpacesType.Sym_t]:
                tabs_pos.append(i)
            i += 1
        return tabs_pos

    def change_space_to_tab(self, tab_size):
        i = 0
        file_char_size = len(self.prev_chars)
        is_new_line = True
        while i < file_char_size:
            if is_new_line:
                pos = i
                while self.prev_chars[pos] == SPACES[SpacesType.Space]:
                    pos += 1
                if pos - i >= tab_size:
                    tab_num = (pos - i) // tab_size
                    self.prev_chars = self.prev_chars[0:i] + '\t'*tab_num + self.prev_chars[i + tab_size * tab_num:file_char_size]
                    file_char_size = len(self.prev_chars)
                    i += tab_num - 1
                is_new_line = False
            i += 1
            if i < file_char_size and self.prev_chars[i] == SPACES[SpacesType.Sym_n]:
                is_new_line = True
                i += 1
        self.merge_token_and_spaces()
    def find_spaces_tabs(self, tab_size):
        i = 0
        tabs_pos = []
        file_char_size = len(self.prev_chars)
        is_new_line = True
        while i < file_char_size:
            if is_new_line:
                pos = i
                while self.prev_chars[pos] == SPACES[SpacesType.Space]:
                    pos += 1
                if pos - i >= tab_size:
                    tab_num = (pos - i) // tab_size
                    for tab_pos in range(tab_num):
                        tabs_pos.append(i + tab_pos * tab_size)
                    i += tab_num * tab_size - 1
                is_new_line = False
            i += 1
            if i < file_char_size and self.prev_chars[i] == SPACES[SpacesType.Sym_n]:
                is_new_line = True
                i += 1
        return tabs_pos

    def change_indent(self, indent, cont_indent):
        open_brackets = 0
        i = 0
        file_char_size = len(self.prev_chars)
        is_new_line = True
        while i < file_char_size:
            if is_new_line:
                pos = i
                while self.prev_chars[pos] == SPACES[SpacesType.Space]:
                    pos += 1
                if pos - i != indent:
                    self.prev_chars = self.prev_chars[0:i] + ' '*indent + self.prev_chars[i + indent:file_char_size]
                    file_char_size = len(self.prev_chars)
                    i+= indent - 1
                is_new_line = False
            i += 1
            if i < file_char_size:
                if self.prev_chars[i] == SPACES[SpacesType.Sym_n]:
                    is_new_line = True
                    i += 1
                elif self.prev_chars[i] == ALL_TOKEN_DICT[PunctType.RoundBracket_Open]:
                    open_brackets += 1
                elif self.prev_chars[i] == ALL_TOKEN_DICT[PunctType.RoundBracket_Close] and open_brackets > 0:
                    open_brackets += 1

        self.merge_token_and_spaces()
    def find_indent(self, indent, cont_indent):
        pass