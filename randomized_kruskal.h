//
//  randomized_kruskal.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//

#include "util.h"
#include "definitions.h"
#include "print_direction.h"
#include "print_maze_draft.h"
#include "print_maze.h"

#ifndef randomized_kruskal_h
#define randomized_kruskal_h

struct coordinate {
    unsigned int x;
    unsigned int y;
};

unsigned char *available_directions(int x, int y, int **maze_draft, int size, unsigned int options)
{
    const unsigned int enable_standard = 0b00000001;
    const unsigned int enable_diagonal = 0b00000010;
    const unsigned int enable_letters  = 0b00000100;

    int legality_counter = 0;

    bool legality[TOTAL_DIRECTIONS] = {false};

    bool near_top_border = y == 0;
    bool near_right_border = x == (size - 1);
    bool near_bottom_border = y == (size - 1);
    bool near_left_border = x == 0;

    bool near_border = near_top_border || near_right_border || near_bottom_border || near_left_border;

    // Check top left
    if ((options & enable_diagonal)
        && !near_top_border
        && !near_left_border
        && all_unique_3(maze_draft[x][y], maze_draft[x][y - 1], maze_draft[x - 1][y - 1]))
    {
        legality[TOP_LEFT] = true;
        legality_counter++;
    }

    // Check top
    if ((options & enable_standard)
        && !near_top_border
        && (maze_draft[x][y] != maze_draft[x][y - 1]))
    {
        legality[TOP] = true;
        legality_counter++;
    }

    // Check top right
    if ((options & enable_diagonal)
        && !near_top_border
        && !near_right_border
        && all_unique_3(maze_draft[x][y], maze_draft[x][y - 1], maze_draft[x + 1][y - 1]))
    {
        legality[TOP_RIGHT] = true;
        legality_counter++;
    }

    // Check right top
    if ((options & enable_diagonal)
        && !near_right_border
        && !near_top_border
        && all_unique_3(maze_draft[x][y], maze_draft[x + 1][y], maze_draft[x + 1][y - 1]))
    {
        legality[RIGHT_TOP] = true;
        legality_counter++;
    }

    // Check right
    if ((options & enable_standard)
        && !near_right_border
        && (maze_draft[x][y] != maze_draft[x + 1][y]))
    {
        legality[RIGHT] = true;
        legality_counter++;
    }

    // Check right bottom
    if ((options & enable_diagonal)
        && !near_right_border
        && !near_bottom_border
        && all_unique_3(maze_draft[x][y], maze_draft[x + 1][y], maze_draft[x + 1][y + 1]))
    {
        legality[RIGHT_BOTTOM] = true;
        legality_counter++;
    }

    // Check bottom right
    if ((options & enable_diagonal)
        && !near_bottom_border
        && !near_right_border
        && all_unique_3(maze_draft[x][y], maze_draft[x][y + 1], maze_draft[x + 1][y + 1]))
    {
        legality[BOTTOM_RIGHT] = true;
        legality_counter++;
    }

    // Check bottom
    if ((options & enable_standard)
        && !near_bottom_border
        && (maze_draft[x][y] != maze_draft[x][y + 1]))
    {
        legality[BOTTOM] = true;
        legality_counter++;
    }

    // Check bottom left
    if ((options & enable_diagonal)
        && !near_bottom_border
        && !near_left_border
        && all_unique_3(maze_draft[x][y], maze_draft[x][y + 1], maze_draft[x - 1][y + 1]))
    {
        legality[BOTTOM_LEFT] = true;
        legality_counter++;
    }

    // Check left bottom
    if ((options & enable_diagonal)
        && !near_left_border
        && !near_bottom_border
        && all_unique_3(maze_draft[x][y], maze_draft[x - 1][y], maze_draft[x - 1][y + 1]))
    {
        legality[LEFT_BOTTOM] = true;
        legality_counter++;
    }

    // Check left
    if ((options & enable_standard)
        && !near_left_border
        && (maze_draft[x][y] != maze_draft[x - 1][y]))
    {
        legality[LEFT] = true;
        legality_counter++;
    }

    // Check left top
    if ((options & enable_diagonal)
        && !near_left_border
        && !near_top_border
        && all_unique_3(maze_draft[x][y], maze_draft[x - 1][y], maze_draft[x - 1][y - 1]))
    {
        legality[LEFT_TOP] = true;
        legality_counter++;
    }

    // Checking letters

    // Check letter S
    if ((options & enable_letters)
        && !near_border)
    {
        int rooms_S[9] = {
            maze_draft[x - 1][y - 1],
            maze_draft[x][y - 1],
            maze_draft[x + 1][y - 1],
            
            maze_draft[x - 1][y],
            maze_draft[x][y],
            maze_draft[x + 1][y],
            
            maze_draft[x - 1][y + 1],
            maze_draft[x][y + 1],
            maze_draft[x + 1][y + 1]
        };

        if (all_unique_array(9, rooms_S)) {
            legality[LETTER_S] = true;
            legality_counter++;
        }
    }

    unsigned char *array = (unsigned char *)calloc(legality_counter + 1, sizeof(unsigned char));

    array[0] = legality_counter; // First element shows how many items are legal

    int index = 1;
    for (int i = 0; i < TOTAL_DIRECTIONS; i++)
    {
        if (legality[i])
        {
            array[index] = i;
            index++;
        };
    }

    return array;
}

struct maze randomized_kruskal(bool verbose, int size, unsigned int direction_options)
{
    struct maze result;

    const int total_nodes = size * size;

    // Create maze draft
    int **maze_draft = (int **)calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        maze_draft[i] = (int *)calloc(size, sizeof(int));
    }

    // Assign each cell in draft an integer identifier
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            maze_draft[x][y] = x * size + y;
        }
    }

    // Print maze_draft
    if (verbose)
    {
        print_maze_draft(maze_draft, size);
        printf("\n");
    }

    // Create graph
    int **graph = (int **)calloc(total_nodes, sizeof(int *));
    for (int i = 0; i < total_nodes; i++)
    {
        graph[i] = (int *)calloc(total_nodes, sizeof(int));
    }

    int pass_number = 0;
    int failed_pass_number = 0;
    int rooms_counter = total_nodes;
    int fail_streak = 0;
    const int max_fail_streak = size * size * 10;

    while (1)
    {
        pass_number++;

        struct coordinate node_mid;

        node_mid.x = rand() % size;
        node_mid.y = rand() % size;

        unsigned char *directions = available_directions(node_mid.x, node_mid.y, maze_draft, size, direction_options);
        unsigned char total_available_directions = directions[0];

        // If the selected node has no available direction, re-random
        if (total_available_directions == 0)
        {
            free(directions);
            failed_pass_number++;
            fail_streak++;
            
            if (fail_streak > max_fail_streak) {
                printf("ERROR: Too much fail streak. Can't combine all rooms using legal directions.\n");
                print_maze(graph, size);
                exit(1);
            }

            continue;
        } else {
            fail_streak = 0;
        }

        if (verbose)
        {
            printf("Pass: %d;\n", pass_number);
            printf("Selected middle node: (%d, %d);\n", node_mid.x, node_mid.y);
        }

        if (verbose)
        {
            printf("Available directions:\n");
            for (int i = 1; i < directions[0] + 1; i++)
            {
                printf(" -> ");
                print_direction(directions[i]);
                printf("\n");
            }
        }

        // Select the direction
        int selected_direction;
        if (directions[total_available_directions] == LETTER_S) {
            // Select letter S if it's available
            selected_direction = directions[total_available_directions];
            
            if (verbose)
            {
                printf("Selected direction is letter-S because why not.");
                printf("\n");
            }
        } else {
            // Otherwise, randomize
            int selected_index = (rand() % total_available_directions) + 1;
            selected_direction = directions[selected_index];

            if (verbose)
            {
                printf("Selected direction (random): ");
                print_direction(selected_direction);
                printf("\n");
            }
        }
 
        free(directions);

        // direction flag
        bool is_diagonal = false;
        bool is_standard = false;
        bool is_letter = false;

        switch (selected_direction) {
            case TOP:
            case RIGHT:
            case BOTTOM:
            case LEFT:
                is_standard = true;
                break;
            case TOP_LEFT:
            case TOP_RIGHT:
            case RIGHT_TOP:
            case RIGHT_BOTTOM:
            case BOTTOM_RIGHT:
            case BOTTOM_LEFT:
            case LEFT_BOTTOM:
            case LEFT_TOP:
                is_diagonal = true;
                break;
            case LETTER_S:
                is_letter = true;
                break;
            default:
                printf("ERROR: Wrong direction code %d.", selected_direction);
                exit(1);
        }

        // get selected node coordinates
        struct coordinate * selected_nodes;
        int total_selected_nodes = -1;
        
        if (is_standard) {
            total_selected_nodes = 2;
            
            selected_nodes = (struct coordinate *) calloc(total_selected_nodes, sizeof(struct coordinate));
            selected_nodes[0] = node_mid;

            switch (selected_direction)
            {
            case TOP:
                selected_nodes[1].x = node_mid.x;
                selected_nodes[1].y = node_mid.y - 1;
                break;
            case RIGHT:
                selected_nodes[1].x = node_mid.x + 1;
                selected_nodes[1].y = node_mid.y;
                break;
            case BOTTOM:
                selected_nodes[1].x = node_mid.x;
                selected_nodes[1].y = node_mid.y + 1;
                break;
            case LEFT:
                selected_nodes[1].x = node_mid.x - 1;
                selected_nodes[1].y = node_mid.y;
                break;
            default:
                break;
            }
        } else if (is_diagonal) {
            total_selected_nodes = 3;

            selected_nodes = (struct coordinate *) calloc(total_selected_nodes, sizeof(struct coordinate));
            selected_nodes[0] = node_mid;

            switch (selected_direction)
            {
            case TOP_LEFT:
            case TOP_RIGHT:
                selected_nodes[1].x = node_mid.x;
                selected_nodes[1].y = node_mid.y - 1;
                break;
            case RIGHT_TOP:
            case RIGHT_BOTTOM:
                selected_nodes[1].x = node_mid.x + 1;
                selected_nodes[1].y = node_mid.y;
                break;
            case BOTTOM_LEFT:
            case BOTTOM_RIGHT:
                selected_nodes[1].x = node_mid.x;
                selected_nodes[1].y = node_mid.y + 1;
                break;
            case LEFT_TOP:
            case LEFT_BOTTOM:
                selected_nodes[1].x = node_mid.x - 1;
                selected_nodes[1].y = node_mid.y;
                break;
            default:
                break;
            }

            switch (selected_direction)
            {
            case TOP_LEFT:
            case LEFT_TOP:
                selected_nodes[2].x = node_mid.x - 1;
                selected_nodes[2].y = node_mid.y - 1;
                break;
            case TOP_RIGHT:
            case RIGHT_TOP:
                selected_nodes[2].x = node_mid.x + 1;
                selected_nodes[2].y = node_mid.y - 1;
                break;
            case RIGHT_BOTTOM:
            case BOTTOM_RIGHT:
                selected_nodes[2].x = node_mid.x + 1;
                selected_nodes[2].y = node_mid.y + 1;
                break;
            case LEFT_BOTTOM:
            case BOTTOM_LEFT:
                selected_nodes[2].x = node_mid.x - 1;
                selected_nodes[2].y = node_mid.y + 1;
                break;
            default:
                break;
            }

        } else if (is_letter && selected_direction == LETTER_S) {
            total_selected_nodes = 9;

            selected_nodes = (struct coordinate *) calloc(total_selected_nodes, sizeof(struct coordinate));
            
            // First row
            selected_nodes[0].x = node_mid.x - 1;
            selected_nodes[0].y = node_mid.y - 1;
            selected_nodes[1].x = node_mid.x;
            selected_nodes[1].y = node_mid.y - 1;
            selected_nodes[2].x = node_mid.x + 1;
            selected_nodes[2].y = node_mid.y - 1;
            
            // Second row
            selected_nodes[3].x = node_mid.x - 1;
            selected_nodes[3].y = node_mid.y;
            selected_nodes[4].x = node_mid.x;
            selected_nodes[4].y = node_mid.y;
            selected_nodes[5].x = node_mid.x + 1;
            selected_nodes[5].y = node_mid.y;
            
            // Last row
            selected_nodes[6].x = node_mid.x - 1;
            selected_nodes[6].y = node_mid.y + 1;
            selected_nodes[7].x = node_mid.x;
            selected_nodes[7].y = node_mid.y + 1;
            selected_nodes[8].x = node_mid.x + 1;
            selected_nodes[8].y = node_mid.y + 1;

        } else {
            printf("FAIL: wrong mode.");
            exit(1);
        }
                
        // Add link in the graph
        
        if (is_standard) {
            int node0_id = selected_nodes[0].x * size + selected_nodes[0].y;
            int node1_id = selected_nodes[1].x * size + selected_nodes[1].y;

            graph[node0_id][node1_id] = 1;
            graph[node1_id][node0_id] = 1;
        } else if (is_diagonal) {
            int node0_id = selected_nodes[0].x * size + selected_nodes[0].y;
            int node1_id = selected_nodes[1].x * size + selected_nodes[1].y;
            int node2_id = selected_nodes[2].x * size + selected_nodes[2].y;

            graph[node0_id][node1_id] = 1;
            graph[node1_id][node0_id] = 1;

            graph[node1_id][node2_id] = 1;
            graph[node2_id][node1_id] = 1;
        } else if (is_letter && selected_direction == LETTER_S) {
            
            int node_id[9];
            
            for (int i = 0; i < 9; i++) {
                node_id[i] = selected_nodes[i].x * size + selected_nodes[i].y;
            }
            
            // First horizontal line
            graph[node_id[0]][node_id[1]] = 1;
            graph[node_id[1]][node_id[0]] = 1;
            graph[node_id[1]][node_id[2]] = 1;
            graph[node_id[2]][node_id[1]] = 1;
            
            // Second horizontal line
            graph[node_id[3]][node_id[4]] = 1;
            graph[node_id[4]][node_id[3]] = 1;
            graph[node_id[4]][node_id[5]] = 1;
            graph[node_id[5]][node_id[4]] = 1;
            
            // Third horizontal line
            graph[node_id[6]][node_id[7]] = 1;
            graph[node_id[7]][node_id[6]] = 1;
            graph[node_id[7]][node_id[8]] = 1;
            graph[node_id[8]][node_id[7]] = 1;

            // First Vertical Line
            graph[node_id[0]][node_id[3]] = 1;
            graph[node_id[3]][node_id[0]] = 1;

            // Third Vertical Line
            graph[node_id[5]][node_id[8]] = 1;
            graph[node_id[8]][node_id[5]] = 1;
        }

        // Unify rooms in maze draft
        bool * merge_room_hashes = (bool *) calloc(total_nodes, sizeof(bool));
        
        for (int i = 0; i < total_selected_nodes; i++) {
            int room_id = maze_draft[selected_nodes[i].x][selected_nodes[i].y];
            merge_room_hashes[room_id] = true;
        }

        int target_room = maze_draft[selected_nodes[0].x][selected_nodes[0].y];
 
        for (int x = 0; x < size; x++)
        {
            for (int y = 0; y < size; y++)
            {
                if (merge_room_hashes[maze_draft[x][y]]) maze_draft[x][y] = target_room;
            }
        }

        // Print maze_draft
        if (verbose)
            print_maze_draft(maze_draft, size);

        // Recalculate the total rooms
        if (is_standard)
        {
            rooms_counter -= 1;
        }
        else if (is_diagonal)
        {
            rooms_counter -= 2;
        }
        else if (is_letter && selected_direction == LETTER_S)
        {
            rooms_counter -= 8;
        }

        if (verbose)
            printf("Total rooms: %d\n", rooms_counter);

        // All done!!!
        if (rooms_counter == 1) {
            break;
        } else {
            if (verbose) printf("\n");
        }
    }

    result.total_deg1_nodes = 0;
    result.total_deg2_nodes = 0;
    result.total_deg3_nodes = 0;
    result.total_deg4_nodes = 0;

    // Print all connections
    for (int i = 0; i < total_nodes; i++)
    {
        int current_degree = 0;
        for (int j = 0; j < total_nodes; j++)
        {
            if (graph[i][j] == 1)
                current_degree++;
        }

        switch (current_degree)
        {
        case 1:
            result.total_deg1_nodes++;
            break;
        case 2:
            result.total_deg2_nodes++;
            break;
        case 3:
            result.total_deg3_nodes++;
            break;
        case 4:
            result.total_deg4_nodes++;
            break;
        default:
            printf("ERROR: Bad degree.");
            exit(1);
        }
    }

    if (verbose)
    {
        printf("DONE!\n\n");

        // Print graph
        printf("Final graph:\n");
        printf("\t");
        for (int i = 0; i < total_nodes; i++)
        {
            printf("[%d]\t", i);
        }
        printf("\n");

        for (int x = 0; x < total_nodes; x++)
        {
            printf("[%d]\t", x);

            for (int y = 0; y < total_nodes; y++)
            {
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

            for (int j = 0; j < total_nodes; j++)
            {
                if (graph[i][j] == 1)
                {
                    printf("[%d]", j);
                }
            }
            printf("\n");
        }
        printf("\n");

        // Print total passes
        printf("Total passes: %d\n", pass_number);
        printf("Total failed passes: %d\n", failed_pass_number);

        printf("\n");
    }

    // Free mems
    for (int i = 0; i < size; i++)
        free(maze_draft[i]);
    free(maze_draft);

    result.total_passes = pass_number;
    result.total_failed_passes = failed_pass_number;
    result.size = size;
    result.graph = graph;
    result.total_nodes = total_nodes;

    return result;
}

#endif /* randomized_kruskal_h */
