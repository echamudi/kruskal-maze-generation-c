//
//  util.c
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/5/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//  License: Apache-2.0
//

#include "util.h"

bool all_unique_3(int x, int y, int z)
{
    bool result = (x != y) && (y != z) && (z != x);
    return result;
}

bool all_unique_array(int length, int array[])
{
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (i == j)
                continue;

            if (array[i] == array[j])
                return false;
        }
    }
    return true;
}

void print_direction(int code)
{
    switch (code)
    {
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
    case LETTER_S:
        printf("letter-S");
        break;
    default:
        printf("ERROR: wrong code");
        break;
    }
}
