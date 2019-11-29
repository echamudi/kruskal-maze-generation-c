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

int ** maze_draft;

unsigned char * available_directions(int x, int y) {
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
    
    unsigned char * array = (unsigned char * ) calloc(total_fillable + 1, sizeof(unsigned char));
    
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

int ** maze() {
    // Initialize randomizer
    srand((unsigned) time(NULL));
    
    const int total_nodes = MAZE_SIZE * MAZE_SIZE;
    
    // Create maze draft
    maze_draft = (int ** ) calloc(MAZE_SIZE, sizeof(int * ));
    for (int i = 0; i < MAZE_SIZE; i++) {
        maze_draft[i] = (int * ) calloc(MAZE_SIZE, sizeof(int));
    }
    
    // Assign each cell in draft an integer identifier
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            maze_draft[x][y] = x * MAZE_SIZE + y;
        }
    }
    
    // Print maze_draft
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            printf("%d\t", maze_draft[x][y]);
        }
        printf("\n");
    }
    
    // Create graph
    int ** graph = (int ** ) calloc(total_nodes, sizeof(int * ));
    for (int i = 0; i < total_nodes; i++) {
        graph[i] = (int * ) calloc(total_nodes, sizeof(int));
    }
    
    // Print graph
    for (int x = 0; x < total_nodes; x++) {
        for (int y = 0; y < total_nodes; y++) {
            printf("%d\t", graph[x][y]);
        }
        printf("\n");
    }
    
    int x1;
    int y1;
    int x2;
    int y2;
    
    int iteration_number = 0;
    
    while (1) {
        iteration_number++;
        
        x1 = rand() % MAZE_SIZE;
        y1 = rand() % MAZE_SIZE;
        
        unsigned char * directions = available_directions(x1, y1);
        unsigned char total_available_directions = directions[0];
        
        // If the selected node has no available direction, re-random
        if (total_available_directions == 0) {
            free(directions);
            continue;
        };
        
        int selected_direction = directions[(rand() % total_available_directions) + 1];
        
        free(directions);
        
        switch (selected_direction) {
            case TOP:
                x2 = x1;
                y2 = y1 - 1;
                break;
            case RIGHT:
                x2 = x1 + 1;
                y2 = y1;
                break;
            case BOTTOM:
                x2 = x1;
                y2 = y1 + 1;
                break;
            case LEFT:
                x2 = x1 - 1;
                y2 = y1;
                break;
            default:
                printf("ERROR: Wrong direction code.");
                return NULL;
        }
        
        printf("Selected pair: (%d, %d) and (%d, %d)\n", x1, y1, x2, y2);
        
        // Add link in the graph
        int node1_id = x1 * MAZE_SIZE + y1;
        int node2_id = x2 * MAZE_SIZE + y2;

        graph[node1_id][node2_id] = 1;
        graph[node2_id][node1_id] = 1;

        int node1_room = maze_draft[x1][y1];
        int node2_room = maze_draft[x2][y2];

        // Unify room
        for (int x = 0; x < MAZE_SIZE; x++) {
            for (int y = 0; y < MAZE_SIZE; y++) {
                if (maze_draft[x][y] == node2_room || maze_draft[x][y] == node1_room)
                    maze_draft[x][y] = node1_room;
            }
        }

        // Print maze_draft
        for (int x = 0; x < MAZE_SIZE; x++) {
            for (int y = 0; y < MAZE_SIZE; y++) {
                printf("%d\t", maze_draft[x][y]);
            }
            printf("\n");
        }

        // Check if all nodes already in the same room
        bool already_in_the_same_room = true;
        int room_sample = maze_draft[0][0];

        for (int x = 0; x < MAZE_SIZE; x++) {
            for (int y = 0; y < MAZE_SIZE; y++) {
                int room_check = maze_draft[x][y];
                if (room_check != room_sample) {
                    printf("Still not in one room!\n");
                    already_in_the_same_room = false;
                    x = total_nodes; // For breaking the outer loop
                    break;
                }
            }
        }
        
        // All done!!!
        if (already_in_the_same_room == true) {
            printf("DONE!\n\n");

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

            break;
        }
        
        printf("\n");
    }

    return maze_draft;
}

int main(int argc, const char * argv[]) {
    printf("Hello, World!\n");
    
    maze();
    return 0;
}
