git clone https://github.com/emscripten-core/emsdk.git

cd emsdk
./emsdk install 1.39.4-upstream
./emsdk activate 1.39.4-upstream
cd ..

source ./emsdk/emsdk_env.sh

mkdir dist
cp index.html ./dist/index.html

chmod +x ./emscripten_compile.sh
./emscripten_compile.sh

rm -rf emsdk
