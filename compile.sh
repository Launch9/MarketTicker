#!/bin/bash
# My first script
g++ -c -fPIC CAlgos.cpp -Wextra -Wall -o ./builds/CAlgos.o -ljsoncpp -std=c++11 -I/usr/include/python2.7 -lpython2.7
g++ -shared -Wl,-soname,./builds/libCAlgos.so -o ./builds/libCAlgos.so ./builds/CAlgos.o -ljsoncpp -std=c++11 -I/usr/include/python2.7 -lpython2.7