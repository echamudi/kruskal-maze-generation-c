//
//  web.c
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 11/29/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//  License: Apache-2.0
//

#include "web.h"

int web_randomized_kruskal(int size, int direction_options)
{
    srand((unsigned)time(NULL));

    struct maze maze1 = randomized_kruskal(0, size, direction_options);
    
    print_maze(maze1.graph, size);

    // Free mems
    for (int i = 0; i < size * size; i++)
        free(maze1.graph[i]);
    free(maze1.graph);

    return 0;
}
