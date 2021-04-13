{-# LANGUAGE OverloadedStrings #-}
module UIInterface where

import Database.MySQL.Base ( MySQLConn, OK (okAffectedRows), MySQLValue, putTextField )
import qualified Data.Text as T
import qualified Converter as Conv ( readInt, readStr, strToDay, strToInt32, strToDayUIInterface, myToInt32 )
import qualified MySQLConnector as MSQLC ( showTables, Table (addValue, getAllValues, printInfo, deleteValue, updateKeyField, updateField, getValue, drop) )
import qualified StudentsTable as UT ( StudentsInfo( StudentsInfo, tableName, fieldNames, ids, emails, surnames, names ), emptyStudentStruct )
import qualified TeachersTable as AT ( TeachersInfo( TeachersInfo, tableName, fieldNames, ids, emails, names, surnames ), emptyTeacherStruct )
import qualified ProgramsTable as RT ( ProgramsInfo( ProgramsInfo, tableName, fieldNames, ids, names, types, descriptions, links, purposes, releaseDate, programSize, system_requirements, rating ), emptyProgramStruct )
import qualified TeachersToPrograms as A2RT ( TeacherToPrograms ( TeacherToPrograms, tableName, fieldNames, ids, teacherIds, programIds ), emptyTeacherToProgramStruct, getTeacherId, getProgramId )
import qualified StudentsToPrograms as U2RT ( StudentToPrograms ( StudentToPrograms, tableName, fieldNames, ids, studentIds, programIds, usageStart ), emptyStudentToProgramStruct, getStudentId )

mainMenu :: String
mainMenu = "main"

subMenu :: String
subMenu = "sub_menu"

subMenuForConnectors :: String
subMenuForConnectors = "sub_menu_for_connectors"

studentUpdateM :: String
studentUpdateM = "student_update_menu"

teacherUpdateM :: String
teacherUpdateM = "teacher_update_menu"

teacherShowM :: String
teacherShowM = "teacher_show_menu"

programUpdateM :: String
programUpdateM = "program_update_menu"

programShowM :: String
programShowM = "program_show_menu"

teacher2ReShowM :: String 
teacher2ReShowM = "teacher_2_program_show_menu"

student2ReShowM :: String 
student2ReShowM = "student_2_program_show_menu"

menu :: String -> String -> String
menu menuType tableName
    | menuType == mainMenu   = "Input with which table you want to work:\
                            \\n\t1 - students,\
                            \\n\t2 - teachers,\
                            \\n\t3 - programs,\
                            \\n\t4 - teacher to program,\
                            \\n\t5 - student to program,\
                            \\n\t-1 - close db."
    | menuType == subMenu    = "Input what you want to do with table \"" ++ tableName ++ "\":\
                            \\n\t1 - add new,\
                            \\n\t2 - remove from table,\
                            \\n\t3 - update value,\
                            \\n\t4 - show all,\
                            \\n\t5 - show by value,\
                            \\n\t-1 - return to main menu."
    | menuType == subMenuForConnectors = "Input what you want to do with table \"" ++ tableName ++ "\":\
                            \\n\t1 - add new,\
                            \\n\t2 - remove from table,\
                            \\n\t3 - show all,\
                            \\n\t4 - show by value,\
                            \\n\t-1 - return to main menu."
    | menuType == studentUpdateM = "Input what you want update in table \"students\":\
                            \\n\t1 - email for 1 student,\
                            \\n\t2 - student name for 1 student,\
                            \\n\t3 - surname for 1 student,\
                            \\n\t-1 - return to table menu."
    | menuType == teacherUpdateM = "Input what you want update in table \"teachers\":\
                            \\n\t1 - email for 1 teacher,\
                            \\n\t2 - surname for 1 teacher,\
                            \\n\t-1 - return to table menu."
    | menuType == teacherShowM = "Input how you want to search in table \"teachers\":\
                            \\n\t1 - by email,\
                            \\n\t2 - by surname,\
                            \\n\t-1 - return to table menu."
    | menuType == programUpdateM = "Input what you want update in table \"programs\":\
                            \\n\t1 - name title for 1 program,\
                            \\n\t2 - link for 1 program,\
                            \\n\t3 - change rating for 1 program,\
                            \\n\t-1 - return to table menu."
    | menuType == programShowM = "Input how you want to search in table \"programs\":\
                            \\n\t1 - by name,\
                            \\n\t2 - by type,\
                            \\n\t3 - by link,\
                            \\n\t-1 - return to table menu."
    | menuType == teacher2ReShowM = "Input how you want to search in table \"teacher_owns\":\
                            \\n\t1 - by teacher email,\
                            \\n\t2 - by program,\
                            \\n\t-1 - return to table menu."
    | menuType == student2ReShowM = "Input how you want to search in table \"student_owns\":\
                            \\n\t1 - by student email,\
                            \\n\t2 - by program,\
                            \\n\t-1 - return to table menu."


intToTableName :: Int -> String
intToTableName value
    | value == 1 = UT.tableName UT.emptyStudentStruct
    | value == 2 = AT.tableName AT.emptyTeacherStruct
    | value == 3 = RT.tableName RT.emptyProgramStruct
    | value == 4 = A2RT.tableName A2RT.emptyTeacherToProgramStruct
    | value == 5 = U2RT.tableName U2RT.emptyStudentToProgramStruct
    | otherwise  = "table not exists"


intToFunc :: String -> Int -> (MySQLConn -> IO ())
intToFunc tableName value
    | value == 1 && tableName == UT.tableName UT.emptyStudentStruct = addStudent
    | value == 2 && tableName == UT.tableName UT.emptyStudentStruct = deleteStudent
    | value == 3 && tableName == UT.tableName UT.emptyStudentStruct = updateStudent
    | value == 4 && tableName == UT.tableName UT.emptyStudentStruct = showAllStudents
    | value == 5 && tableName == UT.tableName UT.emptyStudentStruct = showStudentByEmail

    | value == 1 && tableName == AT.tableName AT.emptyTeacherStruct = addTeacher
    | value == 2 && tableName == AT.tableName AT.emptyTeacherStruct = deleteTeacher
    | value == 3 && tableName == AT.tableName AT.emptyTeacherStruct = updateTeacher
    | value == 4 && tableName == AT.tableName AT.emptyTeacherStruct = showAllTeachers
    | value == 5 && tableName == AT.tableName AT.emptyTeacherStruct = showTeacherBy

    | value == 1 && tableName == RT.tableName RT.emptyProgramStruct = addProgram
    | value == 2 && tableName == RT.tableName RT.emptyProgramStruct = deleteProgram
    | value == 3 && tableName == RT.tableName RT.emptyProgramStruct = updateProgram
    | value == 4 && tableName == RT.tableName RT.emptyProgramStruct = showAllPrograms
    | value == 5 && tableName == RT.tableName RT.emptyProgramStruct = showProgramBy

    | value == 1 && tableName == A2RT.tableName A2RT.emptyTeacherToProgramStruct = addTeacher2Program
    | value == 2 && tableName == A2RT.tableName A2RT.emptyTeacherToProgramStruct = deleteTeacher2Program
    | value == 3 && tableName == A2RT.tableName A2RT.emptyTeacherToProgramStruct = showAllTeacher2Program
    | value == 4 && tableName == A2RT.tableName A2RT.emptyTeacherToProgramStruct = showTeacher2Res

    | value == 1 && tableName == U2RT.tableName U2RT.emptyStudentToProgramStruct = addStudent2Program
    | value == 2 && tableName == U2RT.tableName U2RT.emptyStudentToProgramStruct = deleteStudent2Program
    | value == 3 && tableName == U2RT.tableName U2RT.emptyStudentToProgramStruct = showAllStudent2Program
    | value == 4 && tableName == U2RT.tableName U2RT.emptyStudentToProgramStruct = showStudent2Res
    | otherwise                          = stub

addStudent :: MySQLConn -> IO ()
addStudent conn = do
    email <- Conv.readStr "Input email:\n"
    studentname <- Conv.readStr "Input student name:\n"
    surname <- Conv.readStr "Input surname:\n"
    let table = UT.StudentsInfo {
            UT.tableName = UT.tableName UT.emptyStudentStruct, UT.fieldNames = UT.fieldNames UT.emptyStudentStruct,
            UT.ids = [], UT.emails = [email], UT.surnames = [surname], UT.names = [studentname]
        }
    response <- MSQLC.addValue table conn
    if okAffectedRows response == (-200)
        then putStrLn "### Email is in use (try again next time with another)\n"
        else putStrLn "### Added to table successfully\n"


deleteStudent :: MySQLConn -> IO ()
deleteStudent conn = do
    email <- Conv.readStr "Input email of student to delete:\n"
    let table = UT.StudentsInfo {
            UT.tableName = UT.tableName UT.emptyStudentStruct, UT.fieldNames = UT.fieldNames UT.emptyStudentStruct,
            UT.ids = [], UT.emails = [email], UT.surnames = [], UT.names = []
        }
    response <- MSQLC.deleteValue table conn
    if okAffectedRows response == 0
        then putStrLn "### Email doesn't exist (try again next time with another)\n"
        else putStrLn "### Deleted from table successfully\n"

updateUIInterface :: MySQLConn -> String -> Int -> IO ()
updateUIInterface conn instanceName value = do
    email <- Conv.readStr "Input email of student to update:\n"
    let tableCompare = UT.StudentsInfo {
                UT.tableName = UT.tableName UT.emptyStudentStruct, UT.fieldNames = UT.fieldNames UT.emptyStudentStruct,
                UT.ids = [], UT.emails = [email], UT.surnames = [], UT.names = []
            }
    valueToUpdate <- Conv.readStr "Input new value:\n"
    let tableUpdate
            | value == 1 = UT.StudentsInfo {
                UT.tableName = UT.tableName UT.emptyStudentStruct, UT.fieldNames = UT.fieldNames UT.emptyStudentStruct,
                UT.ids = [], UT.emails = [valueToUpdate], UT.surnames = [], UT.names = []
            }
            | value == 2 = UT.StudentsInfo {
                UT.tableName = UT.tableName UT.emptyStudentStruct, UT.fieldNames = UT.fieldNames UT.emptyStudentStruct,
                UT.ids = [], UT.emails = [], UT.surnames = [], UT.names = [valueToUpdate]
            }
            | otherwise = UT.StudentsInfo {
                UT.tableName = UT.tableName UT.emptyStudentStruct, UT.fieldNames = UT.fieldNames UT.emptyStudentStruct,
                UT.ids = [], UT.emails = [], UT.surnames = [valueToUpdate], UT.names = []
            }
    res <- if value == 1
            then MSQLC.updateKeyField tableUpdate tableCompare conn
            else MSQLC.updateField tableUpdate tableCompare conn
    if okAffectedRows res == -100
        then putStrLn "### Student not exists.\n"
        else if okAffectedRows res == -200
            then putStrLn "### New email is in use\n"
            else putStrLn "### Changed successfully!\n"

updateStudent :: MySQLConn -> IO ()
updateStudent conn =
    actionPrototype conn studentUpdateM (UT.tableName UT.emptyStudentStruct)
        "Exit to table \"students\"!\n" updateUIInterface [1, 3]

showAllStudents :: MySQLConn -> IO ()
showAllStudents conn = do
    allValues <- MSQLC.getAllValues UT.emptyStudentStruct conn
    MSQLC.printInfo allValues conn

showStudentByEmail :: MySQLConn -> IO ()
showStudentByEmail conn = do
    email <- Conv.readStr "Input email to search:\n"
    let tableInfo = UT.StudentsInfo {
                UT.tableName = UT.tableName UT.emptyStudentStruct, UT.fieldNames = UT.fieldNames UT.emptyStudentStruct,
                UT.ids = [], UT.emails = [email], UT.surnames = [], UT.names = []
            }
    res <- MSQLC.getValue tableInfo conn
    MSQLC.printInfo res conn


addTeacher :: MySQLConn -> IO ()
addTeacher conn = do
    email <- Conv.readStr "Input email:\n"
    name <- Conv.readStr "Input name:\n"
    surname <- Conv.readStr "Input surname:\n"
    let table = AT.TeachersInfo {
            AT.tableName = AT.tableName AT.emptyTeacherStruct,
            AT.fieldNames = AT.fieldNames AT.emptyTeacherStruct,
            AT.ids = [], AT.emails = [email], AT.names = [name], AT.surnames = [surname]
        }
    response <- MSQLC.addValue table conn
    if okAffectedRows response == -200
        then putStrLn "### Email is in use (try again next time with another)\n"
        else putStrLn "### Added to table successfully\n"


deleteTeacher :: MySQLConn -> IO ()
deleteTeacher conn = do
    email <- Conv.readStr "Input email of teacher to delete:\n"
    let table = AT.TeachersInfo {
            AT.tableName = AT.tableName AT.emptyTeacherStruct,
            AT.fieldNames = AT.fieldNames AT.emptyTeacherStruct,
            AT.ids = [], AT.emails = [email], AT.names = [], AT.surnames = []
        }
    response <- MSQLC.deleteValue table conn
    if okAffectedRows response == 0
        then putStrLn "### Email doesn't exist (try again next time with another)\n"
        else putStrLn "### Deleted from table successfully\n"

updateTeacherInteraction :: MySQLConn -> String -> Int -> IO ()
updateTeacherInteraction conn instanceName value = do
    email <- Conv.readStr "Input email of teacher to update:\n"
    let tableCompare = AT.TeachersInfo {
            AT.tableName = AT.tableName AT.emptyTeacherStruct,
            AT.fieldNames = AT.fieldNames AT.emptyTeacherStruct,
            AT.ids = [], AT.emails = [email], AT.names = [], AT.surnames = []
        }
    valueToUpdate <- Conv.readStr "Input new value:\n"
    let tableUpdate
            | value == 1 = AT.TeachersInfo {
                AT.tableName = AT.tableName AT.emptyTeacherStruct,
                AT.fieldNames = AT.fieldNames AT.emptyTeacherStruct,
                AT.ids = [], AT.emails = [valueToUpdate], AT.names = [], AT.surnames = []
            }
            | value == 2 = AT.TeachersInfo {
                AT.tableName = AT.tableName AT.emptyTeacherStruct,
                AT.fieldNames = AT.fieldNames AT.emptyTeacherStruct,
                AT.ids = [], AT.emails = [], AT.names = [], AT.surnames = [valueToUpdate]
            }
    res <- if value == 1
            then MSQLC.updateKeyField tableUpdate tableCompare conn
            else MSQLC.updateField tableUpdate tableCompare conn
    if okAffectedRows res == -100
        then putStrLn "### Student not exists.\n"
        else if okAffectedRows res == -200
            then putStrLn "### New email is in use\n"
            else putStrLn "### Changed successfully!\n"

updateTeacher :: MySQLConn -> IO ()
updateTeacher conn =
    actionPrototype conn teacherUpdateM (AT.tableName AT.emptyTeacherStruct)
        "Exit to table \"teachers\"!\n" updateTeacherInteraction [1, 2]

showAllTeachers :: MySQLConn -> IO ()
showAllTeachers conn = do
    allValues <- MSQLC.getAllValues AT.emptyTeacherStruct conn
    MSQLC.printInfo allValues conn

showTeacherInteraction :: MySQLConn -> String -> Int -> IO ()
showTeacherInteraction conn instanceName value = do
    valueToSearch <- Conv.readStr "Input value to search:\n"
    let tableInfo
            | value == 1 = AT.TeachersInfo {
                AT.tableName = AT.tableName AT.emptyTeacherStruct,
                AT.fieldNames = AT.fieldNames AT.emptyTeacherStruct,
                AT.ids = [], AT.emails = [valueToSearch], AT.names = [], AT.surnames = []
            }
            | value == 2 = AT.TeachersInfo {
                AT.tableName = AT.tableName AT.emptyTeacherStruct,
                AT.fieldNames = AT.fieldNames AT.emptyTeacherStruct,
                AT.ids = [], AT.emails = [], AT.names = [], AT.surnames = [valueToSearch]
            }
    res <- MSQLC.getValue tableInfo conn
    MSQLC.printInfo res conn

showTeacherBy :: MySQLConn -> IO ()
showTeacherBy conn =
    actionPrototype conn teacherShowM (AT.tableName AT.emptyTeacherStruct)
        "Exit to table \"teachers\"!\n" showTeacherInteraction [1, 2]

addProgram :: MySQLConn -> IO ()
addProgram conn = do
    name <- Conv.readStr "Input name:\n"
    programType <- Conv.readStr "Input type (Web program, Software, etc.):\n"
    descriptions <- Conv.readStr "Input descriptions:\n"
    link <- Conv.readStr "Input link:\n"
    purpose <- Conv.readStr "Input purpose:\n"
    releaseDate <- Conv.readStr "Input release date (%Y-%m-%d):\n"
    programSize <- Conv.readStr "Input program size (mb):\n"
    system_requirements <- Conv.readStr "Input system requirements:\n"
    rating <- Conv.readStr "Input rating:\n"
    let table = RT.ProgramsInfo {
            RT.tableName = RT.tableName RT.emptyProgramStruct,
            RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
            RT.ids = [], RT.names = [name], RT.types = [programType], RT.descriptions = [descriptions],
            RT.links = [link], RT.purposes = [purpose], RT.releaseDate = [Conv.strToDayUIInterface releaseDate],
            RT.programSize = [Conv.strToInt32 programSize], RT.system_requirements = [system_requirements],
            RT.rating = [Conv.strToInt32 rating]
        }
    response <- MSQLC.addValue table conn
    if okAffectedRows response == -200
        then putStrLn "### Article name is in use (try again next time with another)\n"
        else putStrLn "### Added to table successfully\n"


deleteProgram :: MySQLConn -> IO ()
deleteProgram conn = do
    name <- Conv.readStr "Input article name of program to delete:\n"
    let table = RT.ProgramsInfo {
            RT.tableName = RT.tableName RT.emptyProgramStruct,
            RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
            RT.ids = [], RT.names = [name], RT.types = [], RT.descriptions = [], RT.links = [],
            RT.purposes = [], RT.releaseDate = [], RT.programSize = [], RT.system_requirements = [], RT.rating = []
        }
    response <- MSQLC.deleteValue table conn
    if okAffectedRows response == 0
        then putStrLn "### Article name doesn't exist (try again next time with another)\n"
        else putStrLn "### Deleted from table successfully\n"

updateProgramInteraction :: MySQLConn -> String -> Int -> IO ()
updateProgramInteraction conn instanceName value = do
    name <- Conv.readStr "Input name of programs to update:\n"
    let tableCompare = RT.ProgramsInfo {
            RT.tableName = RT.tableName RT.emptyProgramStruct,
            RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
            RT.ids = [], RT.names = [name], RT.types = [], RT.descriptions = [], RT.links = [],
            RT.purposes = [], RT.releaseDate = [], RT.programSize = [], RT.system_requirements = [], RT.rating = []
        }
    valueToUpdate <- Conv.readStr "Input new value:\n"
    let tableUpdate
            | value == 1 = RT.ProgramsInfo {
                RT.tableName = RT.tableName RT.emptyProgramStruct,
                RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
                RT.ids = [], RT.names = [valueToUpdate], RT.types = [], RT.descriptions = [], RT.links = [],
                RT.purposes = [], RT.releaseDate = [], RT.programSize = [], RT.system_requirements = [], RT.rating = []
            }
            | value == 2 = RT.ProgramsInfo {
                RT.tableName = RT.tableName RT.emptyProgramStruct,
                RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
                RT.ids = [], RT.names = [], RT.types = [], RT.descriptions = [], RT.links = [valueToUpdate],
                RT.purposes = [], RT.releaseDate = [], RT.programSize = [], RT.system_requirements = [], RT.rating = []
            }
            | value == 3 = RT.ProgramsInfo {
                RT.tableName = RT.tableName RT.emptyProgramStruct,
                RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
                RT.ids = [], RT.names = [], RT.types = [], RT.descriptions = [], RT.links = [],
                RT.purposes = [], RT.releaseDate = [], RT.programSize = [], RT.system_requirements = [],
                RT.rating = [Conv.strToInt32 valueToUpdate]
            }

    res <- if value == 1
            then MSQLC.updateKeyField tableUpdate tableCompare conn
            else MSQLC.updateField tableUpdate tableCompare conn
    if okAffectedRows res == -100
        then putStrLn "### Program not exists.\n"
        else if okAffectedRows res == -200
            then putStrLn "### New program name is in use\n"
            else putStrLn "### Changed successfully!\n"

updateProgram :: MySQLConn -> IO ()
updateProgram conn =
    actionPrototype conn programUpdateM (RT.tableName RT.emptyProgramStruct)
        "Exit to table \"programs\"!\n" updateProgramInteraction [1, 3]

showAllPrograms :: MySQLConn -> IO ()
showAllPrograms conn = do
    allValues <- MSQLC.getAllValues RT.emptyProgramStruct conn
    MSQLC.printInfo allValues conn

showProgramByInteraction :: MySQLConn -> String -> Int -> IO ()
showProgramByInteraction conn instanceName value = do
    valueToSearch <- Conv.readStr "Input value to search:\n"
    let tableInfo
            | value == 1 = RT.ProgramsInfo {
                RT.tableName = RT.tableName RT.emptyProgramStruct,
                RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
                RT.ids = [], RT.names = [valueToSearch], RT.types = [], RT.descriptions = [], RT.links = [],
                RT.purposes = [], RT.releaseDate = [], RT.programSize = [], RT.system_requirements = [], RT.rating = []
            }
            | value == 2 = RT.ProgramsInfo {
                RT.tableName = RT.tableName RT.emptyProgramStruct,
                RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
                RT.ids = [], RT.names = [], RT.types = [valueToSearch], RT.descriptions = [], RT.links = [],
                RT.purposes = [], RT.releaseDate = [], RT.programSize = [], RT.system_requirements = [], RT.rating = []
            }
            | value == 3 = RT.ProgramsInfo {
                RT.tableName = RT.tableName RT.emptyProgramStruct,
                RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
                RT.ids = [], RT.names = [], RT.types = [], RT.descriptions = [], RT.links = [valueToSearch],
                RT.purposes = [], RT.releaseDate = [], RT.programSize = [], RT.system_requirements = [],
                RT.rating = []
            }

    res <- MSQLC.getValue tableInfo conn
    MSQLC.printInfo res conn

showProgramBy :: MySQLConn -> IO ()
showProgramBy conn =
    actionPrototype conn programShowM (RT.tableName RT.emptyProgramStruct)
        "Exit to table \"programs\"!\n" showProgramByInteraction [1, 3]


addTeacher2Program :: MySQLConn -> IO ()
addTeacher2Program conn = do
    email <- Conv.readStr "Input teacher email:\n"
    name <- Conv.readStr "Input program name:\n"
    teacherId <- A2RT.getTeacherId email conn
    nameId <- A2RT.getProgramId name conn
    if teacherId == (-1)
    then putStrLn "### Teacher doesn't exist\n"
    else if nameId == (-1)
    then putStrLn "### Program doesn't exist\n"
    else do
        let table = A2RT.TeacherToPrograms {
                A2RT.tableName = A2RT.tableName A2RT.emptyTeacherToProgramStruct,
                A2RT.fieldNames = A2RT.fieldNames A2RT.emptyTeacherToProgramStruct,
                A2RT.ids = [], A2RT.teacherIds = [teacherId], A2RT.programIds = [nameId]
            }
        response <- MSQLC.addValue table conn
        if okAffectedRows response == -200
            then putStrLn "### Record already exists (try again next time with another)\n"
            else putStrLn "### Added to table successfully\n"


deleteTeacher2Program :: MySQLConn -> IO ()
deleteTeacher2Program conn = do
    email <- Conv.readStr "Input email of teacher to delete:\n"
    name <- Conv.readStr "Input name of program to delete:\n"
    teacherId <- A2RT.getTeacherId email conn
    nameId <- A2RT.getProgramId name conn
    if teacherId == (-1)
    then putStrLn "### Teacher doesn't exist\n"
    else if nameId == (-1)
    then putStrLn "###  Program doesn't exist\n"
    else do
        let table = A2RT.TeacherToPrograms {
                    A2RT.tableName = A2RT.tableName A2RT.emptyTeacherToProgramStruct,
                    A2RT.fieldNames = A2RT.fieldNames A2RT.emptyTeacherToProgramStruct,
                    A2RT.ids = [], A2RT.teacherIds = [teacherId], A2RT.programIds = [nameId]
                }
        response <- MSQLC.deleteValue table conn
        if okAffectedRows response == 0
            then putStrLn "### Record doesn't exist (try again next time with another)\n"
            else putStrLn "### Deleted from table successfully\n"

showAllTeacher2Program :: MySQLConn -> IO ()
showAllTeacher2Program conn = do
    allValues <- MSQLC.getAllValues A2RT.emptyTeacherToProgramStruct conn
    MSQLC.printInfo allValues conn

showTeacher2ResInteraction :: MySQLConn -> String -> Int -> IO ()
showTeacher2ResInteraction conn instanceName value = do
    valueToUpdate <- Conv.readStr "Input value to search:\n"
    res <- if value == 1 
            then A2RT.getTeacherId valueToUpdate conn
            else A2RT.getProgramId valueToUpdate conn
    let tableInfo
            | value == 1 = A2RT.TeacherToPrograms {
                    A2RT.tableName = A2RT.tableName A2RT.emptyTeacherToProgramStruct,
                    A2RT.fieldNames = A2RT.fieldNames A2RT.emptyTeacherToProgramStruct,
                    A2RT.ids = [], A2RT.teacherIds = [res], A2RT.programIds = []
                }
            | value == 2 = A2RT.TeacherToPrograms {
                    A2RT.tableName = A2RT.tableName A2RT.emptyTeacherToProgramStruct,
                    A2RT.fieldNames = A2RT.fieldNames A2RT.emptyTeacherToProgramStruct,
                    A2RT.ids = [], A2RT.teacherIds = [], A2RT.programIds = [res]
                }
    res <- MSQLC.getValue tableInfo conn
    MSQLC.printInfo res conn

showTeacher2Res :: MySQLConn -> IO ()
showTeacher2Res conn =
    actionPrototype conn teacher2ReShowM (A2RT.tableName A2RT.emptyTeacherToProgramStruct)
        "Exit to table \"teacher_owns\"!\n" showTeacher2ResInteraction [1, 2]


addStudent2Program :: MySQLConn -> IO ()
addStudent2Program conn = do
    email <- Conv.readStr "Input student email:\n"
    name <- Conv.readStr "Input program name:\n"
    usageSt <- Conv.readStr "Input start day of usage (%Y-%m-d):\n"
    studentId <- U2RT.getStudentId email conn
    nameId <- A2RT.getProgramId name conn
    if studentId == (-1)
    then putStrLn "### Student doesn't exist\n"
    else if nameId == (-1)
    then putStrLn "### Program doesn't exist\n"
    else do
        let table = U2RT.StudentToPrograms {
                U2RT.tableName = U2RT.tableName U2RT.emptyStudentToProgramStruct ,
                U2RT.fieldNames = U2RT.fieldNames U2RT.emptyStudentToProgramStruct,
                U2RT.ids = [], U2RT.studentIds = [studentId], U2RT.programIds = [nameId],
                U2RT.usageStart = [Conv.strToDayUIInterface usageSt]
            }
        response <- MSQLC.addValue table conn
        if okAffectedRows response == -200
            then putStrLn "### Record already exists (try again next time with another)\n"
            else putStrLn "### Added to table successfully\n"


deleteStudent2Program :: MySQLConn -> IO ()
deleteStudent2Program conn = do
    email <- Conv.readStr "Input email of student to delete:\n"
    name <- Conv.readStr "Input name of program to delete:\n"
    studentId <- U2RT.getStudentId email conn
    nameId <- A2RT.getProgramId name conn
    if studentId == (-1)
    then putStrLn "### Student doesn't exist\n"
    else if nameId == (-1)
    then putStrLn "### Program doesn't exist\n"
    else do
        let table = U2RT.StudentToPrograms {
                U2RT.tableName = U2RT.tableName U2RT.emptyStudentToProgramStruct ,
                U2RT.fieldNames = U2RT.fieldNames U2RT.emptyStudentToProgramStruct,
                U2RT.ids = [], U2RT.studentIds = [studentId], U2RT.programIds = [nameId],
                U2RT.usageStart = []
            }
        response <- MSQLC.deleteValue table conn
        if okAffectedRows response == 0
            then putStrLn "### Record doesn't exist (try again next time with another)\n"
            else putStrLn "### Deleted from table successfully\n"

showAllStudent2Program :: MySQLConn -> IO ()
showAllStudent2Program conn = do
    allValues <- MSQLC.getAllValues U2RT.emptyStudentToProgramStruct conn
    MSQLC.printInfo allValues conn

showStudent2ResInteraction :: MySQLConn -> String -> Int -> IO ()
showStudent2ResInteraction conn instanceName value = do
    valueToSearch <- Conv.readStr "Input value to search:\n"
    res <- if value == 1 
            then U2RT.getStudentId valueToSearch conn
            else A2RT.getProgramId valueToSearch conn
    let tableInfo
            | value == 1 = U2RT.StudentToPrograms {
                    U2RT.tableName = U2RT.tableName U2RT.emptyStudentToProgramStruct ,
                    U2RT.fieldNames = U2RT.fieldNames U2RT.emptyStudentToProgramStruct,
                    U2RT.ids = [], U2RT.studentIds = [res], U2RT.programIds = [],
                    U2RT.usageStart = []
                }       
            | value == 2 = U2RT.StudentToPrograms {
                    U2RT.tableName = U2RT.tableName U2RT.emptyStudentToProgramStruct ,
                    U2RT.fieldNames = U2RT.fieldNames U2RT.emptyStudentToProgramStruct,
                    U2RT.ids = [], U2RT.studentIds = [], U2RT.programIds = [res],
                    U2RT.usageStart = []
                }       
    res <- MSQLC.getValue tableInfo conn
    MSQLC.printInfo res conn

showStudent2Res :: MySQLConn -> IO ()
showStudent2Res conn =
    actionPrototype conn student2ReShowM (U2RT.tableName U2RT.emptyStudentToProgramStruct)
        "Exit to table \"student_owns\"!\n" showStudent2ResInteraction [1, 2]

stub :: MySQLConn -> IO ()
stub conn = print =<< MSQLC.showTables conn

dropAll :: MySQLConn -> IO ()
dropAll conn = do
    res <- MSQLC.drop U2RT.emptyStudentToProgramStruct conn
    res <- MSQLC.drop A2RT.emptyTeacherToProgramStruct conn
    res <- MSQLC.drop RT.emptyProgramStruct conn
    res <- MSQLC.drop AT.emptyTeacherStruct conn
    res <- MSQLC.drop UT.emptyStudentStruct conn
    putStrLn "Dropped all"

tableInteraction :: MySQLConn -> String -> Int -> IO ()
tableInteraction conn instanceName value = intToFunc instanceName value conn

subTableAction :: MySQLConn -> String -> Int -> IO ()
subTableAction conn instanceName value = do
    putStrLn ("----- Work with \"" ++ intToTableName value ++ "\" table -----")
    if value < 4
        then actionPrototype conn subMenu (intToTableName value) "Exit to main!\n" tableInteraction [1, 5]
        else actionPrototype conn subMenuForConnectors (intToTableName value) "Exit to main!\n" tableInteraction [1, 4]

action :: MySQLConn -> String -> Maybe Int -> (MySQLConn -> String -> Int -> IO ()) -> [Int] -> IO ()
action conn instanceName value func (x:y:xs) =
    case value of
        Just n -> if (n >= x) && (n <= y)
                    then func conn instanceName n
                    else putStrLn "Wrong input\n"
        Nothing -> putStrLn "Wrong input\n"

actionPrototype :: MySQLConn -> String -> String -> String -> (MySQLConn -> String -> Int -> IO ()) -> [Int]-> IO ()
actionPrototype conn menuType instanceName endString func range = do
    putStrLn (menu menuType instanceName)

    curAction <- Conv.readInt ""
    if curAction == Just (-1)
        then putStrLn endString
        else do
            action conn instanceName curAction func range
            actionPrototype conn menuType instanceName endString func range

doAction :: MySQLConn -> IO ()
doAction conn = actionPrototype conn mainMenu mainMenu "Goodbye!" subTableAction [1, 5]


