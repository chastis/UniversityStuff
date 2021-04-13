{-# LANGUAGE OverloadedStrings #-}
module StudentsToPrograms where

import qualified Data.Text as T ( Text, pack )
import qualified Data.Time.Calendar as C ( Day )
import Database.MySQL.Base
import MySQLConnector
import Data.Int (Int32)
import qualified Text.PrettyPrint as TPrettyP ( ($+$), text, vcat, Doc, (<>), render )
import Converter (mergeLists, myToInt32, myToString, genStruct, genMyLine, genRow, myToDay )

import qualified StudentsTable as UT
import qualified ProgramsTable as RT


data StudentToPrograms = StudentToPrograms
    { tableName :: String,
      fieldNames :: [String],
      ids :: [Int32],
      studentIds :: [Int32],
      programIds :: [Int32],
      usageStart :: [C.Day]
    }
    deriving Show

emptyStudentToProgramStruct :: StudentToPrograms
emptyStudentToProgramStruct =
    StudentToPrograms "student_owns" ["record_id", "student", "program", "usage_start"] [] [] [] []

getStudentEmail :: Int32 -> MySQLConn -> IO String
getStudentEmail value conn = do
    res <- getValue (UT.StudentsInfo {
            UT.tableName = UT.tableName UT.emptyStudentStruct,
            UT.fieldNames = UT.fieldNames UT.emptyStudentStruct,
            UT.ids = [value],
            UT.emails = [],
            UT.surnames = [],
            UT.names = []
    }) conn
    return (head (UT.emails res))

getStudentId :: String -> MySQLConn -> IO Int32
getStudentId value conn = do
    res <- getValue (UT.StudentsInfo {
            UT.tableName = UT.tableName UT.emptyStudentStruct,
            UT.fieldNames = UT.fieldNames UT.emptyStudentStruct,
            UT.ids = [],
            UT.emails = [value],
            UT.surnames = [],
            UT.names = []
    }) conn
    if not (null (UT.ids res))
        then return (head (UT.ids res))
        else return (-1)

getProgramName :: Int32 -> MySQLConn -> IO String
getProgramName value conn = do
    res <- getValue (RT.ProgramsInfo {
            RT.tableName = RT.tableName RT.emptyProgramStruct,
            RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
            RT.ids = [value],
            RT.names = [],
            RT.types = [],
            RT.descriptions = [],
            RT.links = [],
            RT.purposes = [],
            RT.releaseDate = [],
            RT.programSize = [],
            RT.system_requirements = [],
            RT.rating = []
    }) conn
    return (head (RT.names res))

listIdsToListVals :: [Int32] -> MySQLConn -> (Int32 -> MySQLConn -> IO String) -> IO [String]
listIdsToListVals [] _ _ = return []
listIdsToListVals (x:xs) conn func = do
    res <- listIdsToListVals xs conn func
    newValue <- func x conn
    return (newValue : res)

mergeAll :: StudentToPrograms -> MySQLConn -> IO [[String]]
mergeAll tableInfo conn = do 
        emailList <- listIdsToListVals (studentIds tableInfo) conn getStudentEmail
        programNameList <- listIdsToListVals (programIds tableInfo) conn getProgramName
        return (mergeLists
                    (mergeLists
                        (mergeLists
                            (mergeLists [] id (map show (ids tableInfo)) "" maxVal)
                            id emailList "" maxVal)
                        id programNameList "" maxVal)
                    id (map show (usageStart tableInfo)) "" maxVal )
                where maxVal = max (length (ids tableInfo))
                                    (max (length (studentIds tableInfo))
                                        (max (length (programIds tableInfo))
                                              (length (usageStart tableInfo))))

instance Table StudentToPrograms where
    getName tableInfo = tableName tableInfo

    getFieldNames tableInfo =
                        [fieldNames tableInfo !! 0 | not (null (ids tableInfo))] ++
                        [fieldNames tableInfo !! 1 | not (null (studentIds tableInfo))] ++
                        [fieldNames tableInfo !! 2 | not (null (programIds tableInfo))] ++ 
                        [fieldNames tableInfo !! 3 | not (null (usageStart tableInfo))]

    getFieldValues (StudentToPrograms _ _ ids studentIds programIds usageStart) =
        map MySQLInt32 ids ++
        map MySQLInt32 studentIds ++
        map MySQLInt32 programIds ++
        map MySQLDate usageStart

    getMainFieldTables tableInfo =  StudentToPrograms {
            tableName = tableName tableInfo,
            fieldNames = fieldNames tableInfo,
            ids = [],
            studentIds = studentIds tableInfo,
            programIds = programIds tableInfo,
            usageStart = []
        }

    fromMySQLValues res = do
        vals <- res
        return (StudentToPrograms {
            tableName = tableName emptyStudentToProgramStruct,
            fieldNames = fieldNames emptyStudentToProgramStruct,
            ids = map myToInt32 (genStruct vals 0),
            studentIds = map myToInt32 (genStruct vals 1),
            programIds = map myToInt32 (genStruct vals 2),
            usageStart = map myToDay (genStruct vals 3)
        })

    isEmpty tableInfo = null (ids tableInfo) || null (studentIds tableInfo) || 
                        null (programIds tableInfo) || null (usageStart tableInfo)

    len tableInfo = fromEnum (not (null (ids tableInfo))) +
                    fromEnum (not (null (studentIds tableInfo))) +
                    fromEnum (not (null (programIds tableInfo))) +
                    fromEnum (not (null (usageStart tableInfo)))

    printInfo tableInfo conn = do
        merged <- mergeAll tableInfo conn
        putStrLn (TPrettyP.render (draw merged) ++ "\n")
        where
            draw ::[[String]] -> TPrettyP.Doc
            draw allRows = TPrettyP.text header
                TPrettyP.$+$
                    TPrettyP.text (genMyLine (length header +
                                              7 * length (filter (== '\t') header)))
                TPrettyP.$+$
                    TPrettyP.vcat (map row allRows)
                where
                    row t = TPrettyP.text( genRow (fieldNames tableInfo) t id)
                    header = genRow (fieldNames tableInfo) (fieldNames tableInfo) id
