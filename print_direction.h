//
//  print_direction.h
//  kruskal-maze-generation-c
//
//  Created by Ezzat Chamudi on 12/3/19.
//  Copyright © 2019 Ezzat Chamudi. All rights reserved.
//
#include <stdio.h>
#include "definitions.h"

#ifndef print_direction_h
#define print_direction_h

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

#endif /* print_direction_h */
