{-# LANGUAGE OverloadedStrings #-}
module StudentsTable where

import qualified Data.Text as T ( Text, pack )
import Database.MySQL.Base
import MySQLConnector
import Data.Int (Int32)
import qualified Text.PrettyPrint as TPrettyP ( ($+$), text, vcat, Doc, (<>), render )
import Converter (mergeLists, myToInt32, myToString, genStruct, genMyLine, genRow )

data StudentsInfo = StudentsInfo
    { tableName :: String,
      fieldNames :: [String],
      ids :: [Int32],
      emails :: [String],
      surnames :: [String],
      names :: [String]
    }
    deriving Show

emptyStudentStruct :: StudentsInfo
emptyStudentStruct = StudentsInfo "students" ["student_id", "email", "surname", "name"] [] [] [] []

mergeAll :: StudentsInfo -> [[String]]
mergeAll tableInfo = mergeLists
                        (mergeLists
                            (mergeLists
                                (mergeLists [] id (map show (ids tableInfo)) "" maxVal)
                                id (emails tableInfo) "" maxVal)
                            id (surnames tableInfo) "" maxVal)
                        id (names tableInfo) "" maxVal
                    where maxVal = max (length (ids tableInfo)) 
                                        (max (length (emails tableInfo)) 
                                            (max (length (surnames tableInfo))
                                                    (length (names tableInfo))))

instance Table StudentsInfo where
    getName tableInfo = tableName tableInfo

    getFieldNames tableInfo =
                        [fieldNames tableInfo !! 0 | not (null (ids tableInfo))] ++
                        [fieldNames tableInfo !! 1 | not (null (emails tableInfo))] ++
                        [fieldNames tableInfo !! 2 | not (null (surnames tableInfo))] ++
                        [fieldNames tableInfo !! 3 | not (null (names tableInfo))]

    getFieldValues (StudentsInfo _ _ ids emails surnames names) =
        map MySQLInt32 ids ++
        map (MySQLText . T.pack) emails ++
        map (MySQLText . T.pack) surnames ++
        map (MySQLText . T.pack) names

    getMainFieldTables tableInfo =  StudentsInfo {
            tableName = tableName tableInfo,
            fieldNames = fieldNames tableInfo,
            ids = [],
            emails = emails tableInfo,
            surnames = [],
            names = []
        }

    fromMySQLValues res = do
        vals <- res
        return (StudentsInfo {
            tableName = tableName emptyStudentStruct,
            fieldNames = fieldNames emptyStudentStruct,
            ids = map myToInt32 (genStruct vals 0),
            emails = map myToString (genStruct vals 1),
            surnames = map myToString (genStruct vals 2),
            names = map myToString (genStruct vals 3)
        })

    isEmpty tableInfo = null (ids tableInfo) || null (emails tableInfo) ||
                        null (names tableInfo) || null (surnames tableInfo)

    len tableInfo = fromEnum (not (null (ids tableInfo))) +
                    fromEnum (not (null (emails tableInfo))) +
                    fromEnum (not (null (names tableInfo))) +
                    fromEnum (not (null (surnames tableInfo)))

    printInfo tableInfo _ = putStrLn (TPrettyP.render draw ++ "\n")
        where
            draw :: TPrettyP.Doc
            draw = TPrettyP.text header
                TPrettyP.$+$
                    TPrettyP.text (genMyLine (length header +
                                              7 * length (filter (== '\t') header)))
                TPrettyP.$+$
                    TPrettyP.vcat (map row (mergeAll tableInfo))
                where
                    row t = TPrettyP.text( genRow (fieldNames tableInfo) t id)
                    header = genRow (fieldNames tableInfo) (fieldNames tableInfo) id
