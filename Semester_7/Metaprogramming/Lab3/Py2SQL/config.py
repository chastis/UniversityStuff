DB_FILENAME = 'db.sqlite3'

SUPPORTED_TYPES = {'str': 'TEXT',
                   'int': 'INTEGER',
                   'float': 'REAL'}

REVERSE_SUPPORTED_TYPES = {'TEXT': 'str',
                           'INTEGER': 'int',
                           'REAL': 'float'}

EXCEPTION_TEXT_NO_TABLE = 'Введенной таблицы не найдено.'
EXCEPTION_TEXT_NO_TABLE_WITH_THESE_ATTRS = 'Таблицы с эквивалетными параметрами не найдено.'
EXCEPTION_TEXT_NO_RECORD = 'Запись с заданными параметрами не найдена.'
EXCEPTION_TEXT_NO_ID = 'У объекта нет поля id.'
EXCEPTION_TEXT_CLASS_NO_ID = 'У класса нет поля id.'
EXCEPTION_TEXT_CLASS_EXIST = 'Идентичный класс уже присутствует в Базе Данных.'
RECORD_INSERT = 'Запись добавлена.'
RECORD_UPDATE = 'Запись обновлена.'
TABLE_WAS_CREATED = 'Таблица создана.'
TABLE_WAS_UPDATED = 'Таблица была пересоздана.'
RECORD_WAS_DELETED = 'Запись была удалена.'
TABLE_WAS_DELETED = 'Таблица успешно удалена.'
HIERARH_WAS_CREATED = 'Связка таблиц была построена.'
MODULE_WAS_CREATED = 'Модуль был успешно создан.'
HIERARH_WAS_CREATED_IN_PY = 'Модуль построен по иерархии'