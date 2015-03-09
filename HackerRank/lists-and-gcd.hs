-- https://www.hackerrank.com/challenges/lists-and-gcd
f :: [Int] -> [(Int, Int)]
f [] = []
f (x:y:z) = (x,y):(f z)

g :: [(Int, Int)] -> [(Int, Int)] -> [(Int, Int)]
g [] _ = []
g _ [] = []
g ((x0,x1):xs) ((y0,y1):ys) = if x0 == y0 then (x0, min x1 y1) : g xs ys
                              else if x0 < y0 then g xs ((y0,y1):ys)
                              else g ((x0,x1):xs) ys

h :: [(Int, Int)] -> String
h [] = ""
h ((x0,x1):xs) = show x0 ++ " " ++ show x1 ++ " " ++ h xs

solve :: String -> String
solve contents = h $ foldr g (head all) (tail all)
  where
    all = map f (map (map (read :: String->Int)) $ map words (lines contents))

main = do
  n <- readLn :: IO Int
  contents <- getContents
  putStrLn $ solve contents
