#pragma once

#include "Graph.h"
#include <string>
#include <sstream>

/////////////////////////////////////////////////////////////////////////////
// SHELL STRUCTURES AND VARIABLES                                          //
/////////////////////////////////////////////////////////////////////////////

static WeightedDigraph graph;

// Command I/O
static std::string line;
static std::string token;
static bool exitShell;
static std::stringstream tokenizer;

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
const std::string quitCmd("quit");

// General Main Shell Messages
const std::string welcomeMessage("QuickGraph - a simple graph creation software\nAuthor: Nikhil Kumar 2017\nType \"help\" to see all available commands.");
const std::string invalidCmd("Please enter a valid command.\nType \"help\" to see all available commands.");
const std::string helpMessage_main("Commands available:\nlist -- display graphs files on disk that can be loaded into main memory\nload <graph_file> -- load a graph stored on disk into main memory (extension MUST be .graph)\nnew <graph_name> -- enter a live graph creation shell in which graph structures can be created on the fly, and written to disk\nquit -- exit the graph shell");

// Load Graph Messages
const std::string graphLoc("../graphFiles/");
const std::string failLoad("Please re-type filename. Type \"list\" to see avaailable files on disk.");
const std::string failLoad_n1("\nUnable to open ");
const std::string failLoad_n2("\nFile does not contain .graph extension: ");
const std::string goodLoad("File has been loaded properly: ");

// Live Graph Messages
const std::string liveMessage("fill in later...");

/////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTIONS                                                          //
/////////////////////////////////////////////////////////////////////////////

/*
 * Clears contents of string buffer.
 *
 * @param buf, the string buffer
 * @return buf, the cleared buffer, by reference
 */
void clearBuffer(std::stringstream& buf);

/*
 * Displays shell prompt.
 *
 * Can choose from 5 options:
 *      ---> help
 *         Displays a help menu with instructions on how to use the Graphs
 *         program.
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
 *      ---> write
 *         Writes the graph created by the user to the disk. The name initially
 *         specified by the user cannot be changed. If file does not already
 *         exist, a new file will be created and saved. All Graph files are
 *         located in the "graph_files" directory with the extension ".graph".
 *
 *      ---> stats
 *         Displays graph information to the user in the following form.
 *         
 *         <graph name>
 *         <vertex 1> | <neighbor 1> <neighbor 2> ...
 *         <vertex 2> | <neighbor 1> <neighbor 2> ...
 *         ...
 *
 *      ---> matrix
 *         Displays graph represented as an adjacency matrix in the following
 *         form.
 *
 *         <graph name>
 *         <connection 1.1> <connection 1.2> ...
 *         <connection 2.1> ...
 *         ...
 *
 *      ---> add <vertex 1> <vertex 2> ...
 *         Inserts named vertices into the graph. Gives an error report if
 *         there was a problem with adding any vertices.
 *
 *      ---> remove <vertex 1> <vertex 2> ...
 *         Removes named vertices from the graph. Gives an error report if
 *         there was a problem with removing any vertices. 
 *
 *      ---> edge <vertex 1> <vertex 2>
 *         Connects vertex 1 with vertex 2. Gives an error report if there was
 *         a problem with connecting the vertices.
 *
 *      ---> noedge <vertex 1> <vertex 2>
 *         Disconnects vertex 1 from vertex 2. Gives an error report if there
 *         was a problem with disconnecting the vertices.
 *
 *      ---> algo
 *         Enters the algorithm shell. Here, the user can perform certain
 *         advanced operations on the graph, which are implemented using a
 *         variety of graph algorithms (shortest path, cycle detection,
 *         etc..).
 *
 *      ---> quit
 *         Exits the live shell environment. Does not save any changes made to
 *         the current graph after the most recent save. 
 */
void liveShell();

void algorithmShell();
