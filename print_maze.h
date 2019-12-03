//
//  print_maze.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//

#include <stdio.h>

#ifndef print_maze_h
#define print_maze_h

void print_maze(int ** maze_graph, int size) {
    int current_node;

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            // Check if there's connection to the above node.
            current_node = x * size + y;

            if (current_node - 1 >= 0 && maze_graph[current_node][current_node - 1] == 1) {
                printf("██  ");
            } else {
                printf("████");
            }
        }

        // Right most border
        printf("██\n");

        for (int x = 0; x < size; x++)
        {
            // Check if there's connection to the left node.
            current_node = x * size + y;
            
            if (current_node - size >= 0 && maze_graph[current_node][current_node - size] == 1) {
                printf("    ");
            } else {
                printf("██  ");
            }
        }

        // Right most border
        printf("██\n");
    }

    // Bottom border
    for (int i = 0; i < size; i++)
    {
        printf("████");
    }
    printf("██\n");
}

#endif
