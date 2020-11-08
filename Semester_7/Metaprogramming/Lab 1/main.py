from lexer import Lexer
from tokens import *

l = Lexer()
l.parse("test.sql")
print(ALL_KW_DICT)
for token in l.tokens:
    print(token)
