#ifndef web_h
#define web_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#include "definitions.h"
#include "print_maze.h"
#include "randomized_kruskal.h"
#include "stats.h"
#include "util.h"

extern int web_randomized_kruskal(int size, int direction_options);

#endif /* web_h */


