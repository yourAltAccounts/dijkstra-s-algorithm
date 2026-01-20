#include "Vertex.h"
#include <climits>

Vertex::Vertex(){
    this->index = -1;
    this->degree = -1;
    this->distance = INT_MAX; // from <climits>
}

int Vertex::getIndex(){
    return this->index;
}

int Vertex::getDegree(){
    return this->degree;
}

void Vertex::setIndex(int index){
    this->index = index;
}

void Vertex::setDegree(int deg){
    this->degree = deg;
}

int Vertex::getDistance(){
    return this->distance;
}

void Vertex::setDistance(int dis){
    this->distance = dis;
}