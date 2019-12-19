#!/bin/bash
# My first script
# Algo1
g++ -c -fPIC ./CPP/CAlgos.cpp -Wextra -Wall -o ./builds/CAlgos.o -ljsoncpp -std=c++11 -I/usr/include/python2.7 -lpython2.7 -I./builds/CAlgos2.cpp
g++ -shared -Wl,-soname,./builds/libCAlgos.so -o ./builds/libCAlgos.so ./builds/CAlgos.o -ljsoncpp -std=c++11 -I/usr/include/python2.7 -lpython2.7
# Algo2
g++ -c -fPIC ./CPP/CAlgos2.cpp -Wextra -Wall -o ./builds/CAlgos2.o -ljsoncpp -std=c++11 -I/usr/include/python2.7 -lpython2.7 -I./builds/GF.cpp
g++ -shared -Wl,-soname,./builds/libCAlgos2.so -o ./builds/libCAlgos2.so ./builds/CAlgos2.o -ljsoncpp -std=c++11 -I/usr/include/python2.7 -lpython2.7
# GF
g++ -c -fPIC ./CPP/GF.cpp -Wextra -Wall -o ./builds/GF.o -ljsoncpp -std=c++11 -I/usr/include/python2.7 -lpython2.7
g++ -shared -Wl,-soname,./builds/libGF.so -o ./builds/libGF.so ./builds/GF.o -ljsoncpp -std=c++11 -I/usr/include/python2.7 -lpython2.7