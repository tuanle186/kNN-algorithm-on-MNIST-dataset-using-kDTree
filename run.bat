@echo off

g++ -o main main.cpp kDTree.cpp Dataset.cpp -I . -std=c++11

main.exe

exit