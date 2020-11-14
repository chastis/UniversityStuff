from formatter import Formatter
from lexer import Lexer
from tokens import *

l = Lexer()
l.parse("test.sql")
print ('tokens : --------------------------------------------------------------------------------------------------------------')
if True:
    for token_type in l.tokens_dict:
        print(token_type)
        for token_value in l.tokens_dict[token_type]:
            print("    " + str(token_value))
            for token in l.tokens_dict[token_type][token_value]:
                print("        " + str(token))
else:
    for token in l.tokens:
        print(token)


print ('errors  : --------------------------------------------------------------------------------------------------------------')
for token in l.error_token:
    print(token)

f = Formatter()
f.load_template("template.json")
f.format_lexer(l)
l = f.formatted_lexer
f.create_formatted_file('formatted test.sql')
print ('modified tokens : --------------------------------------------------------------------------------------------------------------')
if True:
    for token_type in l.tokens_dict:
        print(token_type)
        for token_value in l.tokens_dict[token_type]:
            print("    " + str(token_value))
            for token in l.tokens_dict[token_type][token_value]:
                print("        " + str(token))
else:
    for token in l.tokens:
        print(token)
f.print_format_errors('output.log')
