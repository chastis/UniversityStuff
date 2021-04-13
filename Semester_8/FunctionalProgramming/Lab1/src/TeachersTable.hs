{-# LANGUAGE OverloadedStrings #-}
module TeachersTable where

import qualified Data.Text as T ( Text, pack )
import Database.MySQL.Base
import MySQLConnector
import Data.Int (Int32)
import qualified Text.PrettyPrint as TPrettyP ( ($+$), text, vcat, Doc, (<>), render )
import Converter (mergeLists, myToInt32, myToString, genStruct, genMyLine, genRow )

data TeachersInfo = TeachersInfo
    { tableName :: String,
      fieldNames :: [String],
      ids :: [Int32],
      names :: [String],
      surnames :: [String],
      emails :: [String]
    }
    deriving Show

emptyTeacherStruct :: TeachersInfo
emptyTeacherStruct = TeachersInfo "teachers" ["teacher_id", "name", "surname", "email"] [] [] [] []

mergeAll :: TeachersInfo -> [[String]]
mergeAll tableInfo = mergeLists
                        (mergeLists
                            (mergeLists
                                (mergeLists [] id (map show (ids tableInfo)) "" maxVal)
                                id (names tableInfo) "" maxVal)
                            id (surnames tableInfo) "" maxVal)
                        id (emails tableInfo) "" maxVal
                    where maxVal = max (length (ids tableInfo)) 
                                        (max (length (names tableInfo)) 
                                            (max (length (surnames tableInfo))
                                                    (length (emails tableInfo))))

                    

instance Table TeachersInfo where
    getName tableInfo = tableName tableInfo

    getFieldNames tableInfo =
                        [fieldNames tableInfo !! 0 | not (null (ids tableInfo))] ++
                        [fieldNames tableInfo !! 1 | not (null (names tableInfo))] ++
                        [fieldNames tableInfo !! 2 | not (null (surnames tableInfo))] ++
                        [fieldNames tableInfo !! 3 | not (null (emails tableInfo))]

    getFieldValues (TeachersInfo _ _ ids names surnames emails) =
        map MySQLInt32 ids ++
        map (MySQLText . T.pack) names ++
        map (MySQLText . T.pack) surnames ++
        map (MySQLText . T.pack) emails

    getMainFieldTables tableInfo = TeachersInfo {
            tableName = tableName tableInfo,
            fieldNames = fieldNames tableInfo,
            ids = [],
            names = [],
            surnames = [],
            emails = emails tableInfo
        }

    fromMySQLValues res = do
        vals <- res
        return (TeachersInfo {
            tableName = tableName emptyTeacherStruct,
            fieldNames = fieldNames emptyTeacherStruct,
            ids = map myToInt32 (genStruct vals 0),
            names = map myToString (genStruct vals 1),
            surnames = map myToString (genStruct vals 2),
            emails = map myToString (genStruct vals 3)
        })

    isEmpty tableInfo = null (ids tableInfo) || null (names tableInfo) || 
                        null (surnames tableInfo) || null (emails tableInfo) 

    len tableInfo = fromEnum (not (null (ids tableInfo))) +
                    fromEnum (not (null (names tableInfo))) +
                    fromEnum (not (null (surnames tableInfo))) +
                    fromEnum (not (null (emails tableInfo)))

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
