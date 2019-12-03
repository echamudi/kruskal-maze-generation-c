#  Kruskal Maze Generation

Modified randomized Kruskal's maze generation algorithm written in C.

## Key Difference

- Original algorithm
    - In each iteration, the algorithm will select two random adjacent nodes that belong to two different groups and merge them into one group.

- Modified algorithm
    - In each iteration, if it can select S shaped nine adjacent nodes, it will select it. Or, if it can not select S shaped nine adjacent nodes, the algorithm can select L shaped three adjacent nodes that belong to three different group and merge them into one group.

## Running
```
clang main.c && ./a.out
```

## License

2019 © Ezzat Chamudi

Code is released under Apache-2.0 license
