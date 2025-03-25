#!/bin/bash
### A script for build this library totally.
## vars:
COMMAND_GCC=/usr/bin/gcc
PATH_SOURCECODES=src
PATH_OUTPUT=output
NAME_THIS_LIB=minpiecrypto


## commands:
### libminpieSslaes.o:
$COMMAND_GCC -c -fpic ${PATH_SOURCECODES}/symmetric/libminpieSslaes.c -o ${PATH_OUTPUT}/libminpieSslaes.o

### libminpieAes.o:
$COMMAND_GCC -c -fpic ${PATH_SOURCECODES}/symmetric/libminpieAes.c -o ${PATH_OUTPUT}/libminpieAes.o

### libminpieGmprsa.o:
$COMMAND_GCC -c -fpic ${PATH_SOURCECODES}/asymmetric/libminpieGmprsa.c -o ${PATH_OUTPUT}/libminpieGmprsa.o

### combine all .o file to one .so file:
$COMMAND_GCC -shared -o ${PATH_OUTPUT}/lib${NAME_THIS_LIB}.so ${PATH_OUTPUT}/libminpieSslaes.o ${PATH_OUTPUT}/libminpieAes.o ${PATH_OUTPUT}/libminpieGmprsa.o
echo "Done!"