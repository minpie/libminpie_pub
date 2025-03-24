#!/bin/bash
### A script for build this library.
## vars:
COMMAND_GCC=/usr/bin/gcc
PATH_SOURCECODES=src
PATH_OUTPUT=output


## commands:
$COMMAND_GCC -c -fpic ${PATH_SOURCECODES}/symmetric/libminpieSslaes.c -o ${PATH_OUTPUT}/libminpieSslaes.o
$COMMAND_GCC -shared ${PATH_OUTPUT}/libminpieSslaes.o -o ${PATH_OUTPUT}/libminpieSslaes.so