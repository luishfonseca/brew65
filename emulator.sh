set -e

if [ -z "$CMAKE_TOOLCHAIN_FILE" ]; then
    echo "CMAKE_TOOLCHAIN_FILE is not set, please set it to the path of the Emscripten toolchain file."
    exit 1
fi

CONFIG="Release"
if [ "$1" = "debug" ]; then
    CONFIG="Debug"
fi

mkdir -p build
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE -DCMAKE_BUILD_TYPE:STRING=$CONFIG -G Ninja
cmake --build build --config $CONFIG --target emulator

emrun build/emulator/src/emulator.html
