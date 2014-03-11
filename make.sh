#!/bin/bash

g++ -c main.cpp && g++ main.o -o opengl -framework OpenGL -lsfml-graphics -lsfml-window -lsfml-system && ./opengl