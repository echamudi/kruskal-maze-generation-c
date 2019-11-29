//
//  main.c
//  maze
//
//  Created by Ezzat Chamudi on 11/29/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

const int TOP = 0;
const int RIGHT = 1;
const int BOTTOM = 2;
const int LEFT = 3;

int *is_neighbor_fillable(int** maze_draft, int x, int y)
{
    int total_fillable = 0;

    bool top_fillable = false;
    bool right_fillable = false;
    bool bottom_fillable = false;
    bool left_fillable = false;

    // Check top
    if (y > 0 && (maze_draft[x][y] != maze_draft[x][y])) {
        
    }

    // Check right

    // Check bottom

    // Check left

    return;
}

int **maze(unsigned int n)
{
    int total_nodes = n * n;

    // Create maze draft
    int **maze_draft = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        maze_draft[i] = (int *)calloc(n, sizeof(int));
    }

    // Assign each cell in draft an integer identifier
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            maze_draft[x][y] = x * n + y;
        }
    }

    // Print maze_draft
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            printf("%d\t", maze_draft[x][y]);
        }
        printf("\n");
    }

    // Create graph
    int **graph = (int **)calloc(total_nodes, sizeof(int *));
    for (int i = 0; i < total_nodes; i++)
    {
        graph[i] = (int *)calloc(total_nodes, sizeof(int));
    }

    // Print graph
    for (int x = 0; x < total_nodes; x++)
    {
        for (int y = 0; y < total_nodes; y++)
        {
            printf("%d\t", graph[x][y]);
        }
        printf("\n");
    }

    // Randomize selection
    srand((unsigned)time(NULL));

    int x1;
    int y1;
    int x2;
    int y2;
    int direction;
    int iteration_number = 0;

    while (1)
    {
        iteration_number++;
        printf("Iteration: %d\n", iteration_number);

        while (1)
        {
            x1 = rand() % n;
            y1 = rand() % n;
            printf("random position: x=%d y=%d\n", x1, y1);

            direction = rand() % 4;

            switch (direction)
            {
            case TOP:
                printf("Chosen direction: TOP\n");
                x2 = x1;
                y2 = y1 - 1;
                break;
            case RIGHT:
            default:
                printf("Chosen direction: RIGHT\n");
                x2 = x1 + 1;
                y2 = y1;
                break;
            case BOTTOM:
                printf("Chosen direction: BOTTOM\n");
                x2 = x1;
                y2 = y1 + 1;
                break;
            case LEFT:
                printf("Chosen direction: LEFT\n");
                x2 = x1 - 1;
                y2 = y1;
                break;
            }

            if (x2 < 0 || x2 >= n)
            {
                printf("x2 is out of range, re-random...\n");
                continue;
            }

            if (y2 < 0 || y2 >= n)
            {
                printf("y2 is out of range, re-random...\n");
                continue;
            }

            if (maze_draft[x1][y1] == maze_draft[x2][y2])
            {
                printf("Both nodes is already in the same room, re-random...\n");
                continue;
            }

            break;
        }

        // Add link
        int node1_id = x1 * n + y1;
        int node2_id = x2 * n + y2;

        graph[node1_id][node2_id] = 1;
        graph[node2_id][node1_id] = 1;

        int node1_room = maze_draft[x1][y1];
        int node2_room = maze_draft[x2][y2];

        // Unify room
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < n; y++)
            {
                if (maze_draft[x][y] == node2_room || maze_draft[x][y] == node1_room)
                    maze_draft[x][y] = node1_room;
            }
        }

        // Print maze_draft
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < n; y++)
            {
                printf("%d\t", maze_draft[x][y]);
            }
            printf("\n");
        }

        // Check if all nodes already in the same room
        for (int x = 0; x < total_nodes; x++)
        {
            for (int y = 0; y < total_nodes; y++)
            {
            }
        }

        if (iteration_number > 10)
            break;
    }

    // Print graph
    printf("\t");
    for (int i = 0; i < total_nodes; i++)
    {
        printf("%d\t", i);
    }
    printf("\n");

    for (int x = 0; x < total_nodes; x++)
    {
        printf("%d\t", x);

        for (int y = 0; y < total_nodes; y++)
        {
            printf("%d\t", graph[x][y]);
        }
        printf("\n");
    }

    return maze_draft;
}

int main(int argc, const char *argv[])
{
    // insert code here...
    printf("Hello, World!\n");

    int **maze_result = maze(4);
    return 0;
}
