#!/bin/bash

clear

rm -rf build/

mkdir -p build

cd build

cmake .. -DCMAKE_C_COMPILER=/opt/homebrew/bin/gcc-13 -DCMAKE_CXX_COMPILER=/opt/homebrew/bin/g++-13

cmake --build .

export OMP_NUM_THREADS=10

ctest --VV
