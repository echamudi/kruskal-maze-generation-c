#  Kruskal Maze Generation

Modified randomized Kruskal's maze generation algorithm written in C.

## Key Difference

- Original algorithm
    - In each iteration, the algorithm will select two random adjacent nodes that belong to two different groups and merge them into one group.

- Modified algorithm
    - In each iteration, the algorithm can select L shaped three adjacent nodes that belong to three different group and merge them into one group.

## Sample Output

```
Kruskal's Maze Generation!
Current maze draft:
    0    1    2    3    
0    0    4    8    12    
1    1    5    9    13    
2    2    6    10    14    
3    3    7    11    15    

Pass: 1;
Selected first node: (2, 0);
Available directions:
 -> right
 -> right bottom
 -> bottom right
 -> bottom
 -> bottom left
 -> left bottom
 -> left
Selected direction: right bottom
All nodes: (2, 0), (3, 0), and (3, 1);
Current maze draft:
    0    1    2    3    
0    0    4    8    8    
1    1    5    9    8    
2    2    6    10    14    
3    3    7    11    15    
Still not in one room. Continuing...

Pass: 2;
Selected first node: (3, 2);
Available directions:
 -> top left
 -> top
 -> bottom
 -> bottom left
 -> left bottom
 -> left
 -> left top
Selected direction: bottom left
All nodes: (3, 2), (3, 3), and (2, 3);
Current maze draft:
    0    1    2    3    
0    0    4    8    8    
1    1    5    9    8    
2    2    6    10    14    
3    3    7    14    14    
Still not in one room. Continuing...

Pass: 3;
Selected first node: (1, 0);
Available directions:
 -> right
 -> right bottom
 -> bottom right
 -> bottom
 -> bottom left
 -> left bottom
 -> left
Selected direction: bottom right
All nodes: (1, 0), (1, 1), and (2, 1);
Current maze draft:
    0    1    2    3    
0    0    4    8    8    
1    1    4    4    8    
2    2    6    10    14    
3    3    7    14    14    
Still not in one room. Continuing...

Pass: 4;
Selected first node: (2, 2);
Available directions:
 -> top
 -> top right
 -> right top
 -> right
 -> bottom
 -> bottom left
 -> left bottom
 -> left
 -> left top
Selected direction: left top
All nodes: (2, 2), (1, 2), and (1, 1);
Current maze draft:
    0    1    2    3    
0    0    10    8    8    
1    1    10    10    8    
2    2    10    10    14    
3    3    7    14    14    
Still not in one room. Continuing...

Pass: 5;
Selected first node: (2, 1);
Available directions:
 -> top
 -> right
 -> right bottom
Selected direction: right bottom
All nodes: (2, 1), (3, 1), and (3, 2);
Current maze draft:
    0    1    2    3    
0    0    10    10    10    
1    1    10    10    10    
2    2    10    10    10    
3    3    7    10    10    
Still not in one room. Continuing...

Pass: 6;
Selected first node: (0, 3);
Available directions:
 -> top
 -> top right
 -> right top
 -> right
Selected direction: top
All nodes: (0, 3) and (0, 2);
Current maze draft:
    0    1    2    3    
0    0    10    10    10    
1    1    10    10    10    
2    3    10    10    10    
3    3    7    10    10    
Still not in one room. Continuing...

Pass: 8;
Selected first node: (1, 3);
Available directions:
 -> top left
 -> top
 -> right
 -> left
Selected direction: top left
All nodes: (1, 3), (1, 2), and (0, 2);
Current maze draft:
    0    1    2    3    
0    0    7    7    7    
1    1    7    7    7    
2    7    7    7    7    
3    7    7    7    7    
Still not in one room. Continuing...

Pass: 11;
Selected first node: (1, 0);
Available directions:
 -> left bottom
 -> left
Selected direction: left
All nodes: (1, 0) and (0, 0);
Current maze draft:
    0    1    2    3    
0    7    7    7    7    
1    1    7    7    7    
2    7    7    7    7    
3    7    7    7    7    
Still not in one room. Continuing...

Pass: 14;
Selected first node: (0, 2);
Available directions:
 -> top
Selected direction: top
All nodes: (0, 2) and (0, 1);
Current maze draft:
    0    1    2    3    
0    7    7    7    7    
1    7    7    7    7    
2    7    7    7    7    
3    7    7    7    7    
DONE!

Final graph:
    0    1    2    3    4    5    6    7    8    9    10    11    12    13    14    15    
0    0    0    0    0    1    0    0    0    0    0    0    0    0    0    0    0    
1    0    0    1    0    0    0    0    0    0    0    0    0    0    0    0    0    
2    0    1    0    1    0    0    1    0    0    0    0    0    0    0    0    0    
3    0    0    1    0    0    0    0    0    0    0    0    0    0    0    0    0    
4    1    0    0    0    0    1    0    0    0    0    0    0    0    0    0    0    
5    0    0    0    0    1    0    1    0    0    1    0    0    0    0    0    0    
6    0    0    1    0    0    1    0    1    0    0    1    0    0    0    0    0    
7    0    0    0    0    0    0    1    0    0    0    0    0    0    0    0    0    
8    0    0    0    0    0    0    0    0    0    0    0    0    1    0    0    0    
9    0    0    0    0    0    1    0    0    0    0    0    0    0    1    0    0    
10    0    0    0    0    0    0    1    0    0    0    0    0    0    0    0    0    
11    0    0    0    0    0    0    0    0    0    0    0    0    0    0    0    1    
12    0    0    0    0    0    0    0    0    1    0    0    0    0    1    0    0    
13    0    0    0    0    0    0    0    0    0    1    0    0    1    0    1    0    
14    0    0    0    0    0    0    0    0    0    0    0    0    0    1    0    1    
15    0    0    0    0    0    0    0    0    0    0    0    1    0    0    1    0    

All connections:
Node [0] -> [4]
Node [1] -> [2]
Node [2] -> [1][3][6]
Node [3] -> [2]
Node [4] -> [0][5]
Node [5] -> [4][6][9]
Node [6] -> [2][5][7][10]
Node [7] -> [6]
Node [8] -> [12]
Node [9] -> [5][13]
Node [10] -> [6]
Node [11] -> [15]
Node [12] -> [8][13]
Node [13] -> [9][12][14]
Node [14] -> [13][15]
Node [15] -> [11][14]

Program ended with exit code: 0
```
## License

2019 © Ezzat Chamudi

Code is released under Apache-2.0 license
