from copy import copy
import errno
from typing import List
from tokens import *
from formatblock import *

class TokenNode:
    def __init__(self, token, parent):
        self.token = token
        self.parent = parent
    token = None
    parent = None
    childes = None
    def get_closest_token(self):
        node = self
        while TokenNode.node_is_token(node):
            if node.parent is None:
                return None
            node = node.parent
        return node.token
    def get_prev_childs(self):
        if self.parent is not None:
            index = self.parent.childes.index(self)
            if index > 0:
                return self.parent.childes[0:index]
        return None
    def get_prev_childs_with_blocks(self):
        if self.parent is not None:
            index = self.parent.childes.index(self)
            if index > 0:
                childes = self.parent.childes[0:index]
                i = 0
                while i < len(childes):
                    if childes[i].is_block() or childes[i].is_sub_block():
                        new_child = childes[i].get_first_child_token()
                        childes[i] = new_child
                    i += 1
                return childes
        return None
    def get_first_child_token(self):
        if self.childes is None:
            return None
        for child in self.childes:
            if child.is_token():
                return child
            else:
                child_token = child.get_first_child_token()
                if child_token is not None:
                    return child_token
        return None
    def get_closest_parent_token(self):
        if self.parent is not None:
            if self.parent.is_token():
                return self.parent
            else:
                return self.parent.get_closest_parent_token()
        return None
    def get_closest_parent_in_block(self):
        if TokenNode.node_is_token(self.parent):
            return self.parent
        return None
    def add_child(self, child):
        if self.childes is None:
            self.childes = [child]
        else:
            self.childes.append(child)
    def print(self, indent):
        if not TokenNode.node_is_token(self):
            print(indent * '    ' + self.token)
        else:
            print(indent * '    ' + self.token.value)
        if self.childes is not None:
            for child in self.childes:
                child.print(indent + 1)
    def find_node_by_token(self, token):
        if self.token is not None and\
            self.token == token:
            return self
        if self.childes is not None:
            for child in self.childes:
                child_token = child.find_node_by_token(token)
                if child_token is not None:
                    return child_token
        return None
    def is_sub_block(self):
        return self.token and self.token == 'sub-block'
    def is_block(self):
        return self.token and self.token == 'block'
    def is_token(self):
        return TokenNode.node_is_token(self)
    @staticmethod
    def node_is_token(node):
        if node is None \
            or node.token is None \
            or node.token == 'block'\
            or node.token == 'sub-block':
            return False
        return True


class Lexer:
    pos = 0
    prev_chars = ''
    orig_chars = ''
    changed_chars = ''
    tokens = []
    tokens_dict = {}
    error_token = []
    _shft_by_error = 0
    token_tree = None
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
        if cur_token == len(self.tokens):
            cur_token = None
        if cur_error == len(self.error_token):
            cur_error = None
        i = 0
        self.changed_chars = self.prev_chars.lower()
        while i < len(self.changed_chars):
            if cur_token is not None:
                pos = i
                is_token = True
                # if there is multi-line comment, it can have changed value (coz tabs can be replaced to spaces)
                is_check_old_value = self.tokens[cur_token].subtype != CommentType.MultiComment
                check_value = self.tokens[cur_token].old_value if is_check_old_value else self.tokens[cur_token].value
                for char in check_value:
                    if pos >= len(self.changed_chars) or char.lower() != self.changed_chars[pos]:
                        is_token = False
                        break
                    pos += 1
                if is_token:
                    self.tokens[cur_token].pos = i
                    token_v  = self.tokens[cur_token].value
                    self.tokens[cur_token].old_value = token_v
                    self.changed_chars = self.changed_chars[0:i] + token_v + self.changed_chars[i+len(check_value):len(self.changed_chars)]
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
        if cur_error == len(self.error_token):
            cur_error = None
        if cur_token == len(self.tokens):
            cur_token = None
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
    def is_start_of_digit(self, i):
        return self.is_correct_pos(i) and (self.prev_chars[i].isdigit() or \
            self.prev_chars[i] == ALL_TOKEN_DICT[OperationType.Minus] and self.is_correct_pos(i+1) and self.prev_chars[i+1].isdigit())
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
            correct_digit = self.is_start_of_digit(i) or self.prev_chars[i].isdigit()      
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
        while self.is_correct_pos():
            c = self.prev_chars[self.pos]
            if c in SPACES.values():
                self.next_char()
                continue
            if self.is_start_of_identifier(c):
                current_token = self.parse_next_word()
                # if this not identifier, it will wkow about this inside at token.set_type()
                token = self.insert_token(current_token, TokenType.Identifier)
                if current_token.lower() not in ALL_TOKEN:
                    # if pre-previous token is AS, so we are find AliaS
                    if len(self.tokens) > 1 and self.tokens[-2].token_type == TokenType.KeyWord and self.tokens[-2].subtype == KeyWordType.As:
                        token.subtype = IdentifierType.AliasDefault
                    else:
                        token.subtype = IdentifierType.Default
                continue
            if self.is_start_of_digit(self.pos):
                current_token = self.parse_next_digit()
                token = self.insert_token(current_token, TokenType.Value)
                token.subtype = ValuesType.Real if '.' in current_token else ValuesType.Integer
                continue
            if c == ALL_TOKEN_DICT[PunctType.SingleQuotes]:
                current_token = self.parse_next_string(PunctType.SingleQuotes)
                token = self.insert_token(current_token, TokenType.Value)
                token.subtype = ValuesType.String
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
            if c in TOKEN_DICT[TokenType.Punctuaition].values() \
                or c in TOKEN_DICT[TokenType.Operations].values():
                if self.is_correct_pos(self.pos+1):
                    temp_c = c + self.prev_chars[self.pos + 1]
                    if temp_c in TOKEN_DICT[TokenType.Punctuaition].values() \
                        or temp_c in TOKEN_DICT[TokenType.Operations].values() \
                        or temp_c in TOKEN_DICT[TokenType.Comment].values():
                        c = temp_c
                if c in TOKEN_DICT[TokenType.Comment].values():
                    current_token, commentType = self.parse_next_comment()
                    self.insert_token(current_token, TokenType.Comment).subtype = commentType
                elif c in TOKEN_DICT[TokenType.Punctuaition].values():
                    self.insert_token(c, TokenType.Punctuaition)
                elif c in TOKEN_DICT[TokenType.Operations].values():
                    self.insert_token(c, TokenType.Operations)
                continue
            if c == ALL_TOKEN_DICT[KeyWordType.Star]:
                self.insert_token(c, TokenType.KeyWord)
            self.next_char()
        self.calculate_column_and_row()
        self.build_token_tree()

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
    @staticmethod
    def change_tab_to_space_in_string(string, tab_size):
        i = 0
        string_size = len(string)
        while i < string_size:
            if string[i] == SPACES[SpacesType.Sym_t]:
                string = string[0:i] + ' '*tab_size + string[i+1:string_size]
                string_size = len(string)
            i += 1
        return string
    def change_tab_to_space(self, tab_size):
        self.prev_chars = self.change_tab_to_space_in_string(self.prev_chars, tab_size)
        if TokenType.Comment in self.tokens_dict:
            multi_comment_token_for_change = []
            for token_value in self.tokens_dict[TokenType.Comment]:
                token = self.tokens_dict[TokenType.Comment][token_value][0]
                if token.subtype == CommentType.MultiComment:
                    new_token_value = self.change_tab_to_space_in_string(token.value, tab_size)
                    multi_comment_token_for_change.append((token.value, new_token_value))
            for t_v in multi_comment_token_for_change:
                self.change_token_value(t_v[0], t_v[1])
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
    @staticmethod
    def change_space_to_tab_in_string(string, tab_size):
        i = 0
        file_char_size = len(string)
        is_new_line = True
        while i < file_char_size:
            if is_new_line:
                pos = i
                while string[pos] == SPACES[SpacesType.Space]:
                    pos += 1
                if pos - i >= tab_size:
                    tab_num = (pos - i) // tab_size
                    string = string[0:i] + '\t'*tab_num + string[i + tab_size * tab_num:file_char_size]
                    file_char_size = len(string)
                    i += tab_num - 1
                is_new_line = False
            i += 1
            if i < file_char_size and string[i] == SPACES[SpacesType.Sym_n]:
                is_new_line = True
                i += 1
        return string
    def change_space_to_tab(self, tab_size):
        self.prev_chars = self.change_space_to_tab_in_string(self.prev_chars, tab_size)
        
        if TokenType.Comment in self.tokens_dict:
            multi_comment_token_for_change = []
            for token_value in self.tokens_dict[TokenType.Comment]:
                token = self.tokens_dict[TokenType.Comment][token_value][0]
                if token.subtype == CommentType.MultiComment:
                    new_token_value = self.change_space_to_tab_in_string(token.value, tab_size)
                    multi_comment_token_for_change.append((token.value, new_token_value))
            for t_v in multi_comment_token_for_change:
                self.change_token_value(t_v[0], t_v[1])
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

    # tree tokens logic

    @staticmethod
    def is_token_start_of_block(token):
        if isinstance(token, Token):
            return token.token_type in BLOCKS or token.subtype in BLOCKS
        return False
    @staticmethod
    def is_token_start_of_enumeration(token):
        if isinstance(token, Token):
            return token.token_type in ENUMERAION or token.subtype in ENUMERAION
        return False

    @staticmethod
    def parse_next_block(tokens, start):
        if not isinstance(tokens, List) or not isinstance(start, Token):
            return []
        pos = tokens.index(start) + 1
        block = [start]
        if start.subtype == PunctType.RoundBracket_Open:
            open_brackets_count = 1
            while pos < len(tokens):
                block.append(tokens[pos])
                if tokens[pos].subtype == PunctType.RoundBracket_Close:
                    open_brackets_count -= 1
                if tokens[pos].subtype == PunctType.RoundBracket_Open:
                    open_brackets_count += 1
                if open_brackets_count == 0:
                    break
                pos += 1
        else:
            while pos < len(tokens):
                block.append(tokens[pos])
                if start.token_type in BLOCKS:
                    if tokens[pos].subtype == BLOCKS[start.token_type] \
                        or tokens[pos].token_type == BLOCKS[start.token_type]:
                        break
                if start.subtype in BLOCKS:   
                   if tokens[pos].subtype == BLOCKS[start.subtype] \
                        or tokens[pos].token_type == BLOCKS[start.subtype]:
                        break

                pos += 1
        return block

    @staticmethod
    def check_block_for_enumeration(node):
        if not isinstance(node, TokenNode) \
            or node.childes is None:
            return
        start_type = None
        start_i = None
        i = 0
        is_find_coma = False
        while i < len(node.childes):
            token = node.childes[i].token
            if not TokenNode.node_is_token(node.childes[i]):
                i += 1
                continue
            if Lexer.is_token_start_of_enumeration(token):
                if token.token_type in ENUMERAION:
                    start_type = token.token_type
                else:
                    start_type = token.subtype
                start_i = i
            elif start_type is not None \
                and (is_find_coma and (token.token_type == ENUMERAION[start_type] \
                or token.subtype == ENUMERAION[start_type])\
                or token.subtype == PunctType.Coma):
                is_find_coma = True
                block_node = TokenNode('sub-block', node)
                if token.subtype != PunctType.Coma:
                    if start_type in ENUMERAION_ENDING_SKIP:
                        block_node.childes = node.childes[start_i:i]
                        node.childes = node.childes[0:start_i] + [block_node] + node.childes[i:len(node.childes)]
                    else:
                        block_node.childes = node.childes[start_i:i+1]
                        node.childes = node.childes[0:start_i] + [block_node] + node.childes[i+1:len(node.childes)]
                    start_type = None
                    is_find_coma = False
                else:
                    block_node.childes = node.childes[start_i:i+1]
                    node.childes = node.childes[0:start_i] + [block_node] + node.childes[i+1:len(node.childes)]
                for update_child in block_node.childes:
                    update_child.parent = block_node
                start_i += 1
                i = start_i - 1
            i += 1              

    @staticmethod
    def build_tree_from_block(block, start_block):
        if start_block.childes is None or len(start_block.childes) == 0:
            i = 0
        else:
            i = block.index(start_block.childes[0].token) + 1
        while i < len(block):
            token = block[i]
            if Lexer.is_token_start_of_block(token):
                new_block = Lexer.parse_next_block(block, token)
                block_node = TokenNode('block', start_block)
                block_node.add_child(TokenNode(token, block_node))
                block_node = Lexer.build_tree_from_block(new_block, block_node)
                Lexer.check_block_for_enumeration(block_node)
                start_block.add_child(block_node)
                i += len(new_block) - 1
            else:
                start_block.add_child(TokenNode(token, start_block))
            i += 1
        return start_block            
    
    def build_token_tree(self):
        self.token_tree = TokenNode('block', None)
        self.token_tree = Lexer.build_tree_from_block(self.tokens, self.token_tree)

    # end tree tokens logic

    # indents logic

    @staticmethod
    def token_connected_to_token(parent, child):
         # a parent for b
        if not isinstance(parent, Token) or not isinstance(child, Token):
            return False
        if parent.token_type is not None and parent.token_type in CONNECTED_TOKENS:
            if child.token_type is not None and child.token_type in CONNECTED_TOKENS[parent.token_type] \
                or child.subtype is not None and child.subtype in CONNECTED_TOKENS[parent.token_type]:
                return True
        elif parent.subtype is not None and parent.subtype in CONNECTED_TOKENS:
            if child.token_type is not None and child.token_type in CONNECTED_TOKENS[parent.subtype] \
                or child.subtype is not None and child.subtype in CONNECTED_TOKENS[parent.subtype]:
                return True
        return False
    @staticmethod
    def token_pseudoconnected_to_token(parent, child):
        if not isinstance(parent, Token) or not isinstance(child, Token):
            return False
        if parent.token_type is not None and parent.token_type in PSEUDONONNECTED_TOKENS:
            if child.token_type is not None and child.token_type in PSEUDONONNECTED_TOKENS[parent.token_type] \
                or child.subtype is not None and child.subtype in PSEUDONONNECTED_TOKENS[parent.token_type]:
                return True
        elif parent.subtype is not None and parent.subtype in PSEUDONONNECTED_TOKENS:
            if child.token_type is not None and child.token_type in PSEUDONONNECTED_TOKENS[parent.subtype] \
                or child.subtype is not None and child.subtype in PSEUDONONNECTED_TOKENS[parent.subtype]:
                return True
        return False

    @staticmethod
    def remove_empty_line(string):
        i = 0
        is_new_line = True
        new_line_pos = 0
        while i < len(string):
            if string[i] == SPACES[SpacesType.Sym_n]:
                if is_new_line:
                    string = string[0:new_line_pos] + string[i:len(string)]
                    i = new_line_pos
                is_new_line = True
                new_line_pos = i+1
            elif string[i] not in SPACES.values():
                is_new_line = False
            i += 1
        return string
    def remove_empty_lines(self):
        self.prev_chars = self.remove_empty_line(self.prev_chars)

        if TokenType.Comment in self.tokens_dict:
            multi_comment_token_for_change = []
            for token_value in self.tokens_dict[TokenType.Comment]:
                token = self.tokens_dict[TokenType.Comment][token_value][0]
                if token.subtype == CommentType.MultiComment:
                    new_token_value = self.remove_empty_line(token.value)
                    multi_comment_token_for_change.append((token.value, new_token_value))
            for t_v in multi_comment_token_for_change:
                self.change_token_value(t_v[0], t_v[1])
        self.merge_token_and_spaces()
    def find_not_empty_lines(self):
        string = self.prev_chars
        i = 0
        is_new_line = True
        new_line_pos = 0
        not_empty_lines = []
        while i < len(string):
            if string[i] == SPACES[SpacesType.Sym_n]:
                if is_new_line:
                    if new_line_pos != i:
                        not_empty_lines.append(new_line_pos)
                is_new_line = True
                new_line_pos = i+1
            elif string[i] not in SPACES.values():
                is_new_line = False
            i += 1
        return not_empty_lines
    def get_changed_indents(self, indent, cont_indent, string, skip_comments = False):
        cur_token = 0
        i = 0
        is_new_line = True
        indented_tokens = {}
        new_lines_tokens = []
        first_token_on_line = None
        while i < len(string):
            if cur_token is None:
                i += 1
                break
            token = self.tokens[cur_token]
            pos = i
            is_token = True
            for c in token.value:
                if string[pos] != c:
                    is_token = False
                    break
                else:
                    pos += 1
            if is_token:
                if is_new_line:
                    new_lines_tokens.append(token)
                    first_token_on_line = token
                    node = self.token_tree.find_node_by_token(token)
                    prev_childs = node.get_prev_childs_with_blocks()
                    while prev_childs is None:
                        if node.parent is None:
                            break
                        node = node.parent
                        prev_childs = node.get_prev_childs_with_blocks()
                    connected_prev_child = None
                    need_add_indent = True
                    if prev_childs is not None:
                        for child in reversed(prev_childs):
                            if child.is_token() and Lexer.token_connected_to_token(child.token, token):
                                connected_prev_child = child
                                break
                        if connected_prev_child is None and len(prev_childs) > 0:
                            for child in reversed(prev_childs):
                                if child.is_token() and Lexer.token_pseudoconnected_to_token(child.token, token):
                                    connected_prev_child = child
                                    need_add_indent = False #@#############
                                    break
                        if connected_prev_child is None:    
                            connected_prev_child = prev_childs[0]
                            need_add_indent = False
                    if connected_prev_child is not None:
                        total_indent = indented_tokens[connected_prev_child.token]
                        if need_add_indent:
                            if connected_prev_child.token.subtype == PunctType.RoundBracket_Open:
                                total_indent += cont_indent
                            else:
                                total_indent += indent
                        indented_tokens[token] = total_indent
                    else:
                        prev_parent = node.get_closest_parent_token()
                        if prev_parent is None:
                            indented_tokens[token] = 0
                        else:
                            total_indent = indented_tokens[prev_parent.token]
                            if prev_parent.token.subtype == PunctType.RoundBracket_Open:
                                total_indent += cont_indent
                            else:
                                total_indent += indent
                            indented_tokens[token] = total_indent
                    pos = i
                    while pos > 0 and string[pos-1] != SPACES[SpacesType.Sym_n]:
                        pos -= 1
                    string = string[0:pos] + ' ' * indented_tokens[token] + string[i:len(string)]
                    i = pos + indented_tokens[token]
                else:
                    indented_tokens[token] = indented_tokens[first_token_on_line]
                i += len(token.value) - 1
                cur_token += 1
                while cur_token != len(self.tokens) and \
                    not skip_comments and self.tokens[cur_token].subtype == CommentType.MultiComment:
                    cur_token+=1
                if cur_token == len(self.tokens):
                    cur_token = None
            if string[i] == SPACES[SpacesType.Sym_n]:
                is_new_line = True
            elif string[i] not in SPACES.values():
                is_new_line = False
            i += 1
        return string, indented_tokens, new_lines_tokens
    def change_indent(self, indent, cont_indent):
        self.merge_token_and_spaces()
        self.prev_chars, a, b = self.get_changed_indents(indent, cont_indent, self.prev_chars)
        self.merge_token_and_spaces()
    def find_indent(self, indent, cont_indent, tab_size):
        inc_indents = []
        s = self.change_tab_to_space_in_string(self.prev_chars, tab_size)
        s, indented_tokens, new_lines_tokens = self.get_changed_indents(indent, cont_indent, s)
        for token in new_lines_tokens:
            token_indent = indented_tokens[token]
            i = token.pos
            while i > 0 and self.prev_chars[i - 1] != SPACES[SpacesType.Sym_n]:
                i -= 1
            if token.pos - i != token_indent:
                inc_indents.append(i)
        return inc_indents