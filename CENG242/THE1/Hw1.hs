module Hw1 (next) where -- DO NOT CHANGE THIS

-- Helper Functions--
adjacent1D :: Int -> [a] -> [a]
adjacent1D j a 
    | j == 0 = take 2 a
    | j == (length a)-1 = (reverse . (take 2) . reverse) a
    | otherwise = ((take 3) . (drop (j-1))) a

adjacent2D :: Int -> Int -> [[a]] -> [[a]]
adjacent2D i j a = adjacent1D i [adjacent1D j b | b <- a]

kickout :: [String] -> [String]
kickout a = [ b  | b <- a, b /= "W" ]


numberof :: [[String]] -> Int
numberof a = length (concatMap kickout a)-1

changestate :: Int -> Int -> [[String]] -> String
changestate i j a = 
    if a !! i !! j == "B" && (numberof (adjacent2D i j a) ==  3 || numberof (adjacent2D i j a) ==  2)
        then "B"
        else if a !! i !! j == "W" && (numberof (adjacent2D i j a) == 2)
            then "B"
            else "W"


next :: [[String]] -> [[String]]
next a = [[(changestate i j a) | j <- [0..((length . head) a-1)]] | i <- [0..((length a)-1)]]

-- IMPLEMENT NEXT FUNCTION HERE --

-- DO NOT CHANGE CODE BELOW THIS LINE! --
createFile fileName = writeFile fileName ""

writeSteps filename grid n = do
                    createFile filename
                    writeStepsHelper filename grid n n
    where writeStepsHelper filename grid n all = if n == 0 then putStrLn ((show all) ++ " steps are succesfully written to \'" ++ filename ++ "\'") else do
                                    appendFile filename ((show (next grid)) ++ "\n")
                                    writeStepsHelper filename (next grid) (n-1) all