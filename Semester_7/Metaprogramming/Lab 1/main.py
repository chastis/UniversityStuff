from lexer import Lexer
from tokens import *

l = Lexer()
l.parse("test.sql")
print ('tokens : ')
for token in l.tokens:
    print(token)
print ('errors  : ')
for token in l.error_token:
    print(token)