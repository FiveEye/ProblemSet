-- https://www.hackerrank.com/challenges/range-minimum-query

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

solve_seg :: SegTree Int -> [Int] -> Int
solve_seg st [a, b] = querySegTree min st a b

solve :: Int -> Int -> [Int] -> [[Int]] -> [Int]
solve n m s qs = let st = buildSegTree min 0 (n - 1) s in
  map (solve_seg st) qs

main :: IO()
main = getContents >>= mapM_ (printf "%d\n"). (\([n, m]:s:qs) -> solve n m s qs). map (map read. words). lines
