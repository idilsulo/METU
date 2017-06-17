module Hw1 (next) where -- DO NOT CHANGE THIS

-- Helper Functions--

adjacent1D :: Int -> [a] -> [a]
adjacent1D j a 
    | j == 0 = take 2 a
    | j == (length a)-1 = (reverse . (take 2) . reverse) a
    | otherwise = ((take 3) . (drop (j-1))) a

adjacent2D :: Int -> Int -> [[a]] -> [[a]]
adjacent2D i j a = adjacent1D i [adjacent1D j b | b <- a]

--adjacent :: Int -> Int -> [[a]] -> [[a]] -> [[a]]
--adjacent i j a = (adjacent2D i j a)--

convert :: String -> Int
convert n = if n == "W" then 0 else 1

convertArray :: [[String]] -> [[Int]]
convertArray a = map (map convert) a

{-change :: Int -> Int -> [[Int]] -> [[Int]]
change i j a = a !! i !! j = -1-}

sumArray :: [[Int]] -> Int
sumArray a = sum $ map sum a

-- numliving :: [[Int]] -> Int -> Int
-- make it not to count the bacteria -- 
-- numliving a = sumArray a --

--next :: [[String]] -> [[String]]--
next :: String -> Int
-- IMPLEMENT NEXT FUNCTION HERE --
-- An expression for next just for compilation --
next n = if n == "W" then 0 else 1


-- DO NOT CHANGE CODE BELOW THIS LINE! --
createFile fileName = writeFile fileName ""

writeSteps filename grid n = do
                    createFile filename
                    writeStepsHelper filename grid n n
    where writeStepsHelper filename grid n all = if n == 0 then putStrLn ((show all) ++ " steps are succesfully written to \'" ++ filename ++ "\'") else do
                                    appendFile filename ((show (next grid)) ++ "\n")
                                    writeStepsHelper filename (next grid) (n-1) all