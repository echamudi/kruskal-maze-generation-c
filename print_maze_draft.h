//
//  print_maze_draft.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//

#ifndef print_maze_draft_h
#define print_maze_draft_h

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

#endif /* print_maze_draft_h */
