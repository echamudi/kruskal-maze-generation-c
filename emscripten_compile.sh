emcc \
    web.c \
    definitions.c \
    print_maze_draft.c \
    print_maze.c \
    randomized_kruskal.c \
    stats.c \
    util.c \
    \
    -o ./dist/script.js \
    \
    -s EXPORTED_FUNCTIONS='[
        "_web_randomized_kruskal"
    ]' \
    \
    -s EXTRA_EXPORTED_RUNTIME_METHODS='[
        "ccall",
        "cwrap"
    ]' \
    \
    -s TOTAL_MEMORY=536870912
