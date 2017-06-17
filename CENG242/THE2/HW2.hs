module WordTree(WordTree(Word, Subword, Root), emptyTree, getAllPaths, addWords, deleteWords, getWordsBeginWith) where

data WordTree = Word String | Subword String [WordTree] | Root [WordTree]

emptyTree :: WordTree
emptyTree = Root []
-- DO NOT MODIFY ABOVE

getAllPaths :: WordTree -> [[String]]
addWords :: WordTree -> [String] -> WordTree
deleteWords :: WordTree -> [String] -> WordTree
getWordsBeginWith :: WordTree -> String -> [String]


-- Helper function printTree which includes another function definition treeprint to show a WordTree
printTree :: [WordTree] -> String -> String
printTree tree string = treeprint tree string 0
    where
        treeprint [] _ _ = ""
        treeprint tree previous depth = case (head tree) of
            Word word -> indent (depth+1) ++ id previous ++ id word ++ "\n" ++ (treeprint (tail tree) previous depth)
            Subword subword wordtree -> indent (depth+1) ++ id previous ++ id subword ++ ":" ++ "\n" ++ (treeprint wordtree (previous++subword) (depth+1)) ++ (treeprint (tail tree) (previous) (depth))


--Helper functions for indentation which will be used in printTree function

unwords2          :: [String] -> String
unwords2 []       =  ""
unwords2 ws       =  foldr1 (\w s -> w ++ s) ws

indent       :: Int -> String 
indent depth = 
    if depth /= 0 
        then unwords2 (replicate ((depth-1)*2) " ")
        else
            ""

instance Show WordTree where
      show (Root wtree) = printTree wtree ""
      show emptyTree = ""


getpaths :: [WordTree] -> [[String]]
getpaths [] = []
getpaths tree = case (head tree) of
    Word word -> [[word]] ++ (getpaths (tail tree))
    Subword subword wordtree -> map ([subword]++) (getpaths wordtree) ++ (getpaths (tail tree))

getAllPaths (Root wtree) = getpaths wtree






prefix :: [Char] -> [Char] -> [Char]
prefix [] [] = []
prefix _ [] = []
prefix [] _ = []
prefix (x:xs) (y:ys)
     | (x==y) = [x] ++ prefix xs ys
     | otherwise = []

lexicographic :: [Char] -> [Char] -> Bool
lexicographic [] [] = True
lexicographic [] _ = True
lexicographic _ [] = False
lexicographic (x:xs) (y:ys)
     | x < y = True
     | x==y =  lexicographic xs ys
     | otherwise = False

lexicographer :: [String] -> String -> [String]
lexicographer [] string = [string]
lexicographer treelist "" = treelist
lexicographer treelist string = case (lexicographic (head treelist) string) of
    True -> [head treelist] ++ lexicographer (tail treelist) string
    False -> [string] ++ treelist


putwordtree :: WordTree -> [String] -> [String]
putwordtree wtree list = putwords (getWordsBeginWith wtree "") list
    where
        putwords treelist [] = treelist
        putwords treelist list = putwords (lexicographer treelist (head list)) (tail list)
            where
                lexicographer [] string = [string]
                lexicographer treelist "" = treelist
                lexicographer treelist string = case (lexicographic (head treelist) string) of
                    True -> if prefix (head treelist) string == string
                                then [string] ++ tail treelist
                                else [head treelist] ++ lexicographer (tail treelist) string
                    False -> [string] ++ treelist 
               
split :: [String] -> [[String]]
split [] = []
split list = [take (length ((takeWhile (/= "") (map (prefix (head list)) (tail list))))+1) list] ++ split (drop (length ((takeWhile (/= "") (map (prefix (head list)) (tail list))))+1) list)

commonprefix :: [String] -> String
commonprefix [] = ""
commonprefix list = if length list == 1
                        then ""
                        else minimum [prefix (head list) string | string <- (tail list)] 

deleteprefix :: [String] -> [String]
deleteprefix [] = []
deleteprefix list = map (drop (length (commonprefix list))) list



buildtree' :: [[String]] -> [WordTree] -> [WordTree]
buildtree' [] wordtree = wordtree
--buildtree' [[]] wordtree = wordtree
buildtree' list wordtree = buildtree' (tail list) (buildtree (commonprefix (head list)) (head list) wordtree)  
    where
        buildtree _ [] wordtree = wordtree
        buildtree string list wordtree = if (head list) == ""
                                            then wordtree ++ [Word ""]
                                                else if string == ""
                                                    then wordtree ++ [Word word | word <- list]
                                                    else wordtree ++ [Subword (commonprefix list) (buildtree' (split (deleteprefix list)) [])]


addWords wtree list = Root (buildtree' (split (putwordtree wtree list)) []) 




deletewordtree :: WordTree -> [String] -> [String] 
deletewordtree wtree list = deletewords (getWordsBeginWith wtree "") list
    where
        deletewords treelist [] = treelist
        deletewords treelist list = deletewords (erase treelist (head list)) (tail list)
            where 
                erase [] string = []
                erase treelist string = case ((head treelist) == string) of
                    True -> tail treelist
                    False -> [head treelist] ++ (erase (tail treelist) string)


deleteWords wtree list = Root (buildtree' (split (deletewordtree wtree list)) [])





-- check "yx" "x" returns true in this case
check :: [Char] -> [Char] -> Bool
check [] [] = True
check _ []  = False
check [] _  = False
check (x:xs) (y:ys)
     | y==x = True
     | otherwise = check xs (y:ys)


getwords :: [WordTree] -> String -> [String]
getwords [] _ = []
getwords tree string = case (head tree) of
    Word word -> if ((check string word) || string == "") && (length string <= length word)
                    then [word] ++ getwords (tail tree) string
                    else getwords (tail tree) string
    Subword subword wordtree -> if (check string subword) || string == ""
                                    then map (subword++) (getwords wordtree (drop (length subword) string)) ++ getwords (tail tree) string
                                    else getwords (tail tree) string

getWordsBeginWith (Root wtree) str = getwords wtree str 