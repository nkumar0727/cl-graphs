#include "Graph.h"
#include <iostream>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////
// AUXILIARY FUNCTION IMPLEMENTATIONS                                      //
/////////////////////////////////////////////////////////////////////////////

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t");
    if(std::string::npos == first)
        return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last+first+1));
}

bool contains(const std::vector<Key>& v, const Key& k) {
    for(size_t i = 0; i < v.size(); ++i) {
        if(v[i] == k)
            return true;
    }
    return false;
}

int findGraphSlot(const std::vector<Key>& v, const Key& k) {
    for(size_t i = 0; i < v.size(); ++i) {
        if(v[i] == k)
            return i;
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////////////
// ADJACENCY MATRIX IMPLEMENTATION                                         //
/////////////////////////////////////////////////////////////////////////////

AdjMatrix::AdjMatrix() {
    size = 0;
}

Matrix AdjMatrix::accessMatrix() const{
    return data;
}

Offset AdjMatrix::getSize() const{
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

bool AdjMatrix::isEdge(Offset s1, Offset s2) const{
    return data[s1][s2] != NWT;
}

Weight AdjMatrix::getWeight(Offset s1, Offset s2) const{
    return data[s1][s2];
}

void AdjMatrix::getNeighbors(Offset s, std::vector<Offset>& n) const{
    for(Offset i = 0; i < size; ++i) {
        if(data[s][i] != NWT)
            n.push_back(i);
    }
}

void AdjMatrix::print() const{
    for(Offset i = 0; i < size; ++i) {
        for(Offset j = 0; j < size; ++j) {
			if(data[i][j] == NWT)
				std::cout << "NWT" << " ";
			else
            	std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/////////////////////////////////////////////////////////////////////////////
// GRAPH IMPLEMENTATION                                                    //
/////////////////////////////////////////////////////////////////////////////

WeightedDigraph::WeightedDigraph() {}

bool WeightedDigraph::addVertex(const Key& k) {
    if(contains(vertices, k))
        return false;
    vertices.push_back(k); 
    matrix.addVertex();
    return true;
}

bool WeightedDigraph::removeVertex(const Key& k) {
    int p = findGraphSlot(vertices, k);
    if(p == -1)
        return false;
    vertices.erase(vertices.begin() + p);
    matrix.removeVertex(p);
    return true;
}

void WeightedDigraph::clear() {
    vertices.clear();
    matrix.clear();
}

int WeightedDigraph::fileLoad(const std::string& file) {
    if(file.find(graphExt) != file.size() - 6)
	   return -2;
    std::vector<Key> vertex;
    std::vector<Key> neighbor;
    std::string line;
    std::ifstream inFile(file);
    if(inFile.is_open()) {
        this->clear();
        while(std::getline(inFile, line)) {
            size_t splitPos = line.find_first_of('|');
            vertex.push_back(trim(line.substr(0,splitPos)));
            neighbor.push_back(trim(line.substr(splitPos+1,line.size())));
        }
        inFile.close();
    }
    else
        return -1;
    for(size_t i = 0; i < vertex.size(); ++i) {
        this->addVertex(vertex[i]);
    }
    this->loadEdges(vertex,neighbor);
    return 0; 
}

int WeightedDigraph::fileWrite(const std::string& file) const{
   if(file.find(graphExt) != file.size() - 6)
	   return -2;
   std::ofstream outFile(file);
   if(outFile.is_open()) {
       std::vector<Offset> nbrs;
       for(Offset i = 0; i < vertices.size(); ++i) {
          matrix.getNeighbors(i,nbrs); 
          outFile << vertices[i] << " | ";
          for(Offset j = 0; j < nbrs.size(); ++j) {
              outFile << vertices[nbrs[j]] << "[" << matrix.getWeight(i,nbrs[j])
                  << "] ";
          }
          outFile << std::endl;
          nbrs.clear();
       }
       outFile.close(); 
   }
   else
       return -1;
   return 0;
}


int WeightedDigraph::setEdge(const Key& k1, const Key& k2, Weight w) {
    int p1 = findGraphSlot(vertices, k1);
    int p2 = findGraphSlot(vertices, k2);
    if(p1 == -1 || p2 == -1)
        return -1;
    int retVal = 0;
    if(matrix.isEdge(p1,p2))
        retVal = 1;
    matrix.addEdge(p1,p2,w);
    return retVal;
}

int WeightedDigraph::removeEdge(const Key& k1, const Key& k2) {
    int p1 = findGraphSlot(vertices, k1);
    int p2 = findGraphSlot(vertices, k2);
    if(p1 == -1 || p2 == -1)
        return -1;
    if(!matrix.isEdge(p1,p2))
        return -2;
    matrix.removeEdge(p1,p2);
    return 0;
}

bool WeightedDigraph::isEdge(const Key& k1, const Key& k2) const{
    int p1 = findGraphSlot(vertices, k1);
    int p2 = findGraphSlot(vertices, k2);
    if(p1 == -1 || p2 == -1) 
        return false;
    return matrix.isEdge(p1,p2);
}

bool WeightedDigraph::getWeight(const Key& k1, const Key& k2, Weight& w) const{
    int p1 = findGraphSlot(vertices, k1);
    int p2 = findGraphSlot(vertices, k2);
    if(p1 == -1 || p2 == -1) 
       return false;
    w = matrix.getWeight(p1,p2); 
    return w == NWT ? false : true;
}

bool WeightedDigraph::getNeighbors(const Key& k, std::vector<Key>& n) const{
    int p = findGraphSlot(vertices, k);
    if(p == -1)
       return false;
    std::vector<Offset> nbr;
    matrix.getNeighbors(p,nbr);
    for(auto itr = nbr.begin(); itr != nbr.end(); ++itr) {
        n.push_back(vertices[*itr]);
    } 
    return true;
}

void WeightedDigraph::print() const{
    std::vector<Offset> nbrs;
    for(Offset i = 0; i < vertices.size(); ++i) {
        matrix.getNeighbors(i,nbrs);
        std::cout << "Vertex " << vertices[i] << " connected to: ";
        for(Offset j = 0; j < nbrs.size(); ++j) {
            std::cout << vertices[nbrs[j]] << "[" << matrix.getWeight(i,nbrs[j]) << "] ";
        }
        std::cout << std::endl;
        nbrs.clear();
    }
}

void WeightedDigraph::loadEdges(std::vector<Key>& vertex, 
        std::vector<Key>& edges) {
    std::string line;
    for(size_t i = 0; i < vertex.size(); ++i) {
        line = edges[i];
        char curr;
        Key nbr;
        Weight wt;
        size_t start = 0;
        bool acceptIn = false;
        for(size_t j = 0; j < line.size(); ++j) {
            curr = line[j];
            if(curr == '[') {
                nbr = line.substr(start,j-start);
                start = j+1;
            }
            else if(curr == ']') {
                wt = std::stoi(line.substr(start,j-start));
                start = j+1;
                acceptIn = false;
                // TODO: provide error messages for setEdge
                this->setEdge(vertex[i],nbr,wt);
            }
            else if((curr == ' ' || curr == '\t') && !acceptIn)
                start++;
            else
                acceptIn = true;
        }
    }
}

bool WeightedDigraph::isEmpty() const{
    return vertices.empty();
}
