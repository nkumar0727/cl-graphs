#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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


int main() {
  std::string cmd = "add v1,vertex 2, vertex number 4, v";
  std::stringstream buffer(cmd);
  std::string tok;
  buffer >> tok;
  std::cout << tok << std::endl;
  std::getline(buffer, tok);
  std::cout << tok << std::endl;
}
