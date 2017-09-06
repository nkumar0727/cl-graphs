#include "shell.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

int main() {
    mainShell();
    return 0;
}

void mainShell() {
    bool exitShell = false;
    std::cout << welcomeMessage << std::endl;
    while(!exitShell) {
        std::cout << prompt;
        std::getline(std::cin, line);
        clearBuffer(tokenizer);
        tokenizer.str(line);
        if(tokenizer >> token) {
            cmd.op = token;
            if(tokenizer >> token) {
                cmd.arg = token;
                if(tokenizer >> token)
                    std::cout << invalidCmd << std::endl;
                else if(cmd.op == loadCmd){
                    std::cout << "load " << cmd.arg << std::endl;
                    switch(graph.fileLoad(graphLoc + cmd.arg)) {
                        case -1:
                            std::cout << failLoad << failLoad_n1 << cmd.arg
								<< std::endl;
                            break;
                        case -2:
                            std::cout << failLoad << failLoad_n2 << cmd.arg
								<< std::endl;
                            break;
                        case 0:
                            std::cout << goodLoad << cmd.arg << std::endl;
                            // liveShell();
                    }
                }
                else
                    std::cout << invalidCmd << std::endl;
            } 
			else if(cmd.op == quitCmd)
                exitShell = true;
            else if(cmd.op == helpCmd)
                std::cout << helpMessage_main << std::endl;
            else if(cmd.op == listCmd) 
                std::system("ls -h ../graphFiles");
            else if(cmd.op == newCmd) {
                std::cout << "new" << std::endl;
				graph.clear();
                //liveShell();
            }
            else
            	std::cout << invalidCmd << std::endl;
        } 
		else
            std::cout << invalidCmd << std::endl;
    }
}

void liveShell() {
	bool exitShell = false;
    std::cout << liveMessage << std::endl;
    while(!exitShell) {
        std::cout << prompt;
        std::getline(std::cin, line);
        cleanBuffer(tokenizer);
        tokenizer.str(line);
        if(tokenizer >> token) {
            cmd.op = token;
            if(tokenizer >> token) {
				if(cmd.op == writeCmd) {
					if(g.isEmpty())
						std::cout << emptyWrite << std::endl;
					else {
						switch(g.writeFile(cmd.arg) {
							case -1:
								std::cout << failWrite << failWrite_n1 <<
									cmd.arg << std::endl;							
								break;
							case -2:
								std::cout << failWrite << failWrite_n2 <<
									cmd.arg << std::endl;
								break;
							case 0:
								std::cout << goodWrite << cmd.arg << std::endl;	
						}
					}
				}
				else if(cmd.op == addCmd) {
					std::vector<std::string> tokens;
					std::getline(tokenizer, line);
					tokenizeString(tokens, line, ',');
					for(size_t i = 0; i < tokens.size(); ++i) {
						if(!g.addVertex(tokens[i]))
							std::cout << "error" << std::endl;
						else
							std::cout << "Vertex " << tokens[i] <<
								" has been added." << std::endl;
					}
				}
				else if(cmd.op == removeCmd) {
					std::vector<std::string> tokens;
					std::getline(tokenizer, line);
					tokenizeString(tokens, line, ',');
					for(size_t i = 0; i < tokens.size(); ++i) {
						if(!g.removeVertex(tokens[i]))
							std::cout << "error" << std::endl;
						else
							std::cout << "Vertex " << tokens[i] <<
								" has been removed." << std::endl;
					}
				}
				else if(cmd.op == edgeCmd) {
					std::vector<std::string> tokens;
					std::getline(tokenier, line);
					tokenizeString(tokens, line, ',');
					if(tokens.size() != 3)
						std::cout << invalidCmd << std::endl;
					else {
						switch(g.setEdge(tokens[0],tokens[1],tokens[2])) {
							case -1:
								std::cout << "non existant vertex" << std::endl;
								break;
							case 1:
								std::cout << "created, but overwritten" << 
									std::endl;
								break;
							case 0:
								std::cout << "yay, edge created" << std::endl;
						}
					}
				}
				else if(cmd.op == nedgeCmd) {
					std::vector<std::string> tokens;
					std::getline(tokenier, line);
					tokenizeString(tokens, line, ',');
					if(tokens.size() != 2)
						std::cout << invalidCmd << std::endl;
					else {
						switch(g.removeEdge(tokens[0],tokens[1])) {
							case -1:
								std::cout << "non existant vertex" << std::endl;
								break;
							case -2:
								std::cout << "non existant edge" << std::endl;
								break;
							case 0:
								std::cout << "yay, edge removed" << std::endl;
						}
					}
				}
            } 
			else if(cmd.op == helpCmd)
                std::cout << helpMessage_live << std::endl;
			else if(cmd.op == adjCmd)
				g.printAdjList();
			else if(cmd.op == matrixCmd) 
				g.printAdjMatrix();	
			else if(cmd.op == algoCmd) {
				std::cout << "Algos shell" << std::endl;
				// algorithmShell();
			}
			else if(cmd.op == quitCmd)
				exitShell = true;
        }
		else
            std::cout << invalidCmd << std::endl;
    } 
}

void clearBuffer(std::stringstream& buf) {
    buf.str(std::string());
    buf.clear();
}

void tokenizeString(std::vector<std::string>& tokens, std::string& str,
		char delim) {
	size_t start = 0;
	char curr;
	bool acceptIn = false;
	for(size_t j = 0; j < str.size(); ++j) {
		curr = str[j];
		if(curr == delim) {
			tokens.push_back(str.substr(start,j-start));
			start = j+1;
			acceptIn = false;
		}
		else if((curr == ' ' || curr == '\t') && !acceptIn)
			start++;
		else
			acceptIn = true;
	}
	tokens.push_back(str.substr(start,str.size()-start));
}
