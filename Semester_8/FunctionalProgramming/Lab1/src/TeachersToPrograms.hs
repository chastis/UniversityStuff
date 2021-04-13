{-# LANGUAGE OverloadedStrings #-}
module TeachersToPrograms where

import qualified Data.Text as T ( Text, pack )
import Database.MySQL.Base
import MySQLConnector
import Data.Int (Int32)
import qualified Text.PrettyPrint as TPrettyP ( ($+$), text, vcat, Doc, (<>), render )
import Converter (mergeLists, myToInt32, myToString, genStruct, genMyLine, genRow )

import qualified TeachersTable as AT
import qualified ProgramsTable as RT


data TeacherToPrograms = TeacherToPrograms
    { tableName :: String,
      fieldNames :: [String],
      ids :: [Int32],
      teacherIds :: [Int32],
      programIds :: [Int32]
    }
    deriving Show

emptyTeacherToProgramStruct :: TeacherToPrograms
emptyTeacherToProgramStruct =
    TeacherToPrograms "teacher_owns" ["record_id", "teacher", "program"] [] [] []

getTeacherEmail :: Int32 -> MySQLConn -> IO String
getTeacherEmail value conn = do
    res <- getValue (AT.TeachersInfo  {
            AT.tableName = AT.tableName AT.emptyTeacherStruct,
            AT.fieldNames = AT.fieldNames AT.emptyTeacherStruct,
            AT.ids = [value],
            AT.names = [],
            AT.surnames = [],
            AT.emails = []
    }) conn
    return (head (AT.emails res))

getTeacherId :: String -> MySQLConn -> IO Int32
getTeacherId value conn = do
    res <- getValue (AT.TeachersInfo  {
            AT.tableName = AT.tableName AT.emptyTeacherStruct,
            AT.fieldNames = AT.fieldNames AT.emptyTeacherStruct,
            AT.ids = [],
            AT.names = [],
            AT.surnames = [],
            AT.emails = [value]
    }) conn
    if not (null (AT.ids res))
        then return (head (AT.ids res))
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

getProgramId :: String -> MySQLConn -> IO Int32
getProgramId value conn = do
    res <- getValue (RT.ProgramsInfo {
            RT.tableName = RT.tableName RT.emptyProgramStruct,
            RT.fieldNames = RT.fieldNames RT.emptyProgramStruct,
            RT.ids = [],
            RT.names = [value],
            RT.types = [],
            RT.descriptions = [],
            RT.links = [],
            RT.purposes = [],
            RT.releaseDate = [],
            RT.programSize = [],
            RT.system_requirements = [],
            RT.rating = []
    }) conn
    if not (null (RT.ids res))
        then return (head (RT.ids res))
        else return (-1)

listIdsToListVals :: [Int32] -> MySQLConn -> (Int32 -> MySQLConn -> IO String) -> IO [String]
listIdsToListVals [] conn func = return []
listIdsToListVals (x:xs) conn func = do
    res <- listIdsToListVals xs conn func
    newValue <- func x conn
    return (newValue : res)

mergeAll :: TeacherToPrograms -> MySQLConn -> IO [[String]]
mergeAll tableInfo conn = do 
        emailList <- listIdsToListVals (teacherIds tableInfo) conn getTeacherEmail
        programNameList <- listIdsToListVals (programIds tableInfo) conn getProgramName
        return (mergeLists
                (mergeLists
                    (mergeLists [] id (map show (ids tableInfo)) "" maxVal)
                    id emailList "" maxVal)
                id programNameList "" maxVal)
                where maxVal = max (length (ids tableInfo))
                                    (max (length (teacherIds tableInfo))
                                        (length (programIds tableInfo)))

instance Table TeacherToPrograms where
    getName tableInfo = tableName tableInfo

    getFieldNames tableInfo =
                        [fieldNames tableInfo !! 0 | not (null (ids tableInfo))] ++
                        [fieldNames tableInfo !! 1 | not (null (teacherIds tableInfo))] ++
                        [fieldNames tableInfo !! 2 | not (null (programIds tableInfo))]

    getFieldValues (TeacherToPrograms _ _ ids teacherIds programIds) =
        map MySQLInt32 ids ++
        map MySQLInt32 teacherIds ++
        map MySQLInt32 programIds

    getMainFieldTables tableInfo =  TeacherToPrograms {
            tableName = tableName tableInfo,
            fieldNames = fieldNames tableInfo,
            ids = [],
            teacherIds = teacherIds tableInfo,
            programIds = programIds tableInfo
        }

    fromMySQLValues res = do
        vals <- res
        return (TeacherToPrograms {
            tableName = tableName emptyTeacherToProgramStruct,
            fieldNames = fieldNames emptyTeacherToProgramStruct,
            ids = map myToInt32 (genStruct vals 0),
            teacherIds = map myToInt32 (genStruct vals 1),
            programIds = map myToInt32 (genStruct vals 2)
        })

    isEmpty tableInfo = null (ids tableInfo) || null (teacherIds tableInfo) || null (programIds tableInfo)

    len tableInfo = fromEnum (not (null (ids tableInfo))) +
                    fromEnum (not (null (teacherIds tableInfo))) +
                    fromEnum (not (null (programIds tableInfo)))

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
