# Assignment done by Kanishkverse

#we will import double queue as queue from collections

from collections import deque as queue
from time import time 
# 1st we create Direction Vectors for fetching neighbours in the puzzle - direction_x and direction_y
direction_x = [ -1, 0, 1, 0]
direction_y = [ 0, 1, 0, -1]

# Goal_state to compare validity of elements during search, we mention them as Target_grid
target_grid = [[0, 1, 2],
                [3, 4, 5],
                [6, 7, 8]]

# To find 2Dimensional index from 1Dimensional list
def get2Dindex(lst, value):
    for i, x in enumerate(lst):
        if value in x:
            return (i, x.index(value))

# Breadth First Search Method
def bfs(puzzle):
    list = []
    
    # Converting 1D Puzzle to 2D Matrix
    p_arr = []
    for i in range(3):
        p_arr.append(puzzle[i*3:(i+1)*3])


    # Setting up params for BFS
    q = queue()
    visited = [[ False for i in range(3)] for i in range(3)]

    # Adding position of 8 
    x_8, y_8 = get2Dindex(p_arr, 8)
    q.append((x_8, y_8))
    visited[x_8][y_8] = True

    print("BFS Visit Path:")

    # Performing BFS Visit
    start = time()

    while (len(q) > 0):
        curr = q.popleft()
        x = curr[0]
        y = curr[1]
        
        # Checking with goal
        if p_arr[x][y] != target_grid[x][y]:
            list.append(3 * x + y)
        # print(p_arr[x][y], end=' ')

        # Exploring Neighbours
        for i in range(4):
            adj_x = x + direction_x[i]
            adj_y = y + direction_y[i]
            if (adj_x >= 0 and adj_y >= 0 and adj_x < 3 and adj_y < 3):
                if not visited[adj_x][adj_y]:
                    q.append((adj_x, adj_y))
                    visited[adj_x][adj_y] = True
    # print()  
    end = time()

    # Priting Time
    print(f"Time Taken by BFS:", (end-start)*1000 ,"seconds")

    # Removing the first value which is index of 8
    list = list[1:]
    print(list)
    
    return list

# Depth First Search Method
def dfs(puzzle):
    list = []

    # Converting 1D Puzzle to 2D Matrix
    d_arr = []
    for i in range(3):
        d_arr.append(puzzle[i*3:(i+1)*3])

    visited = [[False for i in range(3)] for i in range(3)]
    x_8, y_8 = get2Dindex(d_arr, 8)

    # Stack, we use instead of queue in DFS
    s = []
    s.append([x_8, y_8])

    print("DFS Visit Path:")
    # Performing DFS Visit
    while (len(s) > 0):
        curr = s[len(s) - 1]
        s.remove(s[len(s) - 1])
        x = curr[0]
        y = curr[1]

        # Checking validity 
        if not (x >= 0 and y >= 0 and x < 3 and y < 3 and visited[x][y] == False):
            continue
 
        visited[x][y] = True

        # Checking with goal 
        if d_arr[x][y] != target_grid[x][y]:
            list.append(3 * x + y)
            
        # print(d_arr[x][y], end=' ')

        # Exploring Neighbours
        for i in range(4):
            adjacent_x = x + direction_x[i]
            adjacent_y = y + direction_y[i]
            s.append([adjacent_x, adjacent_y])

    # print()

    # Removing the first value which is index of 8
    list = list[1:]
    print(list)

    return list




################################################################################################################################
#2nd Assignment
# Calculates f-values = h-val + g-val
# h = Heuristics: How far the goal state is. 
#     Here the number of differing pieces in currrent state vs goal state
# g = Number of state changes from starting state 
def f(start, goal, level):
    return h(start, goal) + (level + 1)

# Checks for count of misplaced pieces 
# By comparing current puzzle state with desired grid
def h(start, goal):
   cnt = 0
   for i in range(0, len(goal)):
       for j in range(0, len(goal)):
           if goal[i][j] != start[i][j]:
               cnt += 1
   return cnt

# Swaps value of piece at x1, y1 with value of piece at x2, y2
def swap(puzzle, x1, y1, x2, y2):
    swapped = [row[:] for row in puzzle]
    swapped[x1][y1], swapped[x2][y2] = puzzle[x2][y2], puzzle[x1][y1]
    return swapped

# To find index of char in puzzle
def get_index(puzzle, char):
    for i in range(0,len(puzzle)):
        for j in range(0,len(puzzle)):
            if puzzle[i][j] == char:
                return i,j

# Checking if a child is already present 
def is_present(os, cs, child):
    for i in os:
        if h(i['puzzle'], child) == 0:
            return True
    for i in cs:
        if h(i['puzzle'], child) == 0:
            return True

    return False

#astar implementation
def astar(puzzle):

    # List to store the path
    list = []
    moves = 0

    # Converting 1D Puzzle to 2D Matrix
    p_arr = []
    for i in range(3):
        p_arr.append(puzzle[i*3:(i+1)*3])

    # Open List for newly generated states
    # Close List for keeping track of already expanded states
    open_states = []
    close_states = []
    state_id = 0

    # Adding the current state to list
    open_states.append(
    {
        'state_id': 0,
        'puzzle': p_arr,
        'f': f(p_arr, target_grid, -1),
        'g': 0,
        'prev_state': None
    })

    # Performing A* Search
    start = time()
    while True:
        # Getting current state
        curr_state = open_states[0]
        moves += 1
        
        x, y = get_index(curr_state['puzzle'], 8)
        list.append(3 * x + y)

        # Printing State Info
        print("Position of 8: ", x, y)
        print(curr_state['puzzle'])
        
        # No misplaced pieces
        if h(curr_state['puzzle'], target_grid) == 0:
            print(f"A* Search Done with {moves-2} moves!")
            break

        # Exploring Children
        x,y = get_index(curr_state['puzzle'], 8)

        for i in range(4):
            adj_x = x + direction_x[i]
            adj_y = y + direction_y[i]
            # Adding valid children
            if (adj_x >= 0 and adj_y >= 0 and adj_x < 3 and adj_y < 3):
                child = swap(curr_state['puzzle'],x,y, adj_x, adj_y)
                # If child is not explored
                if not is_present(open_states, close_states, child):
                    state_id += 1
                    open_states.append({
                        'state_id': state_id,
                        'puzzle': child,
                        'f': f(child, target_grid, curr_state['g']),
                        'g': curr_state['g'] + 1,
                        'prev_state': curr_state['state_id']
                        })

        # Adding current state to closing state and deleting from open states
        close_states.append(curr_state)
        del open_states[0]

        # Sorting based on least f value
        open_states.sort(key = lambda x:x['f'], reverse=False)

    end = time()

    # Priting Time
    print(f"Time Taken by A*:", (end-start)*100 ,"seconds")

    # Removing the first value which is index of 8
    list = list[1:]
    # print(list)

    return list

if __name__=="__main__":
    # puzzle = [i for i in range(10)]
    puzzle = [0, 4, 1, 3, 8, 2, 6, 7, 5]
    
    # print(bfs(puzzle))
    # print(dfs(puzzle))
    astar(puzzle)
