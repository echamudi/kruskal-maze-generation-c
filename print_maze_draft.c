//
//  print_maze_draft.c
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 11/29/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//  License: Apache-2.0
//

#include "print_maze_draft.h"

void print_maze_draft(int **maze_draft, int size)
{
    // Print maze_draft
    printf("Current maze draft:\n");
    printf("\t");

    for (int i = 0; i < size; i++)
    {
        printf("[%d]\t", i);
    }
    printf("\n");

    for (int x = 0; x < size; x++)
    {
        printf("[%d]\t", x);
        for (int y = 0; y < size; y++)
        {
            printf("%d\t", maze_draft[y][x]);
        }
        printf("\n");
    }
}
