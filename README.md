#  Kruskal Maze Generation

Modified randomized Kruskal's maze generation algorithm written in C.

## Key Difference

- Original algorithm
    - In each iteration, the algorithm will select two random adjacent nodes that belong to two different groups and merge them into one group.

- Modified algorithm
    - In each iteration, if it can select S shaped nine adjacent nodes, it will select it. Or, if it can not select S shaped nine adjacent nodes, the algorithm can select L shaped three adjacent nodes that belong to three different group and merge them into one group.

## Running

Compile & running directly from the desktop

```
clang main.c && ./a.out
```

## Development

### Compiling & Running in Web Browser

We are using emscripten to compile the app to the web browser.

First, let's install emscripten.
```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install 1.39.4-upstream
./emsdk activate 1.39.4-upstream
cd ..
```

Activate PATH and other environment variables in the current terminal.
```
source ./emsdk/emsdk_env.sh
```

Compile C to JS and WebAssembly
```
chmod +x ./emscripten_compile.sh
./emscripten_compile.sh
```

Run python webserver to see the result
```
python3 -m http.server
```

## License

2019 © Ezzat Chamudi

Code is released under Apache-2.0 license
