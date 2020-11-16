from formatblock import CONNECTED_TOKENS, TOKEN_RULES
from formatter import Formatter
from lexer import Lexer
from tokens import *
import os
from os import listdir
from os.path import isfile, join, splitext
import sys

DEBUG = False

def get_dirs_from_path(dir_path):
    dirs = []
    for f in listdir(dir_path):
        if not isfile(join(dir_path, f)):
            dirs.append(f)
    return dirs
 
 
def get_files_from_path(file_path):
    files = []
    for f in listdir(file_path):
        if isfile(join(file_path, f)):
            f_name, f_ext = splitext(f)
            if f_ext.lower() == '.sql':
                files.append(f)
    return files
 
 
def process(file_name, config_name, action):

    l = Lexer()
    l.parse(file_name)
    f = Formatter()
    f.load_template("template.json", config_name)
    f.format_lexer(l)
    if action == '-v' or action == '--verify' or DEBUG:
        f.print_format_errors('output.log', file_name)
        print("Verify of " + file_name + " is Done")
    if action == '-f' or action == '--format':
        if DEBUG:
            f.create_formatted_file('formatted ' + file_name)
        else:
            f.create_formatted_file(file_name)
        print("Formatting of " + file_name + " is Done")
    del l
    del f
 
 
def process_files_in_dir(path, config_name, action):
    files = get_files_from_path(path)
    for f in files:
        process(join(path, f), config_name, action)
 
 
def process_files_in_project(path, config_name, action):
    process_files_in_dir(path, config_name, action)
    dirs = get_dirs_from_path(path)
    for dir in dirs:
        process_files_in_project(join(path, dir), config_name, action)

if DEBUG:
    process('full.sql', 'MyTemplate', '-f')
else:
    if len(sys.argv) == 2 and sys.argv[1] == '-h' \
        or sys.argv[1] == '--help':
        print("This your help!")
        print("Here you can")
        print("{0:10} : {2:31} {1:30}".format("-h", "/..    -- if you want to see help once more",""))
        print("{0:10} : {2:31} {1:30}".format("--help", "/..    -- if you want to see help once more, but in long way",""))
        print("{0:10} : {1:15} {2:15} {3:15}".format("-v", "template-name", "-(p|d|f)", "/..    -- if you want to verify your file(s)"))
        print("{0:10} : {1:15} {2:15} {3:15}".format("--verify", "template-name", "-(p|d|f)", "/..    -- if you want to verify your file(s), but in long way"))
        print("{0:10} : {1:15} {2:15} {3:15}".format("-f", "template-name", "-(p|d|f)", "/..    -- if you want to fromat your file(s), but in long way"))
        print("{0:10} : {1:15} {2:15} {3:15}".format("--format", "template-name", "-(p|d|f)", "/..    -- if you want to fromat your file(s), but in long way"))
        print("LIBRARY---------------------------------------------------------------------------------------------------")
        print("-p - project")
        print("-d - directory")
        print("-f - file")
        print("/.. - path to project, directory or file")
        print("Remember! template-name has to be in template.json")
    elif len(sys.argv) == 5 and sys.argv[3] == '-p':
        process_files_in_project(sys.argv[4], sys.argv[2], sys.argv[1])
    elif len(sys.argv) == 5 and sys.argv[3] == '-d':
        process_files_in_dir(sys.argv[4], sys.argv[2], sys.argv[1])
    elif len(sys.argv) == 5 and sys.argv[3] == '-f':
        process(sys.argv[4], sys.argv[2], sys.argv[1])
    else:
        print("Incorrect command, please use -h or --help for more details")
