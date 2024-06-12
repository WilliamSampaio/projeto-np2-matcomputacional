#!/usr/bin/env bash
gcc -Werror -Wall main.c np2.c np2txt.c -o np2bin.out -lpthread -lSDL2 -lmysqlclient
