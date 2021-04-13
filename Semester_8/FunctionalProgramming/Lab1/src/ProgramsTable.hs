{-# LANGUAGE OverloadedStrings #-}
module ProgramsTable where

import qualified Data.Text as T ( Text, pack )
import Database.MySQL.Base
import Data.Time.Calendar as C ( Day )
import MySQLConnector
import Data.Int (Int32)
import qualified Text.PrettyPrint as TPrettyP ( ($+$), text, vcat, Doc, (<>), render )
import Converter (mergeLists, myToInt32, myToString, myToDay, genStruct, genMyLine, genRow )

data ProgramsInfo = ProgramsInfo
    { tableName :: String,
      fieldNames :: [String],
      ids :: [Int32],
      names :: [String],
      types :: [String],
      descriptions :: [String],
      links :: [String],
      purposes :: [String],
      releaseDate :: [C.Day],
      programSize :: [Int32],
      system_requirements :: [String],
      rating :: [Int32]
    }
    deriving Show

emptyProgramStruct :: ProgramsInfo
emptyProgramStruct = ProgramsInfo "programs" 
    ["program_id", "name", "type", "description", "link", "purpose", 
        "release_date", "program_size", "system_requirements", "rating"] 
            [] [] [] [] [] [] [] [] [] []

mergeAll :: ProgramsInfo -> [[String]]
mergeAll tableInfo = mergeLists
    (mergeLists
      (mergeLists
        (mergeLists
          (mergeLists
            (mergeLists
              (mergeLists
                (mergeLists
                  (mergeLists
                    (mergeLists [] id (map show (ids tableInfo)) "" maxVal)
                    id (names tableInfo) "" maxVal)
                  id (types tableInfo) "" maxVal)
                id (descriptions tableInfo) "" maxVal)
              id (links tableInfo) "" maxVal)
            id (purposes tableInfo) "" maxVal)
          id (map show (releaseDate tableInfo)) "" maxVal)
        id (map show (programSize tableInfo)) "" maxVal)
      id (system_requirements tableInfo) "" maxVal)
    id (map show (rating tableInfo)) "" maxVal
    where maxVal = max (length (ids tableInfo)) 
            (max (length (names tableInfo)) 
              (max (length (types tableInfo))
                (max (length (descriptions tableInfo))
                  (max (length (links tableInfo))
                    (max (length (types tableInfo))
                      (max (length (purposes tableInfo))
                        (max (length (releaseDate tableInfo))
                          (max (length (programSize tableInfo))
                            (max (length (system_requirements tableInfo))
                                 (length (rating tableInfo)))))))))))
                    

instance Table ProgramsInfo where
    getName tableInfo = tableName tableInfo

    getFieldNames tableInfo =
                        [fieldNames tableInfo !! 0 | not (null (ids tableInfo))] ++
                        [fieldNames tableInfo !! 1 | not (null (names tableInfo))] ++
                        [fieldNames tableInfo !! 2 | not (null (types tableInfo))] ++
                        [fieldNames tableInfo !! 3 | not (null (descriptions tableInfo))] ++
                        [fieldNames tableInfo !! 4 | not (null (links tableInfo))] ++
                        [fieldNames tableInfo !! 5 | not (null (purposes tableInfo))] ++
                        [fieldNames tableInfo !! 6 | not (null (releaseDate tableInfo))] ++
                        [fieldNames tableInfo !! 7 | not (null (programSize tableInfo))] ++
                        [fieldNames tableInfo !! 8 | not (null (system_requirements tableInfo))] ++
                        [fieldNames tableInfo !! 9 | not (null (rating tableInfo))]

    getFieldValues (ProgramsInfo _ _ ids names typeId description link purpose 
            releaseDate programSize system_requirements rating) =
        map MySQLInt32 ids ++
        map (MySQLText . T.pack) names ++
        map (MySQLText . T.pack) typeId ++
        map (MySQLText . T.pack) description ++
        map (MySQLText . T.pack) link ++
        map (MySQLText . T.pack) purpose ++
        map MySQLDate releaseDate ++
        map MySQLInt32 programSize ++
        map (MySQLText . T.pack) system_requirements ++
        map MySQLInt32 rating

    getMainFieldTables tableInfo = ProgramsInfo {
            tableName = tableName tableInfo,
            fieldNames = fieldNames tableInfo,
            ids = [],
            names = names tableInfo,
            types = [],
            descriptions = [],
            links = [],
            purposes = [],
            releaseDate = [],
            programSize = [],
            system_requirements = [],
            rating = []
        }

    fromMySQLValues res = do
        vals <- res
        return (ProgramsInfo {
            tableName   = tableName emptyProgramStruct,
            fieldNames  = fieldNames emptyProgramStruct,
            ids         = map myToInt32 (genStruct vals 0),
            names       = map myToString (genStruct vals 1),
            types       = map myToString (genStruct vals 2),
            descriptions = map myToString (genStruct vals 3),
            links       = map myToString (genStruct vals 4),
            purposes    = map myToString (genStruct vals 5),
            releaseDate    = map myToDay (genStruct vals 6),
            programSize   = map myToInt32 (genStruct vals 7),
            system_requirements       = map myToString (genStruct vals 8),
            rating  = map myToInt32 (genStruct vals 9)
        })

    isEmpty tableInfo = null (ids tableInfo) || null (names tableInfo) || null (types tableInfo) || 
                        null (descriptions tableInfo) || null (links tableInfo) || null (purposes tableInfo) || 
                        null (releaseDate tableInfo) || null (programSize tableInfo) || null (system_requirements tableInfo) || 
                        null (rating tableInfo)

    len tableInfo = fromEnum (not (null (ids tableInfo))) +
                    fromEnum (not (null (names tableInfo))) +
                    fromEnum (not (null (types tableInfo))) +
                    fromEnum (not (null (descriptions tableInfo))) +
                    fromEnum (not (null (links tableInfo))) +
                    fromEnum (not (null (purposes tableInfo))) +
                    fromEnum (not (null (releaseDate tableInfo))) +
                    fromEnum (not (null (programSize tableInfo))) +
                    fromEnum (not (null (system_requirements tableInfo))) +
                    fromEnum (not (null (rating tableInfo)))

    printInfo tableInfo _ = putStrLn (TPrettyP.render draw ++ "\n")
        where
            draw :: TPrettyP.Doc
            draw = TPrettyP.text header
                TPrettyP.$+$
                    TPrettyP.text (genMyLine (length header +
                                              4 * length (filter (== '\t') header)))
                TPrettyP.$+$
                    TPrettyP.vcat (map row (mergeAll tableInfo))
                where
                    row t = TPrettyP.text( genRow (fieldNames tableInfo) t id)
                    header = genRow (fieldNames tableInfo) (fieldNames tableInfo) id
