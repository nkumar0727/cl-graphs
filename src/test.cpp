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
	char delim = ',';
	std::string line;
	std::vector<std::string> tokens;
	std::getline(std::cin, line);
	tokenizeString(tokens, line, delim);
	for(auto itr = tokens.begin(); itr != tokens.end(); ++itr) {
		std::cout << *itr << std::endl;
	}
	return 0;
}
