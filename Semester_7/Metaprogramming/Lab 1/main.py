from lexer import Lexer
from tokens import *
#print (KEY_WORDS)
print(KEY_WORDS[TokenType.KeyWord])
print('table' in KEY_WORDS[TokenType.KeyWord])
print(ALL_KW)
print('table' in ALL_KW)
#l = Lexer()
#l.parse("test.sql")