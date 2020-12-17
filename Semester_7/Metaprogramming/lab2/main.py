from lexer import Lexer
from formatter import Formatter
from tokens import *
import os
from os import listdir
from os.path import isfile, join, splitext
import sys

DEBUG = True

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
            if f_ext.lower() == '.cpp':
                files.append(f)
            elif f_ext.lower() == '.hpp':
                files.append(f)
            elif f_ext.lower() == '.c':
                files.append(f)
            elif f_ext.lower() == '.h':
                files.append(f)
    return files
 
 
def process(file_name, action):

    l = Lexer()
    l.parse(file_name)
    if DEBUG:
        l.print_tokens()
        f = Formatter()
        f.change_case(l)
        print('chaned ------------------------------')
        l.print_tokens()
    del l
 
 
def process_files_in_dir(path, action):
    files = get_files_from_path(path)
    for f in files:
        process(join(path, f), action)
 
 
def process_files_in_project(path, action):
    process_files_in_dir(path, action)
    dirs = get_dirs_from_path(path)
    for dir in dirs:
        process_files_in_project(join(path, dir), action)

if DEBUG:
    process('TestProject/main.cpp', '-f')
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
        print("{0:10} : {1:15} {2:15} {3:15}".format("--fix", "template-name", "-(p|d|f)", "/..    -- if you want to fromat your file(s), but in long way"))
        print("LIBRARY---------------------------------------------------------------------------------------------------")
        print("-p - project")
        print("-d - directory")
        print("-f - file")
        print("/.. - path to project, directory or file")
    elif len(sys.argv) == 4 and sys.argv[2] == '-p':
        process_files_in_project(sys.argv[3], sys.argv[1])
    elif len(sys.argv) == 4 and sys.argv[2] == '-d':
        process_files_in_dir(sys.argv[3], sys.argv[1])
    elif len(sys.argv) == 3 and sys.argv[2] == '-f':
        process(sys.argv[2], sys.argv[1])
    else:
        print("Incorrect command, please use -h or --help for more details")
