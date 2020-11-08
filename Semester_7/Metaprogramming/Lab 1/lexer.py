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

    def parse_next_word(self):
        current_token = self.file_chars[self.pos]
        i = self.pos + 1
        while self.is_correct_pos(i) and self.file_chars[i]:
            if self.can_be_in_identifier(self.file_chars[i]):
                current_token += self.file_chars[i]
                i += 1
            else:
                break
        return current_token
    def parse_next_digit(self):
        current_token = self.file_chars[self.pos]
        i = self.pos + 1
        while self.is_correct_pos(i) and self.file_chars[i]:
            if self.can_be_in_digit(i):
                current_token += self.file_chars[i]
                i += 1
            else:
                break
        return current_token

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
            if c in SPACES:
                self.next_char()
                continue
            if self.is_start_of_identifier(c):
                current_token = self.parse_next_word()
                current_type = TokenType.Identifier
                if current_token in ALL_KW:
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
            self.next_char()
        
        for token in self.tokens:
            token.set_type()


