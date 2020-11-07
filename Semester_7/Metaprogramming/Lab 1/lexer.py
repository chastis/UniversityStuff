import errno
from tokens import *

class Lexer:
    pos = 0
    file_chars = ''
    def reset(self):
        pos = 0
        file_chars = ''
    def __init__(self):
        reset()
    def is_correct_pos(self):
        return pos < len(file_chars)
    def next_char(self):
        pos += 1

    def parse(self, file_name):
        reset()
        with open(file_name, "r") as file:
            for line in file:
                for char in line:
                    file_chars += char
        if len(file_chars) == 0:
            print ("you are loh, as your file btw")
            return
        while is_correct_pos():
            if file_chars[pos] in SPACES:
                next_char()
                continue
            if file_chars[pos].isalpha():
                pass
