module Lib where

-- calculates one block of the rieman function

-- calculates one block of the rieman function
import GHC.Conc.Sync (par, pseq, numCapabilities)

riemanBlock :: Double -> Double -> (Double -> Double) -> Double
riemanBlock intA intB f
  | intA > intB     = riemanBlock intB intA f
  | otherwise       = (f intA + f intB) / 2.0 * (intB-intA) 

-- iterates over all blocks of the rieman sum and gives a list of block sizes
-- riemanIterator :: [Double] -> (Double -> Double) -> [Double]
-- riemanIterator [a] _ = []
-- riemanIterator (p:q:ps) f = (riemanBlock p q f) : (riemanIterator (q:ps) f)



-- iterates over all blocks of the rieman sum and gives a list of block sizes
riemanIteratorPar :: [Double] -> (Double -> Double) -> Bool -> Int -> [Double]
riemanIteratorPar [a] _ _ _ = []
riemanIteratorPar (p:q:ps) f paral num
    | paral && num <= numCapabilities = tailR `par` (forceElem headR `pseq` (headR : tailR))
    | otherwise = headR:tailR
    where 
        headR = riemanBlock p q f 
        tailR = riemanIteratorPar (q:ps) f paral (num + 1)

riemanIterator :: [Double] -> (Double -> Double) -> [Double]
riemanIterator [a] _ = []
riemanIterator (p:q:ps) f = (riemanBlock p q f) : (riemanIterator (q:ps) f)

forceElem :: a -> ()
forceElem x = x `pseq` ()

force :: [a] -> ()
force [] = ()
force (x:xs) = x `pseq` force xs

riemanDivide :: [Double] -> (Double -> Double) -> Int -> [Double]
riemanDivide list f ind
    | ind <= numCapabilities = force resultPartList `par` nextIteration `pseq` (resultPartList ++ nextIteration)  
    | otherwise              = []
    where 
        headElements = length list `div` (numCapabilities - ind + 1)
        partList = take headElements list
        resultPartList = riemanIterator partList f
        nextIteration = riemanDivide (drop (headElements - 1) list) f (ind+1)

-- calculates the rieman sum for the given partition
riemanSum :: [Double] -> (Double -> Double) -> Bool -> Double
riemanSum partition f paral = sum (riemanIteratorPar partition f paral 1)

-- creates a partition of a given interval with n sub-intervals
createPartition :: (Double, Double) -> Double -> [Double]
createPartition (intA, intB) n
  | intA > intB = createPartition (intB, intA) n
  | otherwise   = [intA, intA+(intB-intA)/n .. intB]

-- this does all the work, calculate riemanSums over more and more finely divided partitions until the difference between this one and the last one is below prec
integralIterator :: Double -> Double -> (Double, Double) -> (Double -> Double) -> Double -> Bool -> Double
integralIterator lastInt lastN (intA, intB) f prec paral
  | prec > abs (lastInt - currentInt) = currentInt
  | otherwise                         = integralIterator currentInt currentN (intA, intB) f prec paral
  where currentN = lastN * 2
        currentInt = riemanSum (createPartition (intA, intB) currentN) f paral

-- calculates the integral of f over the interval (intA, intB). The precision can be set in the let-clause
integral :: (Double, Double) -> (Double -> Double) -> Bool -> Double
integral (intA, intB) f paral = let prec = 0.00001
                           in integralIterator (riemanSum [intA, intB] f paral) 1 (intA, intB) f prec paral

