CC = g++-10
PROG = array_to_obj
FRAG = -Wall
OPTIM = -O2 -mtune=native -march=native
# OPTIM = -O3
STD = -std=c++11
INCLUDE = -I/usr/local/Cellar/nlohmann-json/3.9.1_1/include

$(PROG).out : main.cpp.o
	$(CC) $(FRAG) $(INCLUDE) $(OPTIM) $(STD) main.cpp.o -o $(PROG).out

main.cpp.o: main.cpp
	$(CC) $(FRAG) $(INCLUDE) $(OPTIM) $(STD) main.cpp -c -o main.cpp.o

clean:
	rm *.o || rm *.out
