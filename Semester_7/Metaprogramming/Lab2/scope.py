from copy import copy
from typing import List
from tokens import *
import typing

class BlockType(Enum):
    Include = 0
    Macros = 1
    Definition = 2
    Operation = 3
    RoundBracketsScope = 4
    SquareBracketsScope = 5
    BraceBracketsScope = 6
    ClassMemberTypeScope = 7
    Token = 8
    Global = 9
    NonIdentified = 10

class Block:
    def __init__(self, type : BlockType):
        self.type = type
        self.tokens = []
    def is_token(self) -> bool:
        return self.type == BlockType.Token
    def get_by_type(self, type : BlockType) -> typing.List['Block']:
        out : typing.List['Block'] = []
        if self.type == type:
            out.append(self)
        for child in self.tokens:
            if child.type == type:
                out.append(child)
            else:
                child_out = child.get_by_type(type)
                if len(child_out) > 0:
                    out += child_out
        return out
    def get_all_child_tokens(self) -> typing.List['Block']:
        out : typing.List['Block'] = []
        if self.is_token():
            out.append(self)
        for child in self.tokens:
            if child.is_token():
                out.append(child)
            else:
                child_out = child.get_all_child_tokens()
                if len(child_out) > 0:
                    out += child_out
        return out
    type : BlockType
    token : Token
    tokens : typing.List['Block']
    child_len : int = 0
    parent : 'Block' = None

class ScopeNode:
    scope = Block(BlockType.Global)
    @staticmethod
    def if_start_of_block(start : Token) -> bool:
        return start.token_subtype == PunctType.RoundBracket_Open or \
                start.token_subtype == PunctType.BraceBracket_Open or \
                start.token_subtype == PunctType.SquareBracket_Open or \
                start.token_subtype == KeyWordType.Private or \
                start.token_subtype == KeyWordType.Protected or \
                start.token_subtype == KeyWordType.Public or \
                start.token_subtype == PunctType.Sharp
    @staticmethod   
    def parse_templates(full_block : Block) -> Block:
        pos = 0
        pos_finish = len(full_block.tokens)
        while pos < pos_finish:
            token = full_block.tokens[pos]
            if token.type == BlockType.NonIdentified:
                pass
            pos += 1
    @staticmethod
    def parse_next_block(pos_start : int, pos_finish : int, full_block : Block, start : Block = None) -> Block :
        out = Block(BlockType.Global)
        end_scope_type = []
        is_end_included = True
        row_depended = None
        last_unregistred_token = None
        if start is not None:
            out.tokens.append(start)
            out.child_len += start.child_len
            out.type = BlockType.NonIdentified
            if start.is_token():
                if start.token.token_subtype == PunctType.RoundBracket_Open:
                    out.type = BlockType.RoundBracketsScope
                    end_scope_type = [PunctType.RoundBracket_Close]
                elif start.token.token_subtype == PunctType.BraceBracket_Open:
                    out.type = BlockType.BraceBracketsScope
                    end_scope_type = [PunctType.BraceBracket_Close]
                elif start.token.token_subtype == PunctType.SquareBracket_Open:
                    out.type = BlockType.SquareBracketsScope
                    end_scope_type = [PunctType.SquareBracket_Close]
                elif start.token.token_subtype == KeyWordType.Public or\
                    start.token.token_subtype == KeyWordType.Protected or\
                    start.token.token_subtype == KeyWordType.Private :
                    out.type = BlockType.ClassMemberTypeScope
                    end_scope_type = [PunctType.BraceBracket_Close, KeyWordType.Public, KeyWordType.Protected, KeyWordType.Private]
                    is_end_included = False
                    if pos_start < pos_finish:
                        if full_block.tokens[pos_start].is_token() and\
                            full_block.tokens[pos_start].token.token_subtype == OperationType.Colon:
                            out.tokens.append(full_block.tokens[pos_start])
                            out.child_len += full_block.tokens[pos_start].child_len
                            full_block.tokens[pos_start].parent = out
                            pos_start += 1
                elif start.token.token_subtype == PunctType.Sharp:
                    out.type = BlockType.Macros
                    if pos_start < pos_finish:
                        if full_block.tokens[pos_start].is_token() and\
                            full_block.tokens[pos_start].token.token_subtype == KeyWordType.Include:
                            out.type = BlockType.Include
                    row_depended = start.token.row
                else:
                    end_scope_type = [PunctType.Semicolon]
                    last_unregistred_token = start
        
        pos = pos_start
        
        while pos < pos_finish:
            token = full_block.tokens[pos]
            if token.is_token() and token.token:
                if last_unregistred_token is None and\
                    token.token.token_type == TokenType.Identifier:
                    last_unregistred_token = token
                if row_depended is not None:
                    if row_depended != token.token.row:
                        if token.token.token_subtype == PunctType.BackSlash:
                            row_depended = token.token.row + 1
                        else:
                            break
                if token.token.token_subtype in end_scope_type or\
                   token.token.token_type in end_scope_type:
                    if is_end_included:
                        out.tokens.append(token)
                        token.parent = out
                        out.child_len += token.child_len
                    break
                if ScopeNode.if_start_of_block(token.token):
                    new_block = ScopeNode.parse_next_block(pos + 1, pos_finish, full_block, token)
                    new_block.parent = out
                    out.tokens.append(new_block)
                    out.child_len += new_block.child_len
                    pos += new_block.child_len
                    if out.type == BlockType.NonIdentified and \
                        new_block.type == BlockType.BraceBracketsScope and \
                        len(out.tokens) > 3 and out.tokens[-2].type == BlockType.RoundBracketsScope and \
                        out.tokens[-3].is_token() and out.tokens[-3].token.token_type == TokenType.Identifier:
                        break
                    continue
                elif out.type != BlockType.BraceBracketsScope and \
                    out.type != BlockType.ClassMemberTypeScope and \
                    out.type != BlockType.Global:
                    out.tokens.append(token)
                    token.parent = out
                    out.child_len += token.child_len
                else:
                    new_block = ScopeNode.parse_next_block(pos + 1, pos_finish, full_block, token)
                    new_block.parent = out
                    out.tokens.append(new_block)
                    out.child_len += new_block.child_len
                    pos += new_block.child_len
                    continue 
            pos += 1
        return out
    def parse_tokens(self, tokens : typing.List[Token]):
        self.scope.type = BlockType.Global
        for token in tokens:
            tokenBlock =  Block(BlockType.Token)
            tokenBlock.token = token
            tokenBlock.child_len = 1
            tokenBlock.parent = self.scope
            self.scope.tokens.append(tokenBlock)
        if len(tokens) > 0:
            self.scope = self.parse_next_block(0, len(self.scope.tokens), self.scope)
        print('in tokens len = ' + str(len(tokens)))
        print('out tokens len = ' + str(self.scope.child_len))
    def get_variables(self) -> typing.List[Token]:
        blocks = self.scope.get_by_type(BlockType.NonIdentified)
        token_blocks = []
        tokens = []
        for block in blocks:
            token_blocks += block.get_all_child_tokens()
        for token_block in token_blocks:
            if token_block.is_token() and token_block.token.token_type == TokenType.Identifier:
                tokens.append(token_block.token)
        return tokens

