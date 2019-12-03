//
//  main.c
//  maze
//
//  Created by Ezzat Chamudi on 11/29/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//  License: Apache-2.0
//

#include <stdio.h>

#include <stdlib.h>

#include <sys/time.h>

#include <stdbool.h>

const int TOTAL_DIRECTIONS = 12;

const int TOP_LEFT = 0;
const int TOP = 1;
const int TOP_RIGHT = 2;

const int RIGHT_TOP  = 3;
const int RIGHT = 4;
const int RIGHT_BOTTOM = 5;

const int BOTTOM_RIGHT = 6;
const int BOTTOM = 7;
const int BOTTOM_LEFT = 8;

const int LEFT_BOTTOM = 9;
const int LEFT = 10;
const int LEFT_TOP = 11;

const int MAZE_SIZE = 4;

const bool ENABlE_DIAGONAL = true;

int ** maze_draft;

void print_direction(int code) {
    switch (code) {
        case TOP_LEFT:
            printf("top left");
            break;
        case TOP:
            printf("top");
            break;
        case TOP_RIGHT:
            printf("top right");
            break;
        case RIGHT_TOP:
            printf("right top");
            break;
        case RIGHT:
            printf("right");
            break;
        case RIGHT_BOTTOM:
            printf("right bottom");
            break;
        case BOTTOM_RIGHT:
            printf("bottom right");
            break;
        case BOTTOM:
            printf("bottom");
            break;
        case BOTTOM_LEFT:
            printf("bottom left");
            break;
        case LEFT_BOTTOM:
            printf("left bottom");
            break;
        case LEFT:
            printf("left");
            break;
        case LEFT_TOP:
            printf("left top");
            break;
        default:
            printf("ERROR: wrong code");
            break;
    }
}

void print_maze_draft() {
    // Print maze_draft
    printf("Current maze draft:\n");
    printf("\t");

    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("[%d]\t", i);
    }
    printf("\n");

    for (int x = 0; x < MAZE_SIZE; x++) {
        printf("[%d]\t", x);
        for (int y = 0; y < MAZE_SIZE; y++) {
            printf("%d\t", maze_draft[y][x]);
        }
        printf("\n");
    }
}

bool all_unique(int x, int y, int z) {
    bool result = (x != y) && (y != z) && (z != x);
    return result;
}

unsigned char * available_directions(int x, int y) {
    int legality_counter = 0;

    bool legality[TOTAL_DIRECTIONS] = {false};
    
    bool near_top_border = y == 0;
    bool near_right_border = x == (MAZE_SIZE - 1);
    bool near_bottom_border = y == (MAZE_SIZE - 1);
    bool near_left_border = x == 0;

    // Check top left
    if (ENABlE_DIAGONAL
        && !near_top_border
        && !near_left_border
        && all_unique(maze_draft[x][y], maze_draft[x][y - 1], maze_draft[x - 1][y - 1])) {
        legality[TOP_LEFT] = true;
        legality_counter++;
    }

    // Check top
    if (!near_top_border && (maze_draft[x][y] != maze_draft[x][y - 1])) {
        legality[TOP] = true;
        legality_counter++;
    }
    
    // Check top right
    if (ENABlE_DIAGONAL
        && !near_top_border
        && !near_right_border
        && all_unique(maze_draft[x][y], maze_draft[x][y - 1], maze_draft[x + 1][y - 1])) {
        legality[TOP_RIGHT] = true;
        legality_counter++;
    }

    // Check right top
    if (ENABlE_DIAGONAL
        && !near_right_border
        && !near_top_border
        && all_unique(maze_draft[x][y], maze_draft[x + 1][y], maze_draft[x + 1][y - 1])) {
        legality[RIGHT_TOP] = true;
        legality_counter++;
    }

    // Check right
    if (!near_right_border && (maze_draft[x][y] != maze_draft[x + 1][y])) {
        legality[RIGHT] = true;
        legality_counter++;
    }

    // Check right bottom
    if (ENABlE_DIAGONAL
        && !near_right_border
        && !near_bottom_border
        && all_unique(maze_draft[x][y], maze_draft[x + 1][y], maze_draft[x + 1][y + 1])) {
        legality[RIGHT_BOTTOM] = true;
        legality_counter++;
    }

    // Check bottom right
    if (ENABlE_DIAGONAL
        && !near_bottom_border
        && !near_right_border
        && all_unique(maze_draft[x][y], maze_draft[x][y + 1], maze_draft[x + 1][y + 1])) {
        legality[BOTTOM_RIGHT] = true;
        legality_counter++;
    }

    // Check bottom
    if (!near_bottom_border && (maze_draft[x][y] != maze_draft[x][y + 1])) {
        legality[BOTTOM] = true;
        legality_counter++;
    }
    
    // Check bottom left
    if (ENABlE_DIAGONAL
        && !near_bottom_border
        && !near_left_border
        && all_unique(maze_draft[x][y], maze_draft[x][y + 1], maze_draft[x - 1][y + 1])) {
        legality[BOTTOM_LEFT] = true;
        legality_counter++;
    }

    // Check left bottom
    if (ENABlE_DIAGONAL
        && !near_left_border
        && !near_bottom_border
        && all_unique(maze_draft[x][y], maze_draft[x - 1][y], maze_draft[x - 1][y + 1])) {
        legality[LEFT_BOTTOM] = true;
        legality_counter++;
    }

    // Check left
    if (!near_left_border && (maze_draft[x][y] != maze_draft[x - 1][y])) {
        legality[LEFT] = true;
        legality_counter++;
    }

    // Check left top
    if (ENABlE_DIAGONAL
        && !near_left_border
        && !near_top_border
        && all_unique(maze_draft[x][y], maze_draft[x - 1][y], maze_draft[x - 1][y - 1])) {
        legality[LEFT_TOP] = true;
        legality_counter++;
    }


    unsigned char * array = (unsigned char * ) calloc(legality_counter + 1, sizeof(unsigned char));
    
    array[0] = legality_counter; // First element shows how many items are legal
    
    int index = 1;
    for (int i = 0; i < TOTAL_DIRECTIONS; i++) {
        if (legality[i]) {
            array[index] = i;
            index++;
        };
    }
    
    return array;
}

int ** randomized_kruskal() {
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
    print_maze_draft();
    printf("\n");

    // Create graph
    int ** graph = (int ** ) calloc(total_nodes, sizeof(int * ));
    for (int i = 0; i < total_nodes; i++) {
        graph[i] = (int * ) calloc(total_nodes, sizeof(int));
    }
    
    int pass_number = 0;
    int failed_pass_number = 0;
    int rooms_counter = total_nodes;
    
    while (1) {
        pass_number++;

        int x1 = -1;
        int y1 = -1;
        int x2 = -1;
        int y2 = -1;
        int x3 = -1;
        int y3 = -1;

        x1 = rand() % MAZE_SIZE;
        y1 = rand() % MAZE_SIZE;
        
        unsigned char * directions = available_directions(x1, y1);
        unsigned char total_available_directions = directions[0];
        
        // If the selected node has no available direction, re-random
        if (total_available_directions == 0) {
            free(directions);
            failed_pass_number++;
            continue;
        };

        printf("Pass: %d;\n", pass_number);
        printf("Selected first node: (%d, %d);\n", x1, y1);

        int selected_index = (rand() % total_available_directions) + 1;
        int selected_direction = directions[selected_index];
    
        printf("Available directions:\n");
        for(int i = 1; i < directions[0] + 1; i++) {
            printf(" -> ");
            print_direction(directions[i]);
            printf("\n");
        }
        
        free(directions);
        
        // diagonal flag
        bool is_diagonal;
        if(selected_direction != TOP
           && selected_direction != RIGHT
           && selected_direction != BOTTOM
           && selected_direction != LEFT) {
            is_diagonal = true;
        } else {
            is_diagonal = false;
        }
        
        // get second node coordinate
        switch (selected_direction) {
            case TOP_LEFT:
            case TOP:
            case TOP_RIGHT:
                x2 = x1;
                y2 = y1 - 1;
                break;
            case RIGHT_TOP:
            case RIGHT:
            case RIGHT_BOTTOM:
                x2 = x1 + 1;
                y2 = y1;
                break;
            case BOTTOM_RIGHT:
            case BOTTOM:
            case BOTTOM_LEFT:
                x2 = x1;
                y2 = y1 + 1;
                break;
            case LEFT_BOTTOM:
            case LEFT:
            case LEFT_TOP:
                x2 = x1 - 1;
                y2 = y1;
                break;
            default:
                printf("ERROR: Wrong direction code.");
                return NULL;
        }
        
        // get third node coordinate (if exists)
        if(is_diagonal) {
            switch (selected_direction) {
                case TOP_LEFT:
                case LEFT_TOP:
                    x3 = x1 - 1;
                    y3 = y1 - 1;
                    break;
                case TOP_RIGHT:
                case RIGHT_TOP:
                    x3 = x1 + 1;
                    y3 = y1 - 1;
                    break;
                case BOTTOM_RIGHT:
                case RIGHT_BOTTOM:
                    x3 = x1 + 1;
                    y3 = y1 + 1;
                    break;
                case BOTTOM_LEFT:
                case LEFT_BOTTOM:
                    x3 = x1 - 1;
                    y3 = y1 + 1;
                    break;
                default:
                    printf("ERROR: Wrong diagonal direction code.");
                    return NULL;
            }
        }

        printf("Selected direction: ");
        print_direction(selected_direction);
        printf("\n");
        
        if (is_diagonal) {
            printf("All nodes: (%d, %d), (%d, %d), and (%d, %d);\n", x1, y1, x2, y2, x3, y3);
        } else {
            printf("All nodes: (%d, %d) and (%d, %d);\n", x1, y1, x2, y2);
        }
        
        // Add link in the graph
        int node1_id = x1 * MAZE_SIZE + y1;
        int node2_id = x2 * MAZE_SIZE + y2;
        int node3_id = -1;
        
        if (is_diagonal) {
            node3_id = x3 * MAZE_SIZE + y3;
        }
        
        graph[node1_id][node2_id] = 1;
        graph[node2_id][node1_id] = 1;

        if (is_diagonal) {
            graph[node2_id][node3_id] = 1;
            graph[node3_id][node2_id] = 1;
        }

        // Unify rooms
        int node1_room = maze_draft[x1][y1];
        int node2_room = maze_draft[x2][y2];
        int node3_room = -1;
    
        if (is_diagonal) {
            node3_room = maze_draft[x3][y3];
        }

        for (int x = 0; x < MAZE_SIZE; x++) {
            for (int y = 0; y < MAZE_SIZE; y++) {
                if (maze_draft[x][y] == node1_room || maze_draft[x][y] == node2_room || maze_draft[x][y] == node3_room)
                    maze_draft[x][y] = node1_room;
            }
        }
        
        // Print maze_draft
        print_maze_draft();

        // Recalculate the total rooms
        if (is_diagonal) {
            rooms_counter -= 2;
        } else {
            rooms_counter -= 1;
        }
        printf("Total rooms: %d\n", rooms_counter);

        // All done!!!
        if (rooms_counter == 1) {
            printf("DONE!\n\n");

            // Print graph
            printf("Final graph:\n");
            printf("\t");
            for (int i = 0; i < total_nodes; i++) {
                printf("[%d]\t", i);
            }
            printf("\n");

            for (int x = 0; x < total_nodes; x++) {
                printf("[%d]\t", x);

                for (int y = 0; y < total_nodes; y++) {
                    printf("%d\t", graph[x][y]);
                }
                printf("\n");
            }
            printf("\n");

            // Print all connections
            printf("All connections:\n");
            for (int i = 0; i < total_nodes; i++)
            {
                printf("Node [%d] -> ", i);
                
                for (int j = 0; j < total_nodes; j++) {
                    if (graph[i][j] == 1) {
                        printf("[%d]", j);
                    }
                }
                printf("\n");
            }
            printf("\n");

            break;
        }
    }

    // Print total passes
    printf("Total passes: %d\n", pass_number);
    printf("Total failed passes: %d\n", failed_pass_number);

    printf("\n");

    // Free mems
    for(int i = 0; i < MAZE_SIZE; i++)
        free(maze_draft[i]);
    free(maze_draft);
    
    return graph;
}

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

int main(int argc, const char * argv[]) {
    printf("Kruskal's Maze Generation!\n");

    int ** graph = randomized_kruskal();

    print_maze(graph, MAZE_SIZE);

    // Free mems
    for(int i = 0; i < MAZE_SIZE * MAZE_SIZE; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
