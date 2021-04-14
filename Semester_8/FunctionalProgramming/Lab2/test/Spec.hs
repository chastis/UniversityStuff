import Test.QuickCheck
import Data.Monoid
import Control.Monad
import Lib

main :: IO ()
main = do
    -- sequential test
    quickCheck (-1571 == round(integral (0, 500*3.14159) (\x -> x*sin x) True))
    -- parallel test
    quickCheck (-1571 == round(integral (0, 500*3.14159) (\x -> x*sin x) False))
