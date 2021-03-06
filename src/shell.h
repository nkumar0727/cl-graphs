#pragma once

#include "Graph.h"
#include <string>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// SHELL STRUCTURES AND VARIABLES                                          //
/////////////////////////////////////////////////////////////////////////////

static struct Command {
    std::string op;
    std::string arg;
} cmd;

// Commands and Messages
const std::string prompt("--> ");
const std::string helpCmd("help");
const std::string newCmd("new");
const std::string listCmd("list");
const std::string loadCmd("load");
const std::string clearCmd("clear");
const std::string quitCmd("quit");

const std::string writeCmd("write");
const std::string adjCmd("adj");
const std::string matrixCmd("matrix");
const std::string addCmd("add");
const std::string removeCmd("remove");
const std::string edgeCmd("edge");
const std::string nedgeCmd("nedge");
const std::string algoCmd("algo"); 

// General Main Shell Messages
const std::string welcomeMessage("QuickGraph - a simple graph creation software\nAuthor: Nikhil Kumar 2017");
const std::string invalidCmd("\nPlease enter a valid command.");
const std::string helpMessage_main("\nCommands available:\n\nlist -- display graphs files on disk that can be loaded into main memory\nload <graph_file> -- load a graph stored on disk into main memory (extension MUST be .graph)\nnew -- enter a live graph creation shell in which graph structures can be created on the fly, and written to disk\nquit -- exit the graph shell");
const std::string mainMessage("Main Menu\nType \"help\" to see all available commands.");

// Load Graph Messages
const std::string graphLoc("../graphFiles/");
const std::string failLoad("\nPlease re-type filename. Type \"list\" to see available files on disk.");
const std::string failLoad_n1("\nUnable to open ");
const std::string failLoad_n2("\nFile does not contain \".graph\" extension: ");
const std::string goodLoad("\nFile has been loaded properly: ");

// Live Graph Messages
const std::string liveMessage("Live Graph Creation Environment\nType \"help\" to see all available commands.");
const std::string emptyWrite("Graph contains no vertices. Unable to write empty file to disk.");
const std::string goodWrite("File has been wrtten properly: ");
const std::string failWrite("Please re-type filename.");
const std::string failWrite_n1("\nUnable to open ");
const std::string failWrite_n2("File does not contain \".graph\" extension: ");
const std::string helpMessage_live("Commands available:\n\nwrite <graph name> -- writes graph in main memory to the disk (\".graph\" extension required), and will overwrite any existing file with the same name\nadj -- displays graph as an adjacency list\nmatrix -- displays graph as an adjacency matrix\nadd <vertex 1>,<vertex 2>,... -- inserts named vertices into the graph\nremove <vertex 1>,<vertex 2>,... -- removes named vertices from the graph\nedge <vertex 1>,<vertex 2>,<weight> -- creates edge from vertex 1 to vertex 2 using weight specified (overwrites any existing edge from vertex 1 to vertex 2)\nnedge <vertex 1>,<vertex 2> -- removes edge from vertex 1 to vertex 2\nalgo -- enters graph algorithm interface\nquit -- go back to main shell");
const std::string failAddVertex("Vertex could not be added: ");
const std::string failRemoveVertex("Vertex could not be removed: ");
const std::string failVertexExist("A vertex does not exist: ");
const std::string overwriteEdge("(Overwrote existing edge) Edge created: ");
const std::string successEdge("Edge created: ");
const std::string failEdgeExist("An edge between the following could not be found: ");
const std::string successRemove("Edge removed: ");
const std::string successVertexAdd("Vertex was added: ");
const std::string successVertexRemove("Vertex was removed: ");

/////////////////////////////////////////////////////////////////////////////
// AUXILIARY FUNCTIONS                                                     //
/////////////////////////////////////////////////////////////////////////////

/*
 * Clears contents of string buffer.
 *
 * @param buf, the string buffer
 * @return buf, the cleared buffer, by reference
 */
void clearBuffer(std::stringstream& buf);

/*
 * Tokenizes string by delimiter and places tokens into a vector.
 *
 * @param tokens, the tokenized strings returned by reference
 * @param str, the string to tokenize
 * @param delim, the delimiter for the tokenizing process
 */
void tokenizeString(std::vector<std::string>& tokens, std::string& str, 
		char delim);

/////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTIONS                                                          //
/////////////////////////////////////////////////////////////////////////////

/*
 * Displays shell prompt.
 *
 * Can choose from 5 options:
 *      ---> help
 *         Displays a help menu with instructions on how to use the Graphs
 *         program.
 *
 *		---> clear
 *		   Clears the shell prompt from previous commands.
 *
 *      ---> new
 *         Enters a live graph building environemnt where the user can
 *         manually add and remove vertices, connect vertices, retrieve
 *         information about the current graph, perform graph algorithms, and
 *         save the built graph to the disk.
 *
 *      ---> list
 *         Displays all the graph files currently stored on the disk that can
 *         be loaded for use.
 *
 *      ---> load <graph name>
 *         Loads a graph from the disk to memory for user usage. Can still
 *         modify this graph's vertices and connections, access graph
 *         information, and perform graph algorithms. In addition, the updated
 *         version can be written to the disk.
 *
 *      ---> quit
 *         Exits the shell environemnt, and terminates the running instance of
 *         the program. 
 */
void mainShell();

/*
 * Displays a shell environment for constructing graphs.
 *
 * The user then has the option of saving the graph to the disk, as
 * the live graph built will not be written to the disk by default.
 *
 * Can choose from 5 options:
 *      ---> help
 *         Displays a help menu with instructions on how to use the live shell
 *         in the Graphs program.
 *
 *		---> clear
 *		   Clears the shell prompt from previous commands.
 *      
 *      ---> write <graph name>
 *         Writes the graph created by the user to the disk. If file does not
 *         already exist, a new file will be created and saved. All Graph files
 *         are located in the "graphFiles" directory with the extension ".graph".
 *
 *      ---> adj 
 *         Displays graph represented as an adjacency list in the following
 *         form.
 *         
 *         <graph name>
 *         <vertex 1> | <neighbor 1>[weight 1] <neighbor 2>[weight 2] ...
 *         <vertex 2> | <neighbor 1>[weight 1] <neighbor 2>[weight 2] ...
 *         ...
 *         <vertex n> | <neighbor 1>[weight 1] <neighbor 2>[weight 2] ...
 *
 *      ---> matrix
 *         Displays graph represented as an adjacency matrix in the following
 *         form:
 *
 *         <graph name>
 *         
 *         <vertex 1>
 *         <vertex 2>
 *         ...
 *         <vertex n>
 *
 *         <vertex 1->1 weight> <vertex 1->2 weight> ...
 *         <vertex 2->1 weight> <vertex 2->2 weight> ...
 *         ...
 *         <vertex n->1 weight> <vertex n->2 weight> ...
 *
 * 		   Weights marked by NWT indicate no edge present between the
 * 		   vertices. 
 *
 *      ---> add <vertex 1>,<vertex 2>,<vertex 3> ...
 *         Inserts named vertices into the graph. If the operation should fail
 *         for any vertices, the vertices for which the operation succeeded
 *         will still be added, and an error report will be given for those
 *         that were not added.
 *
 *      ---> remove <vertex 1>,<vertex 2>,<vertex 3> ...
 *         Removes named vertices from the graph. If the operation should fail
 *         for any vertices, the vertices for which the operation succeeded
 *         will still be removed, and an error report will be given for those
 *         that were not removed.

 *
 *      ---> edge <vertex 1>,<vertex 2>,<weight>
 *         Connects vertex 1 with vertex 2 with weight specified. All weights
 *         are signed integers. If the operation should fail, the edge will
 *         not be created, and a precise error report wil be given detailing
 *         the reason.
 *
 *      ---> nedge <vertex 1>,<vertex 2>
 *         Disconnects vertex 1 from vertex 2, thereby assigning a sentinel 
 *         "null weight" value for the edge. If the operation should fail, the
 *         edge will not be removed, and a precise error report will be given
 *         detailing the reason.
 *
 *      ---> algo
 *         Enters the algorithm shell. Here, the user can perform certain
 *         advanced operations on the graph, which are implemented using a
 *         variety of graph algorithms (shortest path, cycle detection,
 *         etc..).
 *
 *      ---> quit
 *         Exits the live shell environment, and brings user back to main
 *         shell. Does not save any changes made to the current graph after
 *         the most recent save. 
 */
void liveShell();

/* THE FOLLOWING IS A LIST OF UNINFORMED SEARCHING PROCEDRUES
 *
 * 			 Paths are printed in the form:
 *
 *       Path found from <vertex 1> to <vertex 2>.
 * 			 Path Cost: <cost>
 *			 <vertex 1> [Weight]---> <vertex a> -->[Weight] ... <vertex 2>
 *
 *			 If no such path exists, the following is printed out:
 *
 *       Could not find path from <vertex 1> to <vertex 2>.
 *
 *    ---> bfs <vertex 1>,<vertex 2> 
 *			 Finds a path from vertex 1 to vertex 2 using a breadth-first
 *			 searching implementation with prefix path cycle prevention. Neighbors
 *			 are examined on a FIFO basis based on some innate ordering; therefore,
 *			 weights will not play a role in selecting the path. The outcome can
 *			 be thought of as, the path with the least number of "hops" from
 *			 vertex 1 to vertex 2.
 *
 *    ---> ucs <vertex 1>,<vertex 2>
 *    	 Finds a path from vertex 1 to vertex 2 using a uniform-cost searching
 *    	 implementation with prefix path cycle prevention. Neighbors are
 *    	 examined on a BIFO basis based on the lowest path cost from source to
 *    	 neighbor; therefore, the weights WILL play a role in selecting the
 *    	 path. Any paths going from <vertex 1> to <vertex 2> with a suboptimal
 *    	 cost will not be dropped in favor of the optimal path. The outcome
 *    	 can be thought of as, the path with the lowest "cost" from vertex 1
 *    	 to vertex 2.
 *
 *    ---> dfs <vertex 1>,<vertex 1>,<depth-limit>
 *       Finds a path from vertex 1 to vertex 2 using a depth-limited
 *       depth-first searching implementation with prefix path cycle
 *       prevention. Neighbors are examined on a LIFO basis based on some
 *       innate ordering; therefore, weights will not play a role in selecting
 *       the path. The <depth-limit> denotes the most number of "hops" the
 *       search is willing to take to find its path. This search does not
 *       guarantee and sort of optimality. 
 *
 *    ---> iddfs <vertex 1>,<vertex 2>
 *       Finds a path from vertex 1 to vertex 2 using an depth-first searching
 *       implementation with iterative deepening and prefix path cycle
 *       prevention. Neighbors are examined on a LIFO basis based on some
 *       innate ordering; therefore, weights will not play a role in selecting
 *       the path. This search does guarantee optimality. THe solution can be
 *       thought of the path with the least "hops" from vertex 1 to vertex 2.
 *
 * THE FOLLOWING IS A LIST OF BASIC SHELL COMMANDS
 *
 *		---> clear
 *		   Clears the shell prompt from previous commands.
 *
 *		---> help
 *       Displays a help menu with instructions on how to use the live shell
 *       in the Graphs program.
 *
 *		---> quit
 *		   Exits the algorithm shell environment, and brings user back to live
 *		   shell.
 */
void algorithmShell();
