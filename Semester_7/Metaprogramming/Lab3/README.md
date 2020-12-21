# Metaprogramming - Lab3 - Group Project 

### Installing Cmd Utility

If you want to use this program, you should download command line utility

For establishing you need to write in your terminal:

pip install cmdline-Py2SQL=="0.3.0"

Now you can write to the terminal:

Py2SQL

### Warning

You should locate file db.sqlite3 in the same directory where you run cmd line app

### Distribution of duties

| Author | Tasks | 
| --------------- | --------------- | 
| Maryna | Py2SQL.db_connect(db)    |
|  | Py2SQL.db_disconnect()   |
|  | Py2SQL.find_hierarches() |
|  | Py2SQL.create_object(table, id)|
|  | Py2SQL.create_objects(table, fid, lid)|
|  | Py2SQL.create_class(table, module)|
| Bohdan | Py2SQL.db_engine |
| | Py2SQL.db_size |
| | Py2SQL.db_table_structure(table) |
| | Py2SQL.db_table_size(table) |
| | Py2SQL.save_object(object)  |
| | Py2SQL.save_class(class)|
| | Py2SQL.delete_object(object)|
| | Py2SQL.delete_class|
| | Py2SQL.group_by|
| Danial | Py2SQL.db_name |
| | Py2SQL.db_tables |
| | Py2SQL.find_object(table, py_object) |
| | Py2SQL.find_objects_by(table, *attributes)|
| | Py2SQL.find_class(py_class)|
| | Py2SQL.find_classes_by(*attributes) |
| Maxim | Py2SQL.create_hierarchy(table, package) |
| | Py2SQL.delete_hierarchy(root_class) |
| | Py2SQL.save_hierarchy(root_class) |
