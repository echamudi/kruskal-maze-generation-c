//
//  web.c
//  kruskal-maze-generation-c
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
#include <time.h>

#include "definitions.h"
#include "print_maze.h"
#include "randomized_kruskal.h"
#include "stats.h"
#include "util.h"

struct maze web_randomized_kruskal(int size, unsigned int direction_options)
{
    srand((unsigned)time(NULL));

    struct maze maze1 = randomized_kruskal(0, size, direction_options);
    
    print_maze(maze1.graph, size);

    // Free mems
    for (int i = 0; i < size * size; i++)
        free(maze1.graph[i]);
    free(maze1.graph);
    
    return maze1;
}
