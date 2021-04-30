#!/bin/sh

# usage: 
# sh -c ./Tools/compile_mod.sh output_file.so source1.c source2.c

gcc -std=c11 -shared -fPIC -Os -Wall -Wextra --pedantic --pedantic-errors -Iinclude -o $*
