#!/bin/bash

make clean

make -j$(sysctl -n hw.ncpu) all

export DYLD_LIBRARY_PATH=./engine/bin/Release:$DYLD_LIBRARY_PATH

./client/bin/Release/client