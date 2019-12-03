//
//  main.c
//  maze
//
//  Created by Ezzat Chamudi on 11/29/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//  License: Apache-2.0
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>

#include "print_maze.h"
#include "randomized_kruskal.h"

int main(int argc, const char *argv[])
{
    printf("Kruskal's Maze Generation!\n");
    // Initialize randomizer
    srand((unsigned)time(NULL));

    int size = 4;

    struct maze maze1 = randomized_kruskal(true, size, 0b00000011);

    print_maze(maze1.graph, size);

    // Free mems
    for (int i = 0; i < size * size; i++)
        free(maze1.graph[i]);
    free(maze1.graph);

    return 0;
}
