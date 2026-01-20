#include "Vertex.h"
#include <iostream>
#include <climits>

// minHeap functions
void heapify(Vertex* h[], int i, int n) {
    int smallest = i;

    if(2*i <= n && h[2*i]->getDistance() < h[smallest]->getDistance()) { // check if left smaller
        smallest = 2*i;
    }
    if(2*i+1 <= n && h[2*i+1]->getDistance() < h[smallest]->getDistance()) { // check if right smaller
        smallest = 2*i+1;
    }
    
    if(smallest != i) {
        //swap
        Vertex* temp = h[smallest];
        h[smallest] = h[i];
        h[i] = temp;

        heapify(h, smallest, n);
    }
}

Vertex* popRoot(Vertex* h[], int n) {
    Vertex* save = h[1]; // minimum value in h

    h[1] = h[n];
    heapify(h, 1, n-1);

    return save;
}

void buildHeap(Vertex* h[], int n) {
    for(int i = n/2; i > 0; i--) heapify(h, i, n);
}

int main(){

    // start of the initial pipeline that loads the test case file stream from std::cin

    int numOfVertices;
    int numOfEdges;

    if(!std::cin.eof()){
        std::cin >> numOfVertices;
        std::cin >> numOfEdges; // not used
    }
    else{
        std::cout<<"Input not found!"<<std::endl;
        return 1;
    }

    int adjmatrix[numOfVertices][numOfVertices] = {}; // adjacency matrix of G initialized to all 0s

    Vertex vertices[numOfVertices + 1]; // vertex k can be found at vertices[k] if vertices[k].getIndex() != -1

    int startVertice, endVertice, weight;
    while(std::cin >> startVertice >> endVertice >> weight){

        // Here is where you load up the Graph object
        
        adjmatrix[startVertice - 1][endVertice - 1] = weight;
        adjmatrix[endVertice - 1][startVertice - 1] = weight;
        
        // Deal with startVertice in vertices
        if(vertices[startVertice].getIndex() == -1) { // vertex #startVertice has not yet been added to vertices
            vertices[startVertice].setIndex(startVertice);
            vertices[startVertice].setDegree(1);
        } else {
            vertices[startVertice].setDegree(1 + vertices[startVertice].getDegree()); //increment degree by 1
        }
        // Deal with endVertice in vertices
        if(vertices[endVertice].getIndex() == -1) { // vertex #endVertice has not yet been added to vertices
            vertices[endVertice].setIndex(endVertice);
            vertices[endVertice].setDegree(1);
        } else {
            vertices[endVertice].setDegree(1 + vertices[endVertice].getDegree()); //increment degree by 1
        }

    }

    // And here is where you start working on the three tasks
    // Part 1
    std::cout << "The adjacency matrix of G is:" << std::endl;
    for(int row = 0; row < numOfVertices; row++) {
        for(int col = 0; col < numOfVertices; col++) {
            std::cout << adjmatrix[row][col];
            if(col < numOfVertices - 1) std::cout << " "; // add space if NOT final element in the row
        }
        std::cout << std::endl; // end line after each row
    }
    std::cout << std::endl; // skip line after Part 1

    // Part 2
    Vertex* oddDegreeVertices[numOfVertices];
    int numOfOddDegreeVertices = 0;
    std::cout << "The nodes with odd degrees in G are:\nO = {";
    for(Vertex& v : vertices) {
        if(v.getIndex() != -1 && v.getDegree() % 2 == 1) { // v.getIndex() should always != -1, but just to be safe
            std::cout << " " << v.getIndex();
            oddDegreeVertices[numOfOddDegreeVertices] = &v;
            numOfOddDegreeVertices++;
        }
    }
    std::cout << " }\n"; 

    // Part 3
    for(int i = 0; i < numOfOddDegreeVertices; i++) {
        int currNodeIndex = (oddDegreeVertices[i])->getIndex(); // Running Dijsktra's with this node as Source

        for(int j = 1; j <= numOfVertices; j++) { // reset distance in every Vertex object
            vertices[j].setDistance(INT_MAX); 
        }
        vertices[currNodeIndex].setDistance(0); // Node currNodeIndex is 0 away from itself

        bool visited[numOfVertices + 1]{}; // initialized to all false, node j has been visited if visited[j] = true;

        Vertex* minHeap[numOfVertices + 1]; // minHeap of pointers to Vertex objects, organized by ->distance (Note: minHeap[0] is junk)
        int minHeapLength = numOfVertices;
        for(int j = 1; j <= numOfVertices; j++) { // populate minHeap with pointers to all elements from vertices
            minHeap[j] = &(vertices[j]);
        }
        
        // Running Dijsktra's
        while(minHeapLength > 0) { // minHeap is "The Not Considered" so we will run until it's empty
            buildHeap(minHeap, minHeapLength); // must do on every loop because if neighbors have just been relaxed, heap must be re-built
            int currMin = (popRoot(minHeap, minHeapLength))->getIndex(); // Not considered Vertex with smallest distance to Source is currMin
            int distToCurrMin = vertices[currMin].getDistance(); // distance from source to currMin
            minHeapLength--; // popRoot decreases size of minHeap by 1, update minHeapLength accordingly
            visited[currMin] = true; // We are currently "Considering" currMin, so we have removed it from minHeap and mark it visited
            // Relax (unconsidered) neighbors of currMin
            for(int v = 0; v < numOfVertices; v++) { // 0-indexed instead of 1-indexed because adjmatrix[][] is 0-indexed
                int currDistToV = vertices[v+1].getDistance(); // current distance from Source to Vertex v+1
                if(adjmatrix[(currMin - 1)][v] > 0 && !visited[v+1]) { // check if there's an edge between currMin and Vertex v+1, and if it's not considered yet
                    int newDist = distToCurrMin + adjmatrix[(currMin - 1)][v]; // distance from Source to Vertex v+1 IF we take the route through currMin
                    if(newDist < currDistToV) {
                        vertices[v+1].setDistance(newDist); // only relax this neighbor if the route through currMin is faster
                    }
                }
            }
        }
        
        // skip line before each step in Part 3
        std::cout << "\nThe shortest path lengths from Node " << currNodeIndex << " to all other nodes are:" << std::endl;

        for(int nodeNum = 1; nodeNum <= numOfVertices; nodeNum++) { // loop through every node, with respect to this node oddDegreeVertices[i]
            std::cout << "  " << nodeNum << ": " << (vertices[nodeNum].getDistance()) << std::endl;
        }
    }
    return 0;
}
