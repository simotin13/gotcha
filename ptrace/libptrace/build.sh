#!/bin/bash
rm libptrace.a
gcc -c libptrace.c -o libptrace.o
ar rcs libptrace.a libptrace.o

#gcc main.c -L. -lptrace
