#include <iostream>

#include "Graph.h"
#include "gtest/gtest.h"

#define PASS 1      // success return value, with side effects
#define SUCCESS 0   // general success return value
#define FAILN1 -1   // failure return value 
#define FAILN2 -2   // failure return value

const std::string goodFile = "../graphFiles/test.graph";
const std::string nonExist = "nonExist.graph";
const std::string badExtension1 = "../graphFiles/noExtension";
const std::string badExtension2 = "../graphFiles/badExtension.wumbo";

/*
 * GraphTest
 *
 * Performs the following tests on a weighted digraph.
 *     -AddRemoveVertex
 *     -AddRemoveEdge
 *     -EdgeExistance
 *     -NeighborValidity
 *     -EmptyGraphOps
 *     -FileLoad
 */
TEST(GraphTest, VertexOps) {
	WeightedDigraph a;
	std::vector<Key> v = {"New York", "Massachusetts" ,"California", "Texas", 
			"Nevada", "Maine", "New York", "new York", "California", "Maine", 
			" Massachusetts", "Massachusetts ", "Random", "     Massachusetts",
			"Massachusetts  ", "massachusetts"};
	
	// tests adding unique vertex key
	for(size_t i = 0; i < 6; ++i) {
		EXPECT_TRUE(a.addVertex(v[i]));
	}

	// tests adding duplicate vertex key
	EXPECT_FALSE(a.addVertex(v[6]));
	EXPECT_FALSE(a.addVertex(v[8]));
	EXPECT_FALSE(a.addVertex(v[9]));

	// test case sensitivity and leading/trailing whitespace
	EXPECT_TRUE(a.addVertex(v[7]));
	EXPECT_TRUE(a.addVertex(v[10]));
	EXPECT_TRUE(a.addVertex(v[11]));

	// test removing existing vertex key
	EXPECT_TRUE(a.removeVertex(v[0]));
	EXPECT_TRUE(a.removeVertex(v[7]));
	EXPECT_TRUE(a.removeVertex(v[2]));

	// test removing nonexistent vertex key
	EXPECT_FALSE(a.removeVertex(v[0]));
	EXPECT_FALSE(a.removeVertex(v[7]));
	EXPECT_FALSE(a.removeVertex(v[2]));
	EXPECT_FALSE(a.removeVertex(v[12]));

	// test case sensitivity and leading/trailing whitespace
	for(size_t i = 13; i < 16; ++i) {
		EXPECT_FALSE(a.removeVertex(v[i]));
	}
}

TEST(GraphTest, EdgeOps) {
	WeightedDigraph a;
	Key random = "Random";
	Weight rw = 45;
	std::vector<Key> v = {"Boston", "Hartford", "Chicago", "Albany", "Sacramento"};
	for(size_t i = 0; i < v.size(); ++i) {
			a.addVertex(v[i]);
	}
	/*
	 * Graph should look as follows (in adjacency list representation):
	 *
	 * Boston --> Hartford(4), Albany(7)
	 * Hartford --> Albany(4), Chicago(10)
	 * Chicago --> Boston(10), Sacramento(12)
	 * Albany --> Sacramento(20), Hartford(4)
	 * Sacramento --> Chicago(12), Boston(18)
	 */

	// test for correct edge creation
	EXPECT_EQ(a.setEdge(v[0],v[1],4), SUCCESS);
	EXPECT_EQ(a.setEdge(v[0],v[3],7), SUCCESS);
	EXPECT_EQ(a.setEdge(v[1],v[3],4), SUCCESS);
	EXPECT_EQ(a.setEdge(v[1],v[2],10), SUCCESS);
	EXPECT_EQ(a.setEdge(v[2],v[0],10), SUCCESS);
	EXPECT_EQ(a.setEdge(v[2],v[4],12), SUCCESS);
	EXPECT_EQ(a.setEdge(v[3],v[4],20), SUCCESS);
	EXPECT_EQ(a.setEdge(v[3],v[1],4), SUCCESS);
	EXPECT_EQ(a.setEdge(v[4],v[2],12), SUCCESS);
	EXPECT_EQ(a.setEdge(v[4],v[0],18), SUCCESS);

	// test for nonexisting vertex edge creation
	ASSERT_EQ(a.setEdge(v[0],random,rw), FAILN1);
	ASSERT_EQ(a.setEdge(random,v[0],rw), FAILN1);
	ASSERT_EQ(a.setEdge(random,random,rw), FAILN1);

	// test for edge existence/non-existence
	EXPECT_TRUE(a.isEdge(v[0],v[1]));
	EXPECT_TRUE(a.isEdge(v[0],v[3]));
	EXPECT_TRUE(a.isEdge(v[1],v[3]));
	EXPECT_TRUE(a.isEdge(v[1],v[2]));
	EXPECT_TRUE(a.isEdge(v[2],v[0]));
	EXPECT_TRUE(a.isEdge(v[2],v[4]));
	EXPECT_TRUE(a.isEdge(v[3],v[4]));
	EXPECT_TRUE(a.isEdge(v[3],v[1]));
	EXPECT_TRUE(a.isEdge(v[4],v[2]));
	EXPECT_TRUE(a.isEdge(v[4],v[0]));

	EXPECT_FALSE(a.isEdge(v[0],v[0]));
	EXPECT_FALSE(a.isEdge(v[0],v[2]));
	EXPECT_FALSE(a.isEdge(v[0],v[4]));
	EXPECT_FALSE(a.isEdge(v[1],v[0]));
	EXPECT_FALSE(a.isEdge(v[1],v[1]));
	EXPECT_FALSE(a.isEdge(v[1],v[4]));
	EXPECT_FALSE(a.isEdge(v[2],v[1]));
	EXPECT_FALSE(a.isEdge(v[2],v[2]));
	EXPECT_FALSE(a.isEdge(v[2],v[3]));
	EXPECT_FALSE(a.isEdge(v[3],v[0]));
	EXPECT_FALSE(a.isEdge(v[3],v[2]));
	EXPECT_FALSE(a.isEdge(v[3],v[3]));
	EXPECT_FALSE(a.isEdge(v[4],v[1]));
	EXPECT_FALSE(a.isEdge(v[4],v[3]));
	EXPECT_FALSE(a.isEdge(v[4],v[4]));

	// test for edge weight correctness
	Weight w;
	EXPECT_TRUE(a.getWeight(v[0],v[1],w));
	EXPECT_EQ(w,4);
	EXPECT_TRUE(a.getWeight(v[0],v[3],w));
	EXPECT_EQ(w,7);
	EXPECT_TRUE(a.getWeight(v[1],v[3],w));
	EXPECT_EQ(w,4);
	EXPECT_TRUE(a.getWeight(v[1],v[2],w));
	EXPECT_EQ(w,10);
	EXPECT_TRUE(a.getWeight(v[2],v[0],w));
	EXPECT_EQ(w,10);
	EXPECT_TRUE(a.getWeight(v[2],v[4],w));
	EXPECT_EQ(w,12);
	EXPECT_TRUE(a.getWeight(v[3],v[4],w));
	EXPECT_EQ(w,20);
	EXPECT_TRUE(a.getWeight(v[3],v[1],w));
	EXPECT_EQ(w,4);
	EXPECT_TRUE(a.getWeight(v[4],v[2],w));
	EXPECT_EQ(w,12);
	EXPECT_TRUE(a.getWeight(v[4],v[0],w));
	EXPECT_EQ(w,18);

	EXPECT_FALSE(a.getWeight(v[0],v[0],w));
	EXPECT_FALSE(a.getWeight(v[0],v[2],w));
	EXPECT_FALSE(a.getWeight(v[0],v[4],w));
	EXPECT_FALSE(a.getWeight(v[1],v[0],w));
	EXPECT_FALSE(a.getWeight(v[1],v[1],w));
	EXPECT_FALSE(a.getWeight(v[1],v[4],w));
	EXPECT_FALSE(a.getWeight(v[2],v[1],w));
	EXPECT_FALSE(a.getWeight(v[2],v[2],w));
	EXPECT_FALSE(a.getWeight(v[2],v[3],w));
	EXPECT_FALSE(a.getWeight(v[3],v[0],w));
	EXPECT_FALSE(a.getWeight(v[3],v[2],w));
	EXPECT_FALSE(a.getWeight(v[3],v[3],w));
	EXPECT_FALSE(a.getWeight(v[4],v[1],w));
	EXPECT_FALSE(a.getWeight(v[4],v[3],w));
	EXPECT_FALSE(a.getWeight(v[4],v[4],w)); 

	// test for edge overwriting edge creation
	EXPECT_EQ(a.setEdge(v[0],v[1],900), PASS);
	EXPECT_TRUE(a.isEdge(v[0],v[1]));
	EXPECT_TRUE(a.getWeight(v[0],v[1],w));
	EXPECT_EQ(w,900);

	// test for edge removal
	EXPECT_EQ(a.removeEdge(random,random), FAILN1);
	EXPECT_EQ(a.removeEdge(random,v[0]), FAILN1);
	EXPECT_EQ(a.removeEdge(v[0],random), FAILN1);

	EXPECT_EQ(a.removeEdge(v[0],v[0]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[0],v[2]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[0],v[4]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[1],v[0]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[1],v[1]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[1],v[4]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[2],v[1]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[2],v[2]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[2],v[3]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[3],v[0]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[3],v[2]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[3],v[3]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[4],v[1]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[4],v[3]), FAILN2);
	EXPECT_EQ(a.removeEdge(v[4],v[4]), FAILN2);

	EXPECT_EQ(a.removeEdge(v[0],v[1]), SUCCESS);
	EXPECT_EQ(a.removeEdge(v[0],v[3]), SUCCESS);
	EXPECT_EQ(a.removeEdge(v[1],v[3]), SUCCESS);
	EXPECT_EQ(a.removeEdge(v[1],v[2]), SUCCESS);
	EXPECT_EQ(a.removeEdge(v[2],v[0]), SUCCESS);
	EXPECT_EQ(a.removeEdge(v[2],v[4]), SUCCESS);
	EXPECT_EQ(a.removeEdge(v[3],v[4]), SUCCESS);
	EXPECT_EQ(a.removeEdge(v[3],v[1]), SUCCESS);
	EXPECT_EQ(a.removeEdge(v[4],v[2]), SUCCESS);
	EXPECT_EQ(a.removeEdge(v[4],v[0]), SUCCESS);
}

TEST(GraphTest, NeighborValidity) {
	WeightedDigraph a;
	Key random = "Random";
	std::vector<Key> v = {"Boston", "Hartford", "Chicago", "Albany", "Sacramento", "Canada"};
	for(size_t i = 0; i < v.size(); ++i) {
		a.addVertex(v[i]);
	}
	std::vector<Key> neighbors;

	a.setEdge(v[0],v[1],4);
	a.setEdge(v[0],v[3],7);
	a.setEdge(v[1],v[3],4);
	a.setEdge(v[1],v[2],10);
	a.setEdge(v[2],v[0],10);
	a.setEdge(v[2],v[4],12);
	a.setEdge(v[3],v[4],20);
	a.setEdge(v[3],v[1],4);
	a.setEdge(v[4],v[2],12);
	a.setEdge(v[4],v[0],18);
	
	/*
	 * Graph should look as follows (in adjacency list representation):
	 *
	 * Boston --> Hartford(4), Albany(7)
	 * Hartford --> Albany(4), Chicago(10)
	 * Chicago --> Boston(10), Sacramento(12)
	 * Albany --> Sacramento(20), Hartford(4)
	 * Sacramento --> Chicago(12), Boston(18)
	 * Canada -->
	 */

	// test nonexisting vertex neighbors
	EXPECT_FALSE(a.getNeighbors(random,neighbors));
	EXPECT_TRUE(neighbors.empty());
	
	// test existing neighbors
	ASSERT_TRUE(a.getNeighbors(v[0],neighbors));
	ASSERT_EQ(neighbors.size(),2);
	EXPECT_TRUE(contains(neighbors,v[1]));
	EXPECT_TRUE(contains(neighbors,v[3]));
	neighbors.clear();

	ASSERT_TRUE(a.getNeighbors(v[1],neighbors));
	ASSERT_EQ(neighbors.size(),2);
	EXPECT_TRUE(contains(neighbors,v[3]));
	EXPECT_TRUE(contains(neighbors,v[2]));
	neighbors.clear();

	ASSERT_TRUE(a.getNeighbors(v[2],neighbors));
	ASSERT_EQ(neighbors.size(),2);
	EXPECT_TRUE(contains(neighbors,v[0]));
	EXPECT_TRUE(contains(neighbors,v[4]));
	neighbors.clear();

	ASSERT_TRUE(a.getNeighbors(v[3],neighbors));
	ASSERT_EQ(neighbors.size(),2);
	EXPECT_TRUE(contains(neighbors,v[4]));
	EXPECT_TRUE(contains(neighbors,v[1]));
	neighbors.clear();
	
	ASSERT_TRUE(a.getNeighbors(v[4],neighbors));
	ASSERT_EQ(neighbors.size(),2);
	EXPECT_TRUE(contains(neighbors,v[0]));
	EXPECT_TRUE(contains(neighbors,v[2]));
	neighbors.clear();
	
	ASSERT_TRUE(a.getNeighbors(v[5],neighbors));
	ASSERT_EQ(neighbors.size(),0);
	neighbors.clear();
}

TEST(GraphTest, EmptyGraphOps) {
	WeightedDigraph a;
	Weight temp;
	std::vector<Key> v = {"Boston", "Hartford"};
	std::vector<Key> n;

	// empty add vertex
	EXPECT_TRUE(a.addVertex(v[0]));
	EXPECT_TRUE(a.removeVertex(v[0]));

	// empty remove vertex
	EXPECT_FALSE(a.removeVertex(v[0]));

	// empty set edge
	EXPECT_EQ(a.setEdge(v[0],v[1],10),FAILN1);

	// empty remove edge
	EXPECT_EQ(a.removeEdge(v[0],v[1]),FAILN1);

	// empty edge detection
	EXPECT_FALSE(a.isEdge(v[0],v[1]));

	// empty weight retrieval
	EXPECT_FALSE(a.getWeight(v[0],v[1],temp));
	
	// empty neighbor retrieval
	EXPECT_FALSE(a.getNeighbors(v[0],n));
}

// TODO: further test for proper extensions and format
TEST(GraphTest, FileLoad) {
	WeightedDigraph a;

	// test incorrect file loads over no existing info
	ASSERT_EQ(a.fileLoad(nonExist), FAILN1);
	ASSERT_TRUE(a.isEmpty());
	ASSERT_EQ(a.fileLoad(badExtension1), FAILN2);
	ASSERT_TRUE(a.isEmpty());
	ASSERT_EQ(a.fileLoad(badExtension2), FAILN2);
	ASSERT_TRUE(a.isEmpty());
/*
	ASSERT_EQ(a.fileLoad(badFormat), FAILN2);
	ASSERT_TRUE(a.isEmpty());
*/
	// test incorrect file loads over existing info
	/*
	 * Graph a should look as follows:
	 *
	 * V1 ---> V2[10], V3[8]
	 * V2 ---> V3[3]
	 * V3 --->
	 */
	Key v1 = "V1";
	Key v2 = "V2";
	Key v3 = "V3";
	Weight one_two = 10;
	Weight one_three = 8;
	Weight two_three = 3;
	a.addVertex(v1);
	a.addVertex(v2);
	a.addVertex(v3);
	a.setEdge(v1,v2,one_two);
	a.setEdge(v1,v3,one_three);
	a.setEdge(v2,v3,two_three);

	EXPECT_EQ(a.fileLoad(nonExist), FAILN1);
	EXPECT_FALSE(a.isEmpty());
	EXPECT_TRUE(a.isEdge(v1,v2));
	EXPECT_TRUE(a.isEdge(v1,v3));
	EXPECT_TRUE(a.isEdge(v2,v3));
	
	ASSERT_EQ(a.fileLoad(badExtension1), FAILN2);
	EXPECT_FALSE(a.isEmpty());
	EXPECT_TRUE(a.isEdge(v1,v2));
	EXPECT_TRUE(a.isEdge(v1,v3));
	EXPECT_TRUE(a.isEdge(v2,v3));
	
	ASSERT_EQ(a.fileLoad(badExtension2), FAILN2);
	EXPECT_FALSE(a.isEmpty());
	EXPECT_TRUE(a.isEdge(v1,v2));
	EXPECT_TRUE(a.isEdge(v1,v3));
	EXPECT_TRUE(a.isEdge(v2,v3));
	/*
	ASSERT_EQ(a.fileLoad(badFormat), FAILN2);
	EXPECT_TRUE(!a.isEmpty());
	EXPECT_TRUE(a.isEdge(v1,v2));
	EXPECT_TRUE(a.isEdge(v1,v3));
	EXPECT_TRUE(a.isEdge(v2,v3));
*/
	// test correct file loads over existing info
	/*
	 * Graph should look as follows after loading from test.graph.
	 *
	 * Boston --> New York[19], Los Angeles[4]
	 * New York --> Houston[28], Hartford[12], Miami[10]
	 * Miami --> San Francisco[9], Boston[4]
	 * San Francisco --> Boston[20], Houston[1], New York[6]
	 * Los Angeles --> Miami[29]
	 * Houston --> Los Angeles[13]
	 * Hartford
	 */
	std::vector<Key> v = {"Boston", "New York", "Miami", "San Francisco",
			"Los Angeles", "Houston", "Hartford"};
	Weight w;
	ASSERT_EQ(a.fileLoad(goodFile), SUCCESS);

	EXPECT_FALSE(a.isEdge(v1,v2));
	EXPECT_FALSE(a.isEdge(v1,v3));
	EXPECT_FALSE(a.isEdge(v2,v3));

	ASSERT_FALSE(a.isEmpty());
	EXPECT_TRUE(a.getWeight(v[0],v[1],w));
	EXPECT_EQ(w,19);
	EXPECT_TRUE(a.getWeight(v[0],v[4],w));
	EXPECT_EQ(w,4);
	EXPECT_TRUE(a.getWeight(v[1],v[5],w));
	EXPECT_EQ(w,28);
	EXPECT_TRUE(a.getWeight(v[1],v[6],w));
	EXPECT_EQ(w,12);
	EXPECT_TRUE(a.getWeight(v[1],v[2],w));
	EXPECT_EQ(w,10);
	EXPECT_TRUE(a.getWeight(v[2],v[3],w));
	EXPECT_EQ(w,9);
	EXPECT_TRUE(a.getWeight(v[2],v[0],w));
	EXPECT_EQ(w,4);
	EXPECT_TRUE(a.getWeight(v[3],v[0],w));
	EXPECT_EQ(w,20);
	EXPECT_TRUE(a.getWeight(v[3],v[5],w));
	EXPECT_EQ(w,1);
	EXPECT_TRUE(a.getWeight(v[3],v[1],w));
	EXPECT_EQ(w,6);
	EXPECT_TRUE(a.getWeight(v[4],v[2],w));
	EXPECT_EQ(w,29);
	EXPECT_TRUE(a.getWeight(v[5],v[4],w));
	EXPECT_EQ(w,13);
	std::vector<Key> hart_nbrs;
	EXPECT_TRUE(a.getNeighbors(v[6],hart_nbrs));
	EXPECT_TRUE(hart_nbrs.empty());
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
