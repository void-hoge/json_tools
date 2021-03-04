CC = g++
PROG = jsonviewer
OPTIM = -O2 -mtune=native -march=native
# OPTIM = -O3
STD = -std=c++17

$(PROG).out : main.cpp.o viewer.cpp.o
	$(CC) $(OPTIM) $(STD) main.cpp.o viewer.cpp.o -o $(PROG).out

main.cpp.o: main.cpp
	$(CC) $(OPTIM) $(STD) main.cpp -c -o main.cpp.o

viewer.cpp.o: viewer.cpp
	$(CC) $(OPTIM) $(STD) viewer.cpp -c -o viewer.cpp.o
