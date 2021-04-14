{-# LANGUAGE OverloadedStrings #-}
module MySQLConnector where

import Data.Text as T ( Text )
import Database.MySQL.Base
import qualified System.IO.Streams as Streams
import qualified Data.ByteString.Lazy.Char8 as BtSt ( pack )
import Data.Int
import qualified Converter as Conv ( strToInt32, myToString )

-- connect to database which is started by docker-compose
connectDB :: IO MySQLConn
connectDB =
    connect
        defaultConnectInfo { ciPort = 3306,
                             ciUser = "root",
                             ciPassword = "password",
                             ciDatabase = "new_schema",
                             ciHost = "127.0.0.1"
                            }

-- close connection to database
closeDB :: MySQLConn -> IO ()
closeDB = close

-- translate output results into list of values
getRidOfStream :: IO ([ColumnDef], Streams.InputStream [MySQLValue]) -> IO [[MySQLValue]]
getRidOfStream all = do
    (defs, is) <- all
    Streams.toList is

-- get name of database
getDBName :: MySQLConn -> IO [[MySQLValue]]
getDBName conn = getRidOfStream (query_ conn "SELECT DATABASE();")

-- create tables if they doesn't exist
deployDB :: MySQLConn -> IO [OK]
deployDB conn = executeMany_ conn
    "CREATE TABLE IF NOT EXISTS students ( \
        \student_id INT NOT NULL AUTO_INCREMENT, \
        \email VARCHAR(256) NOT NULL, \
        \surname VARCHAR(256) NOT NULL, \
        \name VARCHAR(256) NOT NULL, \
        \PRIMARY KEY ( student_id ) \
    \); \

    \CREATE TABLE IF NOT EXISTS teachers ( \
        \teacher_id INT NOT NULL AUTO_INCREMENT, \
        \name VARCHAR(256) NOT NULL, \
        \surname VARCHAR(256) NOT NULL, \
        \email VARCHAR(256) NOT NULL, \
        \PRIMARY KEY ( teacher_id ) \
    \); \

    \CREATE TABLE IF NOT EXISTS programs ( \
        \program_id INT NOT NULL AUTO_INCREMENT, \
        \name TEXT NOT NULL, \
        \type TEXT NOT NULL, \
        \description TEXT NOT NULL, \
        \link TEXT NOT NULL, \
        \purpose TEXT NOT NULL, \
        \release_date DATE, \
        \program_size INT NOT NULL, \
        \system_requirements TEXT NOT NULL, \
        \rating INT NOT NULL, \
        \PRIMARY KEY ( program_id ) \ 
    \); \

    \CREATE TABLE IF NOT EXISTS teacher_owns ( \
        \record_id INT NOT NULL AUTO_INCREMENT, \
        \teacher INT NOT NULL, \
        \program INT NOT NULL, \
        \PRIMARY KEY ( record_id ), \
        \FOREIGN KEY ( teacher ) REFERENCES teachers( teacher_id ), \
        \FOREIGN KEY ( program ) REFERENCES programs( program_id ) \
    \); \
    
    \CREATE TABLE IF NOT EXISTS student_owns ( \
        \record_id INT NOT NULL AUTO_INCREMENT, \
        \student INT NOT NULL, \
        \program INT NOT NULL, \
        \usage_start DATE NOT NULL, \
        \PRIMARY KEY ( record_id ), \
        \FOREIGN KEY ( student ) REFERENCES students( student_id ), \
        \FOREIGN KEY ( program ) REFERENCES programs( program_id ) \
    \);"

-- return list of tables
showTables :: MySQLConn -> IO [[MySQLValue]]
showTables conn = getRidOfStream (query_ conn "SHOW TABLES;")

-- convert to query
toQuery :: String -> Query
toQuery = Query . BtSt.pack

-- error status if object not exists
errorOnNotExistence :: OK
errorOnNotExistence = OK (-100) (-100) 0 0

-- error status if object already exists
errorOnExistence :: OK
errorOnExistence = OK (-200) (-200) 0 0

-- generate where query
generateWhere :: [String] -> String
generateWhere [] = ""
generateWhere [x] = x ++ " = ?;"
generateWhere (x:xs) = x ++ " = ? and " ++ generateWhere xs

-- generate where query
generateSet :: [String] -> String
generateSet [] = ""
generateSet [x] = x ++ " = ?"
generateSet (x:xs) = x ++ " = ?, " ++ generateWhere xs

-- generate where query
generateInsert :: [String] -> String
generateInsert [] = " "
generateInsert [x] = x
generateInsert (x:xs) = x ++ ", " ++ generateInsert xs

generateInsertValues :: Int -> String
generateInsertValues n
    | n == 0 = " "
    | n == 1 = "?"
    | n > 1  = "?, " ++ generateInsertValues (n-1)

class Table a where
    getName :: a -> String 
    getFieldNames :: a -> [String] 
    getFieldValues :: a -> [MySQLValue]
    getMainFieldTables :: a -> a
    fromMySQLValues :: IO [[MySQLValue]] -> IO a
    isEmpty :: a -> Bool    
    len :: a -> Int
    printInfo :: a -> MySQLConn -> IO ()

    -- delete table from database
    drop :: a -> MySQLConn -> IO OK
    drop tableInfo conn = execute_ conn (toQuery ("DROP TABLE " ++ getName tableInfo ++ ";"))

    -- get all values from table
    getAllValues :: a -> MySQLConn -> IO a
    getAllValues tableInfo conn =
        fromMySQLValues (getRidOfStream ( query_ conn (toQuery("SELECT * FROM " ++ getName tableInfo ++ ";"))))

    -- get all values from table
    getCountRecord :: a -> MySQLConn -> IO Int32
    getCountRecord tableInfo conn = do
        answer <- getRidOfStream ( query_ conn (toQuery("SELECT COUNT(*) FROM " ++ getName tableInfo ++ ";")))
        return $ Conv.strToInt32 $ Conv.myToString $ head $ head answer

    -- get any value by compare from table
    getValue :: a -> MySQLConn -> IO a 
    getValue tableInfo conn = 
        fromMySQLValues (getRidOfStream (query conn (
            toQuery ("SELECT * FROM " ++ getName tableInfo ++ 
                     " WHERE " ++ generateWhere (getFieldNames tableInfo)))
            (getFieldValues tableInfo)))

    -- update field for any table
    updateField :: a -> a -> MySQLConn -> IO OK
    updateField updateInfo compareInfo conn = do
        vals <- getValue compareInfo conn
        if isEmpty vals
        then return errorOnNotExistence
        else execute conn (toQuery (
            "UPDATE " ++ getName updateInfo ++ " \
            \SET " ++ generateSet (getFieldNames updateInfo) ++ " \
            \WHERE " ++ generateWhere (getFieldNames compareInfo) ++";"))
            (getFieldValues updateInfo ++ getFieldValues compareInfo)

    -- update field for key in any table
    updateKeyField :: a -> a -> MySQLConn -> IO OK
    updateKeyField updateInfo compareInfo conn = do
        vals <- getValue compareInfo conn
        valsNew <- getValue updateInfo conn
        if isEmpty vals
        then return errorOnNotExistence
        else if not (isEmpty valsNew)
            then return errorOnExistence
            else execute conn (toQuery (
                "UPDATE " ++ getName updateInfo ++ " \
                \SET " ++ generateSet (getFieldNames updateInfo) ++ " \
                \WHERE " ++ generateWhere (getFieldNames compareInfo) ++";"))
                (getFieldValues updateInfo ++ getFieldValues compareInfo)

    -- add value to table
    addValue :: a -> MySQLConn -> IO OK
    addValue tableInfo conn = do
        vals <- getValue (getMainFieldTables tableInfo) conn        
        if isEmpty vals
        then execute conn
                (toQuery ("INSERT INTO " ++ getName tableInfo ++ 
                            " (" ++ generateInsert (getFieldNames tableInfo) ++ ") " ++
                        "VALUES (" ++ generateInsertValues (len tableInfo) ++ ") ;"))
                (getFieldValues tableInfo)
        else return errorOnExistence

    -- delete value from table
    deleteValue :: a -> MySQLConn -> IO OK
    deleteValue tableInfo conn = 
        execute conn (toQuery ("DELETE FROM " ++ getName tableInfo ++ 
                                " WHERE " ++ generateWhere (getFieldNames tableInfo) ++ ";")) 
                                (getFieldValues tableInfo)
