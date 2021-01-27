CC = g++
PROG = jsonviewer
OPTIM = -O3 -mtune=native -march=native
STD = -std=c++17
SRC = main.cpp viewer.cpp

$(PROG).out : $(SRC)
	$(CC) $(OPTIM) $(SRC) $(STD) -o $(PROG).out
