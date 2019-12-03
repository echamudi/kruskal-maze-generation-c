//
//  definitions.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
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

const int TOTAL_DIRECTIONS = 12;

const int TOP_LEFT = 0;
const int TOP = 1;
const int TOP_RIGHT = 2;

const int RIGHT_TOP = 3;
const int RIGHT = 4;
const int RIGHT_BOTTOM = 5;

const int BOTTOM_RIGHT = 6;
const int BOTTOM = 7;
const int BOTTOM_LEFT = 8;

const int LEFT_BOTTOM = 9;
const int LEFT = 10;
const int LEFT_TOP = 11;



#endif /* definitions_h */
