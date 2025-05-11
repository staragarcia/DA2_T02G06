#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run cmake to regenerate build files if needed
cmake ..

# Recompile the project (only recompiles what's changed)
make

# Run the compiled binary if it exists
if [[ -x knapsack ]]; then
    cd ..
    ./build/knapsack
else
    echo "Build failed: knapsack binary not found."
    exit 1
fi

cd ..
