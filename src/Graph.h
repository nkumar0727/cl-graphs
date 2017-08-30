#pragma once

#include <string>
#include <vector>
#include <climits>

/////////////////////////////////////////////////////////////////////////////
// CUSTOM DATATYPES AND CONSTANTS                                          //
/////////////////////////////////////////////////////////////////////////////

typedef short int Weight; 
typedef unsigned int Offset;
typedef std::string Key;
typedef std::vector<std::vector<Weight>> Matrix;

#define NWT SHRT_MIN       // weight in adjacency matrix corresponding to
                                // lack of edge present between vertices

/////////////////////////////////////////////////////////////////////////////
// AUXILIARY FUNCTION DEFINITIONS                                          //
/////////////////////////////////////////////////////////////////////////////

/*
 * Remove trailing and leading whitespace froms string.
 *
 * @param str, the string to trim
 * @return the trimmed string
 */
std::string trim(const std::string& str);

/*
 * Determine if Key k is present in vector v using linear search.
 *
 * @param v, the vector to search through
 * @param k, the key to search for
 *
 * @return true if key is present
 *         false if key is not present
 */
bool contains(const std::vector<Key>& v, const Key& k);

/*
 * Determine the position in which k is located in v.
 *
 * @param v, the vector to search through
 * @param k, the key to search for
 *
 * @return the position of k in v
 *         -1 if k is not found in v 
 */
int findGraphSlot(const std::vector<Key>& v, const Key& k);

/////////////////////////////////////////////////////////////////////////////
// GRAPH STRUCTURES AND CLASSES                                            //
/////////////////////////////////////////////////////////////////////////////

/*
 * Auxiliary structure used in WeightedDigraph structure.
 *
 * Adjacency matrix structure responsible for keeping track of edges and their
 * respective weights. Implemented using a 2-dimensional dynamic array.
 *
 * Convention dictates that for adjacency matrix A, the value stored in A[i][j] 
 * denotes the weight of the edge starting at i and going to j. This value is
 * equal to the defined NWT if there is no edge starting at i and going
 * to j. Weights are signed, and can be within the range of [SHRT_MIN, SHRT_MAX].
 */
class AdjMatrix {
    private:
        Offset size;
        Matrix data;
    public:
        /* Constructor */
        AdjMatrix();

        /*
         * TESTING PURPOSES ONLY
         */
        Matrix accessMatrix() const;

        /*
         * TESTING PURPOSES ONLY
         */
        Offset getSize() const;

        /*
         * Adds another slot into the square matrix while preserving
         * existing data.
         *
         * @return the offset in array in which slot was added
         */
        Offset addVertex();

        /*
         * Removes a slot from the square matrix, while properly deleting
         * appropriate data and preserving existing data.
         *
         * @param s, the slot to remove
         */
        void removeVertex(Offset s);
        
        /*
         * Removes all entries in matrix, resulting in an empty matrix.
         */
        void clear();

        /*
         * Assigns weight w to data[s1][s2], which denotes the edge going from
         * s1 to s2.
         *
         * @param s1, the first slot in the array
         * @param s2, the second slot in the array
         * @param w, the weight to assign to the edge
         */
        void addEdge(Offset s1, Offset s2, Weight w);
        
        /*
         * Sets data[s1][s2] to value NWT, denoting the lack of an edge
         * from s1 to s2.
         *
         * @param s1, the first slot in the array
         * @param s2, the second slot in the array
         */
        void removeEdge(Offset s1, Offset s2);

        /*
         * Determines if data[s1][s2] is not equal to value NWT,
         * denoting the presence of an edge from s1 to s2.
         *
         * @param s1, the first slot in the array
         * @param s2, the second slot in the array
         *
         * @return true if there is an edge from s1 to s2
         *         false if there is not an edge from s1 to s2
         */
        bool isEdge(Offset s1, Offset s2) const;

        /*
         * Retreives data[s1][s2], which denotes the weight associated with
         * the edge from s1 to s2.
         *
         * @param s1, the first slot in the array
         * @param s2, the second slot in the array
         *
         * @return the weight associated with edge from s1 to s2; data[s1][s2]
         */
        Weight getWeight(Offset s1, Offset s2) const;

        /*
         * Retrieves the neighboring offsets of s that are not equal to
         * NULLWEIGHT; the neighboring vertices of s.
         *
         * @param s, the slot in the array
         * @param n, the list of neighboring offsets returned by reference
         */
        void getNeighbors(Offset s, std::vector<Offset>& n) const;

        /*
         * Prints out contents of matrix to the console in the following
         * format:
         *
         * ...
         */
        void print() const;
};

/*
 * Weighted directed graph structure implemented using an adjacency matrix to
 * keep track of edges and their respective weights, and a dynamic array of
 * vertices in order to maintain a string-key association with vertices.
 */
class WeightedDigraph {
    private:
        AdjMatrix matrix;
        std::vector<Key> vertices;

        /*
         * Auxiliary function for fileLoad(const std::string& file).
         * Adds edges to weighted digraph after vertices have been added in
         * the aformentioned function.
         *
         * @param vertex, the vertex keys
         * @param edges, the outgoing edges in 1-to-1 correspondence with
         * the vertex keys
         */
        void loadEdges(std::vector<Key>& vertex, std::vector<Key>& edges);
    public:
        /* Constructor */
        WeightedDigraph();
        
        /*
         * Adds a vertex to the graph.
         * Does not add a vertex if a duplicate key already exists in the
         * graph.
         *
         * @param k, a non-empty string key of arbitrary length
         * 
         * @return true, if the vertex was successfully added
         *         false, if the vertex could not be added due k already
         *         existing
         */
        bool addVertex(const Key& k);

        /*
         * Removes a vertex from the graph.
         * Severs any existing connections vertex may have with other vertices.
         * Does nothing if vertex does not exist in the graph.
         *
         * @param k, the name of the vertex to remove
         * 
         * @return true, if the vertex could be removed
         *         false, if no such vertex exists in graph
         */
        bool removeVertex(const Key& k);
       
        /*
         * Removes every edge and vertex from the graph.
         * Previous in-memory graph contents are destroyed.
         */ 
        void clear();
       
        /*
         * Clears current graph. Then loads a graph specified by the formatted
         * file. File must hold the .graph extension. For example: test.graph
         * File must be in the following specialized format:
         *
         * <root_vertex1> | <adj_vertex1>,<weight1> <adj_vertex2>,<weight2> ...
         * <root_vertex2> | <adj_vertex1>,<weight1> <adj_vertex2>,<weight2> ...
         * ...
         *
         * @param file, name of the file to load graph from
         *
         * @return 0 upon successful load
         *        -1 upon unsuccessful load due to inability to open file
         *        -2 upon unsuccessful load due to incorrect file extension
         *        and/or format
         */
         int fileLoad(const std::string& file);
      
        /*
         * Writes the current graph to the disk using the file name specified.
         * Will overwrite a file with the same name with new contents. File
         * must hold the .graph extension. For example: test.graph.
         *
         * @param file, the name of the file to write to disk
         *
         * @return 0 upon successful write
         *        -1 upon unsuccessful write due to inability to open file
         *        -2 upon unsuccessful write due to incorrect file extension 
         */ 
        int fileWrite(const std::string& file) const;
         
        /*
         * Sets the weight associated with the edge going from k1 to k2 to
         * value w.
         * Edges exist based on a "from-to" logic.
         *
         * For example, if there is an edge ("Chicago","New York".9000), then
         * setWeight("Chicago","New York",10) will assign the weight of the
         * edge going from "Chicago" to "New York" to be 10.
         *
         * @param k1, vertex where edge starts
         * @param k2, vertex where edge ends
         * @param w, weight of the edge
         *
         * @return 0 if edge was successfully created
         *        -1 if edge was unsuccesfully created due to k1 or k2 not
         *        existing 
         *         1 if edge was successfully created, but overwrote an
         *         existing edge weight between k1 and k2
         */ 
        int setEdge(const Key& k1, const Key& k2, Weight w);
        
        /*
         * Remove an existing edge between k1 and k2.
         * Edges are removed using a "from-to" logic.
         *
         * For example, removeEdge("Chicago","New York") will remove the
         * weighted edge starting from "Chicago" going to "New York".
         *
         * @param k1, vertex where edge starts
         * @param k2, vertex where edge ends
         *
         * @return 0 if edge was successfully removed
         *        -1 if edge was not successfully removed due to k1 or k2 not
         *        existing
         *        -2 if edge was not successfully removed due to a nonexisting
         *         edge between k1 and k2
         */
        int removeEdge(const Key& k1, const Key& k2);
        
        /*
         * Determines whether or not an edge exists between k1 and k2. 
         * Edges exist based on a "from-to" logic.
         *
         * For example, the result of isEdge("Chicago","New York") will
         * determine if there is an edge starting from "Chicago" going to "New
         * York".
         *
         * @param k1, vertex where edge starts
         * @param k2, vertex where edge ends
         *
         * @return true if there is an edge between k1 and k2 (self connections
         *         are included)
         *         false if there is not an edge between k1 and k2, or if
         *         k1 or k2 do not exist
         */
        bool isEdge(const Key& k1, const Key& k2) const;
        
        /*
         * Retreives the weight associated with the edge going from k1 to k2.
         * Edges exist based on a "from-to" logic.
         *
         * For example, if there is an edge ("Chicago","New York",9000), then
         * getWeight("Chicago","New York",weight) will determine if the edge
         * in fact exists, and return the weight associated by reference if
         * the edge exists.
         *
         * @param k1, vertex where edge starts
         * @param k2, vertex where edge ends
         * @param w, weight associated with edge returned by reference
         *
         * @return true if there is an edge between k1 and k2 (self connections 
         *         are included)
         *         false if there is not an edge between k1 and k2, or if k1
         *         or k2 does not exist
         */
        bool getWeight(const Key& k1, const Key& k2, Weight& w) const;
        
        /*
         * Retrieves the neighbors of vertex k in graph.
         *
         * @param k, vertex from which to get neighbors from
         * @param n, list of neighbors returned by reference
         *
         * @return true upon successful retreival of neighbors of k
         *         false upon unsuccessful retreival of neighbors of k due to
         *         k not existing
         */
        bool getNeighbors(const Key& k, std::vector<Key>& n) const;

        /*
         * Prints out contents of graph to the console in the following
         * format:
         *
         * Vertex <vertex1> connected to: <neighbor1> <neighbor2> ...
         * Vertex <vertex2> connected to: <neighbor1> <neighbor2> ...
         * ...
         */
        void print() const;

        /*
         * TESTING PURPOSES ONLY
         */
        bool isEmpty() const;
};
