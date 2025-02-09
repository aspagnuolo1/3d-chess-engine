#!/bin/bash

# Pulisce i file compilati
echo "Eseguendo 'make clean'..."
make clean

# Compila tutto
echo "Eseguendo 'make all'..."
make -j$(sysctl -n hw.ncpu) all

# Imposta la variabile DYLD_LIBRARY_PATH
echo "Esportando DYLD_LIBRARY_PATH..."
export DYLD_LIBRARY_PATH=./engine/bin/Debug:$DYLD_LIBRARY_PATH

# Esegue il client
echo "Avviando client..."
./client/bin/Debug/client
