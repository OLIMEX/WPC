
-- target = 1 (*3 | div 2)* 
--
--
--

import Data.Tree

-- useful operator
x |> f = f x 

-- basic breadth-first search
state_tree children_of state
 = Node state [ state_tree children_of s | s <- children_of state ]

breadth_first t 
 = bft_aux [t]
   where
     bft_aux trees = (trees |> map rootLabel) ++ (trees |> map subForest |> concat |> bft_aux)

breadth_first_search is_goal child_generator start_state
 =    start_state
   |> state_tree child_generator
   |> breadth_first
   |> filter is_goal



-- problem instance
-- storing the "state" as the current string plus corresponding number
start = ("1", 1)

-- two possible next steps: /2 or *3
children (s,n) = [ (s ++ " /2", n `div` 2), (s ++ " *3", n * 3)]

-- and success when the number matches
goal tgt (s,n) = n == tgt 


-- pulling it all together
all_solutions n = breadth_first_search (goal n) children start

first_sol n = head $ all_solutions n 

first_m m n = all_solutions n |> take m |> map show |> unlines |> putStr

main = first_m 10 313 
