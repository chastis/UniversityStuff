from lexer import Lexer
from tokens import *

l = Lexer()
l.parse("test.sql")
for token in l.tokens:
    print(token)