//
//  util.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//

#ifndef util_h
#define util_h

#include <stdbool.h>

bool all_unique_3(int x, int y, int z)
{
    bool result = (x != y) && (y != z) && (z != x);
    return result;
}

bool all_unique_array(int length, int array[]) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (i == j) continue;
            
            if (array[i] == array[j]) return false;
        }
    }
    return true;
}
#endif /* util_h */
