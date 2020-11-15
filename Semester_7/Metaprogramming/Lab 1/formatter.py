from enum import Enum
import json
from lexer import Lexer
from tokens import *
from formatblock import *
import copy

class FormatPartition(Enum):
    Case = 0
    TabsAndIndents = 1

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

class TabsAndIndentsParam(Enum):
    UseTabCharacter = 0
    TabSize = 1
    Indent = 2
    ContinuationIndent = 3
    KeepIndentsOnEmptyLines = 4

CONST_TAB_SIZE = 4

FormatLibrary = {
   FormatPartition.Case: (CaseParam, CaseOption),
   FormatPartition.TabsAndIndents: (TabsAndIndentsParam, [])
}

FormatErrors = {
    0: "Incorrect Case, expected: upper",
    1: "Incorrect Case, expected: lower",
    2: "Incorrect Case, expected: title",
    3: "Incorrect Case, expected: quote",
    4: "Incorrect Case, expected: unquote",
    5: "Incorrect Tab, expected Spaces",
    6: "Incorrect Spaces, expected Tab"
}

class Formatter:
    data = None
    options = {}
    changing = True
    unformatted_tokens = {}
    formatted_lexer = None
    def add_error_message_to_token(self, tokens, message):
        for token in tokens:
            if (token.row, token.column) in self.unformatted_tokens:
                if message not in self.unformatted_tokens[(token.row, token.column)]:
                    self.unformatted_tokens[(token.row, token.column)][2].append(message)
            else:
                self.unformatted_tokens[(token.row, token.column)] = (token, token.value, [])
                self.unformatted_tokens[(token.row, token.column)][2].append(message)
    def add_error_message_to_pos(self, poses, message):
        for pos in poses:
            row, column = self.formatted_lexer.get_row_and_column_for_position(pos)
            if (row, column) in self.unformatted_tokens:
                if message not in self.unformatted_tokens[(row, column)]:
                    self.unformatted_tokens[(row, column)][2].append(message)
            else:
                self.unformatted_tokens[(row, column)] = (None, None, [])
                self.unformatted_tokens[(row, column)][2].append(message)

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
    
    def change_case(self, case_option, token_type, token_subtype = None):
        if case_option != CaseOption.DoNotChange:
            if token_type in self.formatted_lexer.tokens_dict.keys():
                prev_keys = [key for key in self.formatted_lexer.tokens_dict[token_type].keys()]
                for token_value in prev_keys:
                    if token_subtype is None or \
                        len(self.formatted_lexer.tokens_dict[token_type][token_value]) > 0 and self.formatted_lexer.tokens_dict[token_type][token_value][0].subtype == token_subtype:
                        find_tokens = []
                        if case_option == CaseOption.ToUpper and not token_value.isupper():
                            if self.changing:
                                self.formatted_lexer.change_token_value(token_value, token_value.upper())
                            else:
                                find_tokens = self.formatted_lexer.find_token_by_value(token_value)
                                self.add_error_message_to_token(find_tokens, FormatErrors[0])
                        if case_option == CaseOption.ToLower and not token_value.islower():
                            if self.changing:
                                self.formatted_lexer.change_token_value(token_value, token_value.lower())
                            else:
                                find_tokens = self.formatted_lexer.find_token_by_value(token_value)
                                self.add_error_message_to_token(find_tokens, FormatErrors[1])
                        if case_option == CaseOption.ToTittle and not token_value.istitle():
                            if self.changing:
                                self.formatted_lexer.change_token_value(token_value, token_value.title())
                            else:
                                find_tokens = self.formatted_lexer.find_token_by_value(token_value)
                                self.add_error_message_to_token(find_tokens, FormatErrors[2])
                        if case_option == CaseOption.Quote and token_value[0] != '"' and token_value[-1] != '"':
                            if self.changing:
                                self.formatted_lexer.change_token_value(token_value, '"' + token_value + '"')
                            else:
                                find_tokens = self.formatted_lexer.find_token_by_value(token_value)
                                self.add_error_message_to_token(find_tokens, FormatErrors[3])
                        if case_option == CaseOption.Unquote and token_value[0] == '"' and token_value[-1] == '"':
                            if self.changing:
                                self.formatted_lexer.change_token_value(token_value, token_value[1:-1])
                            else:
                                find_tokens = self.formatted_lexer.find_token_by_value(token_value)
                                self.add_error_message_to_token(find_tokens, FormatErrors[4])
    def format_case(self):
        case_options = self.options[FormatPartition.Case]

        if CaseParam.IdentifierQuotation in case_options.keys() and case_options[CaseParam.IdentifierQuotation] != CaseOption.DoNotChange:
            if case_options[CaseParam.IdentifierQuotation] == CaseOption.Quote:
                self.change_case(case_options[CaseParam.IdentifierQuotation], TokenType.Identifier, IdentifierType.Default)
                self.change_case(case_options[CaseParam.IdentifierQuotation], TokenType.Identifier, IdentifierType.AliasDefault)
                if self.changing:
                    self.formatted_lexer.change_token_subtype(IdentifierType.Default, IdentifierType.Quoted)
                    self.formatted_lexer.change_token_subtype(IdentifierType.AliasDefault, IdentifierType.AliasQuoted)
            if case_options[CaseParam.IdentifierQuotation] == CaseOption.Unquote:
                self.change_case(case_options[CaseParam.IdentifierQuotation], TokenType.Identifier, IdentifierType.Quoted)
                self.change_case(case_options[CaseParam.IdentifierQuotation], TokenType.Identifier, IdentifierType.AliasQuoted)
                if self.changing:
                    self.formatted_lexer.change_token_subtype(IdentifierType.Default, IdentifierType.Default)
                    self.formatted_lexer.change_token_subtype(IdentifierType.AliasDefault, IdentifierType.AliasDefault)

        if CaseParam.Keywords in case_options.keys() and case_options[CaseParam.Keywords] != CaseOption.DoNotChange:
            self.change_case(case_options[CaseParam.Keywords], TokenType.KeyWord)

        if CaseParam.Types in case_options.keys() and case_options[CaseParam.Types] != CaseOption.DoNotChange:
            if case_options[CaseParam.Types] == CaseOption.AsKeyWords and \
                CaseParam.Keywords in case_options.keys() and case_options[CaseParam.Keywords] != CaseOption.DoNotChange:
                self.change_case(case_options[CaseParam.Keywords], TokenType.VarType)
            else:
                self.change_case(case_options[CaseParam.Types], TokenType.VarType)

        changed_alias = False
        if CaseParam.Aliases in case_options.keys() and case_options[CaseParam.Aliases] != CaseOption.DoNotChange:
            self.change_case(case_options[CaseParam.Aliases], TokenType.Identifier, IdentifierType.AliasQuoted)
            self.change_case(case_options[CaseParam.Aliases], TokenType.Identifier, IdentifierType.AliasDefault)
            changed_alias = True

        if CaseParam.Identifiers in case_options.keys() and case_options[CaseParam.Identifiers] != CaseOption.DoNotChange:
            self.change_case(case_options[CaseParam.Identifiers], TokenType.Identifier, IdentifierType.Default)
            if not changed_alias:
                self.change_case(case_options[CaseParam.Identifiers], TokenType.Identifier, IdentifierType.AliasDefault)

        if CaseParam.QuotedIdentifiers in case_options.keys() and case_options[CaseParam.QuotedIdentifiers] != CaseOption.DoNotChange:
            self.change_case(case_options[CaseParam.QuotedIdentifiers], TokenType.Identifier, IdentifierType.Quoted)
            if not changed_alias:
                self.change_case(case_options[CaseParam.QuotedIdentifiers], TokenType.Identifier, IdentifierType.AliasQuoted)

        

    def format_indents(self):
        indent_options = self.options[FormatPartition.TabsAndIndents]    

        tab_size = CONST_TAB_SIZE

        if TabsAndIndentsParam.TabSize in indent_options.keys():
            if indent_options[TabsAndIndentsParam.TabSize].isdigit():
                tab_size = int(indent_options[TabsAndIndentsParam.TabSize])

        if TabsAndIndentsParam.UseTabCharacter in indent_options.keys():
            if indent_options[TabsAndIndentsParam.UseTabCharacter] == str(True):
                if self.changing:
                    self.formatted_lexer.change_space_to_tab(tab_size)
                else:
                    mistabs = self.formatted_lexer.find_spaces_tabs(tab_size)
                    self.add_error_message_to_pos(mistabs, FormatErrors[6])
            elif indent_options[TabsAndIndentsParam.UseTabCharacter] == str(False):
                if self.changing:
                    self.formatted_lexer.change_tab_to_space(tab_size)
                else:
                    mistabs = self.formatted_lexer.find_tabs(tab_size)
                    self.add_error_message_to_pos(mistabs, FormatErrors[5])

    def format_lexer(self, lexer):
        if self.data is None or not isinstance(lexer, Lexer):
            return # error
        self.formatted_lexer = copy.deepcopy(lexer)
        need_changing = self.changing
        self.changing = False
        for i in range(2):
            if FormatPartition.Case in self.options.keys():
                self.format_case()
            if FormatPartition.TabsAndIndents in self.options.keys():
                self.format_indents()
            self.changing = need_changing
            if not need_changing:
                break
        if not need_changing:
            self.formatted_lexer.merge_token_and_spaces()
    
    def print_format_errors(self, file_name):
        with open(file_name, "w") as file:
            for token in self.unformatted_tokens:
                for error in self.unformatted_tokens[token][2]:
                    if self.unformatted_tokens[token][0] is not None:
                        file.write('at line {0:5} in {1:30} - {2:1}\n'.format(str(token[0]), str(self.unformatted_tokens[token][1]), error))
                    else:
                        file.write('at line {0:5} at pos {1:26} - {2:1}\n'.format(str(token[0]), str(token[1]), error))
            
            
    def create_formatted_file(self, file_name):
        with open(file_name, "w") as file:
            file.write(self.formatted_lexer.changed_chars)