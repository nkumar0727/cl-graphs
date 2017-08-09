#include <iostream>

#include "Graph.h"
#include "gtest/gtest.h"

#define VCOUNT 10
#define SVCOUNT 4

/*
 * AdjMatrixTest
 *
 * Performs the following tests on an Adjacency Matrix.
 *
 * InitClear
 *     -Correct matrix size and values upon creation and clear.
 * AddRemoveVertex
 *     -Correct addition and removal of rows/columns in matrix.
 * AddRemoveEdge 
 *     -Correct data stored in a correct location in Matrix to denote a
 *     weighted edge.
 * NeighborValidity
 *     -Correct notion of neighbors within a Matrix.
 */

TEST(AdjMatrixTest, InitClear) {
    
    // initialize edgeless matrix
    AdjMatrix m;
    for(Offset i = 0; i < VCOUNT; ++i) {
        m.addVertex();
    }
    Matrix d = m.accessMatrix();

    // test correct edgeless matrix entries
    for(Offset i = 0; i < VCOUNT; ++i) {
        for(Offset j = 0; j < VCOUNT; ++j) {
            ASSERT_EQ(d[i][j], NWT);
        }    
    }

    // test correct size after clear
    m.clear();
    d = m.accessMatrix();
    ASSERT_EQ(d.size(), 0);
    ASSERT_EQ(m.getSize(), 0);
}

TEST(AdjMatrixTest, AddRemoveVertex) {
    AdjMatrix m;

    // test matrix size data when adding vertices
    for(Offset i = 0; i < VCOUNT; ++i) {
        Offset slot = m.addVertex();
        EXPECT_EQ(slot, m.getSize() - 1);
    }
    Matrix d = m.accessMatrix();

    // test correct metadata regarding size
    EXPECT_EQ(d.size(), VCOUNT);
    EXPECT_EQ(d.size(), m.getSize());
    for(Offset i = 0; i < VCOUNT; ++i) {
        EXPECT_EQ(d[i].size(), VCOUNT);
        EXPECT_EQ(d[i].size(), m.getSize());
    }
    EXPECT_EQ(m.getSize(), VCOUNT);

    // test matrix size data when removing vertices
    //     -first, middle, last row/column tests
    //     -step by step size reduction test
    Offset currSize = m.getSize();
    m.removeVertex(0);
    d = m.accessMatrix();
    --currSize;
    EXPECT_EQ(m.getSize(), currSize);
    EXPECT_EQ(d.size(), currSize);
    for(Offset i = 0; i < currSize; ++i) {
        EXPECT_EQ(d[i].size(), currSize);
    }
    m.removeVertex(3);
    d = m.accessMatrix();
    --currSize;
    EXPECT_EQ(m.getSize(), currSize);
    EXPECT_EQ(d.size(), currSize);
    for(Offset i = 0; i < currSize; ++i) {
        EXPECT_EQ(d[i].size(), currSize);
    }
    m.removeVertex(7);
    d = m.accessMatrix();
    --currSize;
    EXPECT_EQ(m.getSize(), currSize);
    EXPECT_EQ(d.size(), currSize);
    for(Offset i = 0; i < currSize; ++i) {
        EXPECT_EQ(d[i].size(), currSize);
    }

    // empty everything
    for(Offset i = 0; i < currSize; ++i) {
        m.removeVertex(0);
    }
    d = m.accessMatrix();

    // matrix should be empty at this point
    EXPECT_EQ(m.getSize(), 0);
    EXPECT_EQ(d.size(), 0);
}

TEST(AdjMatrixTest, AddRemoveEdge) {
    AdjMatrix m;
    for(Offset i = 0; i < SVCOUNT; ++i) {
        m.addVertex();
    }

    /*
     * Convention::
     *     -Matrix A
     *     -N is no edge
     *     -Anything else denotes a weighted edge from i to j
     * 
     * Matrix should look like this:
     *       0 1 2 3
     *
     *   0   N 8 N N 
     *   1   5 N 4 N 
     *   2   1 N N N 
     *   3   N N 3 N 
     */

    m.addEdge(0,1,8);
    m.addEdge(1,0,5);
    m.addEdge(1,2,4);
    m.addEdge(2,0,1);
    m.addEdge(3,2,3);

    // test edge weight addition and correctness
    EXPECT_TRUE(m.isEdge(0,1));
    EXPECT_TRUE(m.isEdge(1,0));
    EXPECT_TRUE(m.isEdge(1,2));
    EXPECT_TRUE(m.isEdge(2,0));
    EXPECT_TRUE(m.isEdge(3,2));
    EXPECT_FALSE(m.isEdge(0,0));
    EXPECT_FALSE(m.isEdge(0,2));
    EXPECT_FALSE(m.isEdge(0,3));
    EXPECT_FALSE(m.isEdge(1,1));
    EXPECT_FALSE(m.isEdge(1,3));
    EXPECT_FALSE(m.isEdge(2,1));
    EXPECT_FALSE(m.isEdge(2,2));
    EXPECT_FALSE(m.isEdge(2,3));
    EXPECT_FALSE(m.isEdge(3,0));
    EXPECT_FALSE(m.isEdge(3,1));
    EXPECT_FALSE(m.isEdge(3,3));

    EXPECT_EQ(m.getWeight(0,1),8);
    EXPECT_EQ(m.getWeight(1,0),5);
    EXPECT_EQ(m.getWeight(1,2),4);
    EXPECT_EQ(m.getWeight(2,0),1);
    EXPECT_EQ(m.getWeight(3,2),3);
    EXPECT_EQ(m.getWeight(0,0),NWT);
    EXPECT_EQ(m.getWeight(0,2),NWT);
    EXPECT_EQ(m.getWeight(0,3),NWT);
    EXPECT_EQ(m.getWeight(1,1),NWT);
    EXPECT_EQ(m.getWeight(1,3),NWT);
    EXPECT_EQ(m.getWeight(2,1),NWT);
    EXPECT_EQ(m.getWeight(2,2),NWT);
    EXPECT_EQ(m.getWeight(2,3),NWT);
    EXPECT_EQ(m.getWeight(3,0),NWT);
    EXPECT_EQ(m.getWeight(3,1),NWT);
    EXPECT_EQ(m.getWeight(3,3),NWT);
    
    m.removeEdge(0,1);
    m.removeEdge(1,0);
    m.removeEdge(1,2);
    m.removeEdge(2,0);
    m.removeEdge(3,2);

    // test for no edges after all edge removal
    for(Offset i = 0; i < SVCOUNT; ++i) {
        for(Offset j = 0; j < SVCOUNT; ++j) {
            EXPECT_EQ(m.getWeight(i,j),NWT);
        }
    }
}

TEST(AdjMatrixTest, NeighborValidity) {
    AdjMatrix m;
    for(Offset i = 0; i < SVCOUNT; ++i) {
        m.addVertex();
    }

    /*
     * Convention::
     *     -Matrix A
     *     -N is no edge
     *     -Anything else denotes a weighted edge from i to j
     * 
     * Matrix should look like this:
     *       0 1 2 3
     *
     *   0   N N N N 
     *   1   5 2 4 7 
     *   2   1 N N N 
     *   3   N N 3 N 
     */

    m.addEdge(1,0,5);
    m.addEdge(1,1,2);
    m.addEdge(1,2,4);
    m.addEdge(1,3,7);
    m.addEdge(2,0,1);
    m.addEdge(3,2,3);

    // test neighbors for different vertices
    std::vector<Offset> nbrs;
    m.getNeighbors(0,nbrs);
    EXPECT_EQ(nbrs.size(), 0);
    nbrs.clear();
    m.getNeighbors(1,nbrs);
    ASSERT_EQ(nbrs.size(), 4);
    EXPECT_EQ(nbrs[0], 0);
    EXPECT_EQ(nbrs[1], 1);
    EXPECT_EQ(nbrs[2], 2);
    EXPECT_EQ(nbrs[3], 3);
    nbrs.clear();
    m.getNeighbors(3, nbrs);
    ASSERT_EQ(nbrs.size(), 1);
    EXPECT_EQ(nbrs[0], 2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
