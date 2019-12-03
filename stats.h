//
//  stats.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//

#include <stdio.h>

#ifndef stats_h
#define stats_h

void stats(unsigned int direction_options)
{
    int size = 10;
    int trials = 100000;

    // Calculate average of passes
    double avg_deg1_nodes = 0;
    double avg_deg2_nodes = 0;
    double avg_deg3_nodes = 0;
    double avg_deg4_nodes = 0;

    for (int i = 0; i < trials; i++)
    {
        struct maze my_maze = randomized_kruskal(false, size, direction_options);
        avg_deg1_nodes += (double)my_maze.total_deg1_nodes / trials;
        avg_deg2_nodes += (double)my_maze.total_deg2_nodes / trials;
        avg_deg3_nodes += (double)my_maze.total_deg3_nodes / trials;
        avg_deg4_nodes += (double)my_maze.total_deg4_nodes / trials;

        // Free mems
        for (int i = 0; i < size * size; i++)
            free(my_maze.graph[i]);
        free(my_maze.graph);
    }

    printf("Avg deg 1 nodes: %lf\n", avg_deg1_nodes);
    printf("Avg deg 2 nodes: %lf\n", avg_deg2_nodes);
    printf("Avg deg 3 nodes: %lf\n", avg_deg3_nodes);
    printf("Avg deg 4 nodes: %lf\n", avg_deg4_nodes);
}

#endif /* stats_h */
