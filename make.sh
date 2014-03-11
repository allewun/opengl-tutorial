#!/bin/bash

g++ -c main.cpp && g++ main.o -o opengl -lsfml-graphics -lsfml-window -lsfml-system && ./opengl