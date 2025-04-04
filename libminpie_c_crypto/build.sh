#!/bin/bash
### A script for build this library seperately.
## vars:
COMMAND_GCC=/usr/bin/gcc
PATH_SOURCECODES=src
PATH_OUTPUT=output


## commands:
### libminpieSslaes.so:
$COMMAND_GCC -c -fpic ${PATH_SOURCECODES}/symmetric/libminpieSslaes.c -o ${PATH_OUTPUT}/libminpieSslaes.o
$COMMAND_GCC -shared ${PATH_OUTPUT}/libminpieSslaes.o -o ${PATH_OUTPUT}/libminpieSslaes.so

### libminpieAes.so:
$COMMAND_GCC -c -fpic ${PATH_SOURCECODES}/symmetric/libminpieAes.c -o ${PATH_OUTPUT}/libminpieAes.o
$COMMAND_GCC -shared ${PATH_OUTPUT}/libminpieAes.o -o ${PATH_OUTPUT}/libminpieAes.so

### libminpieGmprsa.so:
$COMMAND_GCC -c -fpic ${PATH_SOURCECODES}/asymmetric/libminpieGmprsa.c -o ${PATH_OUTPUT}/libminpieGmprsa.o
$COMMAND_GCC -shared ${PATH_OUTPUT}/libminpieGmprsa.o -o ${PATH_OUTPUT}/libminpieGmprsa.so

# other:
echo "Done!"