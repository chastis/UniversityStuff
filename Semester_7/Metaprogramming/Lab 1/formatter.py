from enum import Enum
import json
from lexer import Lexer
from tokens import *
import copy

class FormatPartition(Enum):
    Case = 0

class CaseParam(Enum):
    Keywords = 0
    Types = 1
    Identifiers = 2
    Aliases = 3
    Quoted = 4
    Identifier = 5

class CaseOption(Enum):
    DoNotChange = 0
    ToUpper = 1
    ToLower = 2
    ToTittle = 3
    AsKeyWords = 4
    AsIdentifiers = 5
    Quote = 6
    Unquote = 7

FormatLibrary = {
   FormatPartition.Case: (CaseParam, CaseOption) 
}

class Formatter:
    data = None
    options = {}
    def load_template(self, file_name):
        with open(file_name, "r") as json_file:
            self.data = json.load(json_file)
            for category in self.data:
                category_name = category
                for category_enum in FormatPartition:
                    if category_name == category_enum.name:
                        category_name = category_enum
                        break
                if category_name in FormatLibrary:
                    for key, value in self.data[category].items():
                        key_name = key
                        value_name = value
                        for param_enum in FormatLibrary[category_name][0]:
                            if key_name == param_enum.name:
                                key_name = param_enum
                                break
                        for option_enum in FormatLibrary[category_name][1]:
                            if value_name == option_enum.name:
                                value_name = option_enum
                                break
                        if category_name not in self.options.keys():
                            self.options[category_name] = {}
                        self.options[category_name].update({key_name: value_name})
                else:
                    pass # error
    def format_case(self, lexer):
        case_options = self.options[FormatPartition.Case]
        if CaseParam.Keywords in case_options.keys() and case_options[CaseParam.Keywords] != CaseOption.DoNotChange:
            if TokenType.KeyWord in lexer.tokens_dict.keys():
                prev_keys = [key for key in lexer.tokens_dict[TokenType.KeyWord].keys()]
                for token_value in prev_keys:
                    if case_options[CaseParam.Keywords] == CaseOption.ToUpper:
                        lexer.change_token_value(token_value, token_value.upper())
                    if case_options[CaseParam.Keywords] == CaseOption.ToLower:
                        lexer.change_token_value(token_value, token_value.lower())
                    if case_options[CaseParam.Keywords] == CaseOption.ToTittle:
                        lexer.change_token_value(token_value, token_value.title())
            
    def format_lexer(self, lexer):
        if self.data is None or not isinstance(lexer, Lexer):
            return # error
        if FormatPartition.Case in self.options.keys():
            self.format_case(lexer)
        