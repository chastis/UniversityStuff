from copy import copy
from typing import List
from tokens import *
from lexer import *
import typing

class CaseType(Enum):
    Camel = 0
    UnderScore = 2

class Formatter:
    def change_case(self, lexer : Lexer):
        tokens = lexer.scope.get_variables()
        for token in tokens:
            token.value = token.value.upper()