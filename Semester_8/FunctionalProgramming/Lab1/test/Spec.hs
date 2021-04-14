
import Test.QuickCheck
import MySQLConnector ( connectDB, deployDB, closeDB, Table (getCountRecord, addValue, deleteValue) )
import Data.Time.Calendar as C ( Day, fromGregorian )
import ProgramsTable
import qualified UIInterface as UI ( doAction )

main :: IO ()
main = do

    conn <- connectDB
    
    deployDB conn
    
    countRecords <- getCountRecord emptyProgramStruct conn

    quickCheck(1 == countRecords)

    let programStruct = ProgramsInfo {
            tableName = tableName emptyProgramStruct,
            fieldNames = fieldNames emptyProgramStruct,
            ids = [],
            names = ["a"],
            types = ["a"],
            descriptions = ["a"],
            links = ["a"],
            purposes = ["a"],
            releaseDate = [C.fromGregorian 2000 9 12],
            programSize = [42],
            system_requirements = ["a"],
            rating = [5]
        }

    addValue programStruct conn
    
    newCountRecords <- getCountRecord emptyProgramStruct conn

    quickCheck(2 == newCountRecords)

    deleteValue programStruct conn

    newNewCountRecords <- getCountRecord emptyProgramStruct conn

    quickCheck(1 == newNewCountRecords)

    closeDB conn
