//
//  util.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//

#ifndef util_h
#define util_h

bool all_unique(int x, int y, int z)
{
    bool result = (x != y) && (y != z) && (z != x);
    return result;
}


#endif /* util_h */
