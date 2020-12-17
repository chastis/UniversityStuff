from typing import *
import re
from os import mkdir
from os.path import exists
from importlib import import_module, reload
from Py2SQL.config import SUPPORTED_TYPES, REVERSE_SUPPORTED_TYPES


class Object(object):
    """
        Так как к чистому классу object нельзя добавлять новые аттрибуты
    """
    pass


def serialize_to_py_object(title_columns: list, data: List[Tuple]) -> List[object]:
    """
        Конвертируем данные из бд в объекты
    :param title_columns: список названий полей, или же классовых переменных
    :param data: ряды данных, или же сами объекты в будущем
    :return: список объектов
    """
    python_objects_list: List = []
    for row in data:
        new_object = Object()
        for field, value in zip(title_columns, row):
            # print(field, value)
            object.__setattr__(new_object,
                               field,
                               value)
        python_objects_list.append(new_object)
    return python_objects_list


def merge_field_info_with_value(fields_info: List[Tuple], data: List[Tuple]) -> List[Tuple]:
    """
        Соединяем название и тип поля с его значением
    :param fields_info: список полей с кортежами в которых название и тип поля
    :param data: сами значения
    :return: список кортежей с названием поля, типом, и значением
    """
    result = []
    for row in data:
        for field, cell in zip(fields_info, row):
            result.append(field[1:] + (cell, ))
    return result


def convert_python_types_in_sqlite_types(attributes: tuple,
                                         object_: bool = False) -> List[Tuple]:
    """
        Вычленяем нужные поля, которые являются переменными, и их типы переводим в типы бд
    :param object_: если передаем объект то помечаем что это объект
    :param attributes: нужные аттрибуты класса
    :return: список кортежей где каждый кортеж - имя поля, его тип.
    """
    result = []
    for title_var, field_type in attributes:

        if object_:
            field_type = str(type(field_type))

        if not title_var.startswith('_'):

            if field_type not in SUPPORTED_TYPES.keys():
                type_in_db = re.search(pattern="\'[^\']*",
                                       string=str(field_type)).group()[1:]
            else:
                type_in_db = field_type

            result.append((title_var, SUPPORTED_TYPES.get(type_in_db)))
    return result


def create_class(title: str, data: List[Tuple]) -> str:
    result = f'class {title}:\n    ' + '\n    '.join(row[1] + ': ' + REVERSE_SUPPORTED_TYPES.get(row[2]) for row in data) + '\n'
    return result


def create_module(title_class: str, title_module: str, class_: List[Tuple]):
    """
        Создание модуля и импорт его в глобальную видимость
    :param title_class: название модуля и класса
    :param class_: строение класса, а именно список с переменными, название и тип
    :return:
    """
    if not exists(title_module):
        mkdir(title_module)
    path_to_new_script = title_module + '/' + title_class + '.py'
    with open(title_module + '/__init__.py', 'w', encoding='utf8') as f:
        f.write(f'from {title_module + "." + title_class} import * ')
    with open(path_to_new_script, 'w', encoding='utf8') as f:
        f.write(create_class(title=title_class,
                             data=class_))
    reload(import_module(path_to_new_script.replace('/', '.')[:-3]))


def create_script_with_class(title_class: str, parent_class: str, class_: List[Tuple]):
    with open(parent_class + '/' + title_class + '.py', 'w', encoding='utf8') as f:
        f.write(create_class(title=title_class,
                             data=class_))


def get_children(class_: object, clases: list= []):
    subclasses = class_.__subclasses__()
    if subclasses:
        for subclass in subclasses:
            clases += get_children(subclass, clases + subclasses)
    return clases