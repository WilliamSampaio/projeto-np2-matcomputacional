#!/usr/bin/env bash
gcc -Werror -Wall src/*.c -o np2bin.out -lpthread -lSDL2 -lmysqlclient
