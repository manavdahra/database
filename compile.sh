#!/bin/bash

rm -f bin/*
gcc src/row.c src/table.c src/statement.c src/main.c -o bin/main.o
