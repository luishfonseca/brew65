set -e

if [ -z "$CMAKE_TOOLCHAIN_FILE" ]; then
    echo "CMAKE_TOOLCHAIN_FILE is not set, please set it to the path of the Emscripten toolchain file."
    exit 1
fi

mkdir -p build
cmake -B build -S . -Wno-dev -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -G Ninja
cmake --build build --config Release --target emulator

emrun build/emulator/src/emulator.html
