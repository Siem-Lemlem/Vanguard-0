#!/bin/bash
# GT-7 Specter build script
# Run from project root: ./build.sh

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_ROOT"

echo "Cleaning old build..."
rm -rf build

echo "Creating build directory..."
mkdir build
cd build

echo "Configuring with CMake..."
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

echo "Building..."
make -j4

if [ $? -eq 0 ]; then
    echo ""
    echo "=========================================="
    echo "BUILD SUCCESSFUL"
    echo "=========================================="
    echo "Run simulation: ./build/vanguard_sim.exe"
    echo "Or from build/: ./vanguard_sim.exe"
else
    echo ""
    echo "BUILD FAILED"
    exit 1
fi
