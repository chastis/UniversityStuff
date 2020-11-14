from enum import Enum
import json
from lexer import Lexer
from tokens import *

class FormatPartition(Enum):
    Case = 0

class CaseParam(Enum):
    Keywords = 0
    Types = 1
    Identifiers = 2
    Aliases = 3
    QuotedIdentifiers = 4
    IdentifierQuotation = 5

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
    changing = True
    unformatted_tokens = {}
    def add_error_message_to_token(self, tokens, message):
        for token in tokens:
            if (token.row, token.column) in self.unformatted_tokens:
                if message not in self.unformatted_tokens[(token.row, token.column)]:
                    self.unformatted_tokens[(token.row, token.column)][2].append(message)
            else:
                self.unformatted_tokens[(token.row, token.column)] = (token, token.value, [])
                self.unformatted_tokens[(token.row, token.column)][2].append(message)


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
    
    def change_case(self, lexer, case_option, token_type, token_subtype = None):
        if case_option != CaseOption.DoNotChange:
            if token_type in lexer.tokens_dict.keys():
                prev_keys = [key for key in lexer.tokens_dict[token_type].keys()]
                for token_value in prev_keys:
                    if token_subtype is None or \
                        len(lexer.tokens_dict[token_type][token_value]) > 0 and lexer.tokens_dict[token_type][token_value][0].subtype == token_subtype:
                        find_tokens = []
                        if case_option == CaseOption.ToUpper:
                            find_tokens = lexer.find_token_by_value(token_value)
                            self.add_error_message_to_token(find_tokens, "Incorrect Case, expected: upper")
                            if self.changing:
                                lexer.change_token_value(token_value, token_value.upper())
                        if case_option == CaseOption.ToLower:
                            find_tokens = lexer.find_token_by_value(token_value)
                            self.add_error_message_to_token(find_tokens, "Incorrect Case, expected: lower")
                            if self.changing:
                                lexer.change_token_value(token_value, token_value.lower())
                        if case_option == CaseOption.ToTittle:
                            find_tokens = lexer.find_token_by_value(token_value)
                            self.add_error_message_to_token(find_tokens, "Incorrect Case, expected: title")
                            if self.changing:
                                lexer.change_token_value(token_value, token_value.title())
                        if case_option == CaseOption.Quote:
                            find_tokens = lexer.find_token_by_value(token_value)
                            self.add_error_message_to_token(find_tokens, "Incorrect Case, expected: quote")
                            if self.changing:
                                lexer.change_token_value(token_value, '"' + token_value + '"')
                        if case_option == CaseOption.Unquote:
                            find_tokens = lexer.find_token_by_value(token_value)
                            self.add_error_message_to_token(find_tokens, "Incorrect Case, expected: unquote")
                            if self.changing:
                                lexer.change_token_value(token_value, token_value[1:-1])
    def format_case(self, lexer):
        case_options = self.options[FormatPartition.Case]

        if CaseParam.IdentifierQuotation in case_options.keys() and case_options[CaseParam.IdentifierQuotation] != CaseOption.DoNotChange:
            if case_options[CaseParam.IdentifierQuotation] == CaseOption.Quote:
                self.change_case(lexer, case_options[CaseParam.IdentifierQuotation], TokenType.Identifier, IdentifierType.Default)
                self.change_case(lexer, case_options[CaseParam.IdentifierQuotation], TokenType.Identifier, IdentifierType.AliasDefault)
                lexer.change_token_subtype(IdentifierType.Default, IdentifierType.Quoted)
                lexer.change_token_subtype(IdentifierType.AliasDefault, IdentifierType.AliasQuoted)
            if case_options[CaseParam.IdentifierQuotation] == CaseOption.Unquote:
                self.change_case(lexer, case_options[CaseParam.IdentifierQuotation], TokenType.Identifier, IdentifierType.Quoted)
                self.change_case(lexer, case_options[CaseParam.IdentifierQuotation], TokenType.Identifier, IdentifierType.AliasQuoted)
                lexer.change_token_subtype(IdentifierType.Default, IdentifierType.Default)
                lexer.change_token_subtype(IdentifierType.AliasDefault, IdentifierType.AliasDefault)

        if CaseParam.Keywords in case_options.keys() and case_options[CaseParam.Keywords] != CaseOption.DoNotChange:
            self.change_case(lexer, case_options[CaseParam.Keywords], TokenType.KeyWord)

        if CaseParam.Types in case_options.keys() and case_options[CaseParam.Types] != CaseOption.DoNotChange:
            if case_options[CaseParam.Types] == CaseOption.AsKeyWords and \
                CaseParam.Keywords in case_options.keys() and case_options[CaseParam.Keywords] != CaseOption.DoNotChange:
                self.change_case(lexer, case_options[CaseParam.Keywords], TokenType.Type)
            else:
                self.change_case(lexer, case_options[CaseParam.Types], TokenType.Type)

        if CaseParam.Identifiers in case_options.keys() and case_options[CaseParam.Identifiers] != CaseOption.DoNotChange:
            self.change_case(lexer, case_options[CaseParam.Identifiers], TokenType.Identifier, IdentifierType.Default)
            self.change_case(lexer, case_options[CaseParam.Identifiers], TokenType.Identifier, IdentifierType.AliasDefault)

        if CaseParam.QuotedIdentifiers in case_options.keys() and case_options[CaseParam.QuotedIdentifiers] != CaseOption.DoNotChange:
            self.change_case(lexer, case_options[CaseParam.QuotedIdentifiers], TokenType.Identifier, IdentifierType.Quoted)
            self.change_case(lexer, case_options[CaseParam.QuotedIdentifiers], TokenType.Identifier, IdentifierType.AliasQuoted)

        if CaseParam.Aliases in case_options.keys() and case_options[CaseParam.Aliases] != CaseOption.DoNotChange:
            self.change_case(lexer, case_options[CaseParam.Aliases], TokenType.Identifier, IdentifierType.AliasQuoted)
            self.change_case(lexer, case_options[CaseParam.Aliases], TokenType.Identifier, IdentifierType.AliasDefault)
        
            
    def format_lexer(self, lexer):
        if self.data is None or not isinstance(lexer, Lexer):
            return # error
        if FormatPartition.Case in self.options.keys():
            self.format_case(lexer)
    
    def print_format_errors(self, file_name):
        with open(file_name, "w") as file:
            for token in self.unformatted_tokens:
                for error in self.unformatted_tokens[token][2]:
                    file.write('at line {0:5} in {1:30} - {2:1}\n'.format(str(token[0]), str(self.unformatted_tokens[token][1]), error))
            
            
        