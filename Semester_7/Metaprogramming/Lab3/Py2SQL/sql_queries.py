GET_TABLES = """SELECT `name` 
                FROM `sqlite_master`
                WHERE `type`='table'
                ORDER BY `name`"""


def GET_TABLE_INFO(table: str):
    return 'SELECT `cid`, ' \
           '       `name`, ' \
           '       `type` ' \
           f'FROM pragma_table_info("{table}")'


def GET_RELATIONS(table: str):
    return 'SELECT `table` ' \
           f'FROM pragma_foreign_key_list("{table}")'

def DROP_TABLE(table: str):
    return f'DROP TABLE `{table}`'