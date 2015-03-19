-- https://www.hackerrank.com/challenges/minimum-multiple

import Text.Printf (printf)

data SegTree a = Node Int Int a (SegTree a) (SegTree a) | Leaf deriving Show

getItem :: SegTree a -> a
getItem (Node _ _ a _ _) = a

initSegTree :: Int -> Int -> a -> SegTree a
initSegTree l r a =
  if l == r then Node l r a Leaf Leaf
  else Node l r a (initSegTree l m a) $ initSegTree (m + 1) r a
  where m = fst $ divMod (l + r) 2

buildSegTree :: (a -> a -> a) -> Int -> Int -> [a] -> SegTree a
buildSegTree f l r s@(x:xs) =
  if l == r then Node l r x Leaf Leaf
  else Node l r (f (getItem lc) (getItem rc)) lc rc
  where
    m = fst $ divMod (l + r) 2
    lc = buildSegTree f l m s
    rc = buildSegTree f (m + 1) r (drop (m - l + 1) s)

updateSegTree :: (a -> a -> a) -> SegTree a -> Int -> Int -> a -> SegTree a
updateSegTree _ Leaf _ _ _ = Leaf
updateSegTree f (Node nl nr na lc rc) l r a = if l <= nl && nr <= r then Node nl nr a lc rc
  else if r <= m then let newlc = updateSegTree f lc l r a in Node nl nr (f (getItem newlc) (getItem rc)) newlc rc
  else if l >  m then let newrc = updateSegTree f rc l r a in Node nl nr (f (getItem lc) (getItem newrc)) lc newrc
  else
    let newlc = updateSegTree f lc l r a in
    let newrc = updateSegTree f rc l r a in
      Node nl nr (f (getItem newlc) (getItem newrc)) newlc newrc
  where m = fst $ divMod (nl + nr) 2

querySegTree :: (a -> a -> a) -> SegTree a -> Int -> Int -> a
querySegTree f (Node nl nr na lc rc) l r =
  if l <= nl && nr <= r then na
  else if r <= m then querySegTree f lc l r
  else if l >  m then querySegTree f rc l r
  else
    let la = querySegTree f lc l r in
    let ra = querySegTree f rc l r in 
      f la ra
  where m = fst $ divMod (nl + nr) 2

readInt :: String -> Int
readInt = read
 
transQuery :: [String] -> (Int, Int, Int)
transQuery (a:b:c:[]) = (if a == "Q" then 1 else 0, read b, read c)

--gcd a b = if mod a b == 0 then b else gcd b (mod a b)

--lcm a b = a * b / (gcd a b)


 
solve0 :: (SegTree Integer) -> [(Int, Int, Int)] -> [Integer] 
solve0 sgtree [] = []
solve0 sgtree ((q,l,r):xs) = 
  if q == 1 then 
    (mod (querySegTree lcm sgtree l r) 1000000007):(solve0 sgtree xs)
  else
    let a = (querySegTree lcm sgtree l l) in  
    let t = updateSegTree lcm sgtree l l ((toInteger r) * a) in solve0 t xs

solve :: [String] -> [String]
solve (n_str:l_str:m_str:qs_str) = map show (solve0 sgtree qs)
  where n = read n_str
        l = map read (words l_str)
        qs = map transQuery $ map words qs_str
        sgtree = buildSegTree lcm 0 (n - 1) l
        
        
  
  

main :: IO()
main = do
  contents <- getContents 
  mapM_ putStrLn $ solve (lines contents)
