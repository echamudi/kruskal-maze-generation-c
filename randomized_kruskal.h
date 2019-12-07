//
//  randomized_kruskal.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//  License: Apache-2.0
//

#ifndef randomized_kruskal_h
#define randomized_kruskal_h

#include <stdlib.h>

#include "definitions.h"
#include "util.h"
#include "print_maze_draft.h"
#include "print_maze.h"

extern unsigned char *available_directions(int x, int y, int **maze_draft, int size, unsigned int options);
extern struct maze randomized_kruskal(bool verbose, int size, unsigned int direction_options);

#endif /* randomized_kruskal_h */
