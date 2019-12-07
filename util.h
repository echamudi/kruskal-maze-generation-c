//
//  util.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//  License: Apache-2.0
//

#ifndef util_h
#define util_h

#include <stdio.h>
#include <stdbool.h>
#include "definitions.h"

extern bool all_unique_3(int x, int y, int z);
extern bool all_unique_array(int length, int array[]);
extern void print_direction(int code);

#endif /* util_h */
