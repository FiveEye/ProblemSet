f :: Int -> [Int]
f 0 = [1]
f n = let t = f (n - 1) in (t!!0 * n) : t

fact = reverse (f 9)

g :: Int -> Int
g 0 = 0
g n = (fact!!(mod n 10)) + g (quot n 10)

h :: Int -> [Int]
h n = iterate g n


helper :: [Int] -> [Int] -> [Int]
helper (x:xs) t = if elem x t then t
                  else helper xs (x:t)

len :: Int -> Int
len n = length $ helper (h n) []

ans :: Int -> Int -> Int
ans 0 x = x
ans n x = if len n == 60 then ans (n-1) (x+1)
          else ans (n - 1) x
        

answer = ans 1000000 0