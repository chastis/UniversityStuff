from copy import copy
from typing import List
from tokens import *
import typing

class CommandType(Enum):
    Include = 0
    Macros = 1
    Initialization = 2
    Assigne = 3
    InitAndAssigne = 4

class ScopeNode:
    def __init__(self, token, parent):
        self.token = token
        self.parent = parent
    token = None
    parent : ScopeNode = None
    childes = None
    def get_closest_token(self):
        node = self
        while ScopeNode.node_is_token(node):
            if node.parent is None:
                return None
            node = node.parent
        return node.token
    def get_prev_childs(self):
        if self.parent is not None:
            index = self.parent.childes.index(self)
            if index > 0:
                return self.parent.childes[0:index]
        return None
    def get_prev_childs_token(self):
        if self.parent is not None:
            index = self.parent.childes.index(self)
            if index > 0:
                prev_childes = []
                for child in self.parent.childes[0:index]:
                    if child is not None and child.is_token():
                        prev_childes.append(child)
                if len(prev_childes) > 0:
                    return prev_childes
        return None
    def get_prev_child_token(self):
        if self.parent is not None:
            index = self.parent.childes.index(self)
            if index > 0:
                child = self.parent.childes[index-1]
                return child.get_last_child_token()
            else:
                self.parent.get_prev_child_token()
        return None
    def get_last_child_token(self):
        if self.childes is None:
            return None
        for child in reversed(self.childes):
            if child.is_token():
                return child
            else:
                child_token = child.get_last_child_token()
                if child_token is not None:
                    return child_token
        return None
    def get_prev_childs_with_blocks(self):
        if self.parent is not None:
            index = self.parent.childes.index(self)
            if index > 0:
                childes = self.parent.childes[0:index]
                i = 0
                while i < len(childes):
                    if childes[i].is_block() or childes[i].is_sub_block():
                        new_child = childes[i].get_first_child_token()
                        childes[i] = new_child
                    i += 1
                return childes
        return None
    def get_first_child_token(self):
        if self.childes is None:
            return None
        for child in self.childes:
            if child.is_token():
                return child
            else:
                child_token = child.get_first_child_token()
                if child_token is not None:
                    return child_token
        return None
    def get_first_child_token_or_self(self):
        if self.is_token():
            return self
        if self.childes is None:
            return None
        for child in self.childes:
            if child.is_token():
                return child
            else:
                child_token = child.get_first_child_token_or_self()
                if child_token is not None:
                    return child_token
        return None   
    def get_closest_parent_token(self):
        if self.parent is not None:
            if self.parent.is_token():
                return self.parent
            else:
                return self.parent.get_closest_parent_token()
        return None
    def get_closest_parent_in_block(self):
        if ScopeNode.node_is_token(self.parent):
            return self.parent
        return None
    def is_closest_parent_block(self):
        if self.parent is not None:
            if self.parent.is_block():
                return self.parent
            elif self.parent.is_sub_block():
                return self.parent.is_closest_parent_block()
        return None
    def get_all_childrens_tokens_as_list(self):
        cheild_tokens = []
        for child in self.childes:
            if child.is_token():
                cheild_tokens.append(child.token)
            else:
                cheild_tokens += child.get_all_childrens_tokens_as_list()
        return cheild_tokens
    def add_child(self, child):
        if self.childes is None:
            self.childes = [child]
        else:
            self.childes.append(child)
    def print(self, indent):
        if not ScopeNode.node_is_token(self):
            print(indent * '    ' + self.token)
        else:
            print(indent * '    ' + self.token.value)
        if self.childes is not None:
            for child in self.childes:
                child.print(indent + 1)
    def find_node_by_token(self, token):
        if self.token is not None and\
            self.token == token:
            return self
        if self.childes is not None:
            for child in self.childes:
                child_token = child.find_node_by_token(token)
                if child_token is not None:
                    return child_token
        return None
    def is_sub_block(self):
        return self.token and self.token == 'sub-block'
    def is_block(self):
        return self.token and self.token == 'block'
    def is_token(self):
        return ScopeNode.node_is_token(self)
    @staticmethod
    def node_is_token(node):
        if node is None \
            or node.token is None \
            or node.token == 'block'\
            or node.token == 'sub-block':
            return False
        return True

