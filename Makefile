### C++ Arguments
CC=g++
CF=-std=c++14 -Wall -O2

### Program Arguments
NAME=ttrie

### Compiler Arguments
SRC_P=src

all: merge clean

merge: main.o trie.o trieNode.o 
	$(CC) $(CF) -o $(NAME) main.o trie.o trieNode.o

main.o: trie.o $(SRC_P)/main.cpp
	$(CC) $(CF) -c $(SRC_P)/main.cpp

trie.o: trieNode.o $(SRC_P)/trie.cpp $(SRC_P)/trie.hpp
	$(CC) $(CF) -c $(SRC_P)/trie.cpp

trieNode.o: $(SRC_P)/trieNode.cpp $(SRC_P)/trieNode.hpp
	$(CC) $(CF) -c $(SRC_P)/trieNode.cpp

clean:
	rm -rf *.o
