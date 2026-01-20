all: Main.o Vertex.o 
		g++ -g -Wall Main.o Vertex.o -o dijkstra

Vertex.o: Vertex.h Vertex.cpp	
		g++ -g -Wall -c Vertex.cpp

Main.o: Main.cpp
		g++ -g -Wall -c Main.cpp

clean:
	rm -rf *.o dijkstra
