#include "shell.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

int main() {
    mainShell();
    return 0;
}

void mainShell() {
    exitShell = false;
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
                if(tokenizer >> token) {
                    std::cout << invalidCmd << std::endl;
                }
                else {
                    if(cmd.op == loadCmd) {
                        std::cout << "load " << cmd.arg << std::endl;
                        switch(graph.fileLoad(graphLoc + cmd.arg)) {
                            case -1:
                                std::cout << failLoad << failLoad_n1 << cmd.arg << std::endl;
                                break;
                            case -2:
                                std::cout << failLoad << failLoad_n2 << cmd.arg << std::endl;
                                break;
                            case 0:
                                std::cout << goodLoad << cmd.arg << std::endl;
                                // liveShell();
                        }
                    }
                    else
                        std::cout << invalidCmd << std::endl;
                }
            } else {
                if(cmd.op == quitCmd)
                    exitShell = true;
                else if(cmd.op == helpCmd)
                    std::cout << helpMessage_main << std::endl;
                else if(cmd.op == listCmd) 
                    std::system("ls -h ../graphFiles");
                else if(cmd.op == newCmd) {
                    std::cout << "new" << std::endl;
                    //liveShell();
                }
                else
                    std::cout << invalidCmd << std::endl;
            }
        } else {
            std::cout << invalidCmd << std::endl;
        }
    }
}

void liveShell(std::string name) {
    std::cout << liveMessage << std::endl;
    while(!exitShell) {
        std::cout << prompt;
        std::getline(std::cin, line);
        cleanBuffer(tokenizer);
        tokenizer.str(line);
        if(tokenizer >> token) {
            cmd.op = token;
            if(tokenizer >> token) {
                 
            } else {
                if(cmd.op == helpCmd)
                    std::cout << helpMessage_live << std::endl;
                else if(cmd.op == write) {
                    if(g.isEmpty())
                        std::cout << emptyWrite << std::endl;
                    else
                        g.writeFile();
                }
            }
        } else {
            std::cout << invalidCmd << std::endl;
        }
    } 
}

void clearBuffer(std::stringstream& buf) {
    buf.str(std::string());
    buf.clear();
}
