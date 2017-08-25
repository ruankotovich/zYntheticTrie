### C++ Arguments
CC=g++
CF=-std=c++14 -Wall -O2

### Program Arguments
NAME=ttrie

### Compiler Arguments
SRC_P=src

all: merge clean

merge: main.o engine.o trie.o trieNode.o occurrence.o unionData.o geoDistance.o
	$(CC) $(CF) -o $(NAME) main.o engine.o trie.o trieNode.o occurrence.o unionData.o geoDistance.o

main.o: engine.o $(SRC_P)/main.cpp
	$(CC) $(CF) -c $(SRC_P)/main.cpp

engine.o: trie.o geoDistance.o $(SRC_P)/engine.cpp $(SRC_P)/engine.hpp
	$(CC) $(CF) -c $(SRC_P)/engine.cpp

trie.o: trieNode.o unionData.o $(SRC_P)/trie.cpp $(SRC_P)/trie.hpp
	$(CC) $(CF) -c $(SRC_P)/trie.cpp

trieNode.o: occurrence.o $(SRC_P)/trieNode.cpp $(SRC_P)/trieNode.hpp
	$(CC) $(CF) -c $(SRC_P)/trieNode.cpp

occurrence.o: $(SRC_P)/occurrence.cpp $(SRC_P)/occurrence.hpp
	$(CC) $(CF) -c $(SRC_P)/occurrence.cpp

unionData.o: $(SRC_P)/unionData.cpp $(SRC_P)/unionData.hpp
	$(CC) $(CF) -c $(SRC_P)/unionData.cpp

geoDistance.o: $(SRC_P)/geoDistance.cpp $(SRC_P)/geoDistance.hpp
	$(CC) $(CF) -c $(SRC_P)/geoDistance.cpp

clean:
	rm -rf *.o
