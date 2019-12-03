#include <stdio.h>

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