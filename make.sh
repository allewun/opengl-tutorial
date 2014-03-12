#!/bin/bash

g++ -c main.cpp && g++ main.o -o opengl -framework OpenGL -lglfw3 -lGLEW && ./opengl