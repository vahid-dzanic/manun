#!/bin/bash

rm -rf build
rm -rf install
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_PREFIX_PATH=~/project/stdex/install/cmake
make -j17
ctest
make install
cd ..
