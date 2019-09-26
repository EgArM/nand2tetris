#!/usr/bin/env bash

gcc -L/home/eam/Projects/nand2tetris/06/lib -Wall -Werror -o assemble src/assemble.c -lstruct -I./include
