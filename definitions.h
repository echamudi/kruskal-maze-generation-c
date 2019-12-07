//
//  definitions.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//  License: Apache-2.0
//

#ifndef definitions_h
#define definitions_h

struct maze
{
    int total_passes;
    int total_failed_passes;
    int size;
    int **graph;
    int total_deg1_nodes;
    int total_deg2_nodes;
    int total_deg3_nodes;
    int total_deg4_nodes;
    int total_nodes;
};

struct coordinate {
    unsigned int x;
    unsigned int y;
};

#define TOTAL_DIRECTIONS 13

#define TOP_LEFT 0
#define TOP 1
#define TOP_RIGHT 2

#define RIGHT_TOP 3
#define RIGHT 4
#define RIGHT_BOTTOM 5

#define BOTTOM_RIGHT 6
#define BOTTOM 7
#define BOTTOM_LEFT 8

#define LEFT_BOTTOM 9
#define LEFT 10
#define LEFT_TOP 11

#define LETTER_S 12

#endif /* definitions_h */
