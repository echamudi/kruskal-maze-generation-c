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

const int MAZE_SIZE = 4;

int** maze_draft;

int* is_neighbor_fillable(int x, int y)
{
    int total_fillable = 0;

    bool top_fillable = false;
    bool right_fillable = false;
    bool bottom_fillable = false;
    bool left_fillable = false;
    
    // Check top
    if (y > 0 && (maze_draft[x][y] != maze_draft[x][y - 1])) {
        total_fillable++;
        top_fillable = true;
    }

    // Check right
    if (x < (MAZE_SIZE - 1) && (maze_draft[x][y] != maze_draft[x + 1][y])) {
        total_fillable++;
        right_fillable = true;
    }

    // Check bottom
    if (y < (MAZE_SIZE - 1) && (maze_draft[x][y] != maze_draft[x][y + 1])) {
        total_fillable++;
        bottom_fillable = true;
    }

    // Check left
    if (x > 0 && (maze_draft[x][y] != maze_draft[x - 1][y])) {
        total_fillable++;
        left_fillable = true;
    }

    int* array = (int*) calloc(total_fillable + 1, sizeof(bool));

    array[0] = total_fillable; // First element shows how many items are fillable
    
    int i = 1;
    if (top_fillable) {
        array[i] = TOP;
        i++;
    }
    if (right_fillable) {
        array[i] = RIGHT;
        i++;
    }
    if (bottom_fillable) {
        array[i] = BOTTOM;
        i++;
    }
    if (left_fillable) {
        array[i] = LEFT;
        i++;
    }

    return array;
}

int** maze()
{
    // Initialize randomizer
    srand((unsigned)time(NULL));

    int total_nodes = MAZE_SIZE * MAZE_SIZE;

    // Create maze draft
    maze_draft = (int **)calloc(MAZE_SIZE, sizeof(int *));
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        maze_draft[i] = (int *)calloc(MAZE_SIZE, sizeof(int));
    }

    // Assign each cell in draft an integer identifier
    for (int x = 0; x < MAZE_SIZE; x++)
    {
        for (int y = 0; y < MAZE_SIZE; y++)
        {
            maze_draft[x][y] = x * MAZE_SIZE + y;
        }
    }

    // Print maze_draft
    for (int x = 0; x < MAZE_SIZE; x++)
    {
        for (int y = 0; y < MAZE_SIZE; y++)
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

    return maze_draft;
}

int main(int argc, const char *argv[])
{
    // insert code here...
    printf("Hello, World!\n");

    int **maze_result = maze();
    return 0;
}
