from typing import Tuple, List

from .config import EXCEPTION_TEXT_CLASS_NO_ID


def output_one_column(data: list) -> tuple:
    """
        Вывод кортежа при запросе одной колонки из бд,
        (чтоб не было кортеж в кортеже)
    :param data:
    :return:
    """
    return tuple(row[0] for row in data)


def table_info(title_columns: tuple, data: list) -> list:
    # title_columns = tuple(row[0] for row in title_columns)
    # return tuple((title_columns,) + tuple(data[0:]))
    return data


def generate_sql_to_find_object(table: str, attributes: tuple) -> str:
    query: str = 'SELECT * ' \
                 f'FROM `{table}` ' \
                 f'WHERE '
    if not attributes:
        return query[:-6]
    else:
        for field, value in attributes:
            if isinstance(value, str) and ('>' in value or '<' in value):
                query += f'{field} {value}" AND '
            else:
                query += f'{field} = "{value}" AND '
        return query[:-4]


def generate_save_sql_query(table: str, py_object: object, update: bool = False) -> str:
    if update:
        query: str = f'UPDATE `{table}`' \
                     f'SET ' + '", '.join(title + ' = "' + str(value) for title, value in vars(py_object).items()) + \
                     f'" WHERE id = {vars(py_object).get("id")}'
    else:
        query: str = f'INSERT INTO `{table}` (`{"`, `".join(vars(py_object).keys())}`) ' \
                     f'VALUES ("' + '", "'.join(str(value) for value in vars(py_object).values()) + '")'
    return query


def check_having_in_table(table: str, id_: int) -> str:
    """
        Проверяем наличие записи в бд по id
    :param table: название таблицы
    :param id_: айди записи
    :return:
    """
    query: str = 'SELECT id ' \
                 f'FROM {table} ' \
                 f'WHERE id = {id_}'
    return query


def create_table(title: str, attributes: List[Tuple]):
    """
        Запрос на создание таблицы
    :param title:
    :param attributes:
    :return:
    """
    for title_row, type_ in attributes:
        if title_row.lower() == 'id':
            break
    else:
        raise print(EXCEPTION_TEXT_CLASS_NO_ID)
    query: str = f'CREATE TABLE "{title}" (' + \
                 ', '.join(f'"{title_row}" {type_}' for title_row, type_ in attributes) + \
                 ')'
    return query


def delete_object(table: str, row_id: int):
    """
        Удаление записи из таблицы
    :param table: название таблицы
    :param row_id: айди записи
    :return: запрос на удаление
    """
    query: str = f'DELETE FROM `{table}` ' \
                 f'WHERE id = {row_id}'
    return query


def delete_class(table: str):
    """
        Удаление таблицы из бд
    :param table: название таблицы
    :return: запрос на удаление
    """
    query: str = f'DROP TABLE `{table}`'
    return query


def create_table_with_relation(title: str, attributes: List[Tuple], parents: list):
    """
        Запрос на создание таблицы
    :param title:
    :param attributes:
    :return:
    """
    for title_row, type_ in attributes:
        if title_row.lower() == 'id':
            break
    else:
        raise print(EXCEPTION_TEXT_CLASS_NO_ID)
    if parents and str(parents[0]).find('object') < 1:
        query: str = f'CREATE TABLE "{title}" (' + \
                     ', '.join(f'"{title_row}" {type_}' for title_row, type_ in attributes) + \
                     f', CONSTRAINT "{title}_{parents[0].__name__.lower()}_id_fk" FOREIGN KEY("id") REFERENCES "{title}"' \
                     f' PRIMARY KEY("id" AUTOINCREMENT)' \
                     ')'
        print(query)
    else:
        query: str = f'CREATE TABLE "{title}" (' + \
                     ', '.join(f'"{title_row}" {type_}' for title_row, type_ in attributes) + \
                     f', PRIMARY KEY("id" AUTOINCREMENT)' \
                     ')'
    return query