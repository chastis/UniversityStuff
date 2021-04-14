#!/usr/bin/env stack
-- stack --install-ghc runghc

{-# LANGUAGE OverloadedStrings #-}
module Main where

import MySQLConnector ( connectDB, deployDB, closeDB )
import ProgramsTable
import qualified UIInterface as UI ( doAction )


main :: IO ()
main = do

    conn <- connectDB
    
    deployDB conn

    UI.doAction conn

    closeDB conn


