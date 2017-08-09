#include "Graph.h"
#include <iostream>

AdjMatrix::AdjMatrix() {
    size = 0;
}

Matrix AdjMatrix::accessMatrix() {
    return data;
}

Offset AdjMatrix::getSize() {
    return size;
}

Offset AdjMatrix::addVertex() {
    std::vector<Weight> v(++size, NWT);
    data.push_back(v);
    for(Offset i = 0; i < size-1; ++i) {
        data[i].push_back(NWT);
    }
    return size-1;
}

void AdjMatrix::removeVertex(Offset s) {
    data.erase(data.begin() + s);
    --size;
    for(Offset i = 0; i < size; ++i) {
        data[i].erase(data[i].begin() + s);
    }
}

void AdjMatrix::clear() {
    data.clear();
    size = 0;
}

void AdjMatrix::addEdge(Offset s1, Offset s2, Weight w) {
    data[s1][s2] = w;
}

void AdjMatrix::removeEdge(Offset s1, Offset s2) {
    data[s1][s2] = NWT;
}

bool AdjMatrix::isEdge(Offset s1, Offset s2) {
    return data[s1][s2] != NWT;
}

Weight AdjMatrix::getWeight(Offset s1, Offset s2) {
    return data[s1][s2];
}

void AdjMatrix::getNeighbors(Offset s, std::vector<Offset>& n) {
    for(Offset i = 0; i < size; ++i) {
        if(data[s][i] != NWT)
            n.push_back(i);
    }
}

void AdjMatrix::print() {
    for(Offset i = 0; i < size; ++i) {
        for(Offset j = 0; j < size; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
