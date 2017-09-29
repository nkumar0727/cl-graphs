#include <cstdio>
#include <cstring>

typedef unsigned long wd;

class LinearDict {
	private:
		const wd MAX_WORD = 8;
		const wd slots;
		char** dict;
	public:
		LinearDict(wd slots) {
			this->slots = slots;
			dict = new char*[slots];
			for(wd i = 0; i < slots; ++i) {
				dict[i] = new char[MAX_WORD];
			}
		}
		~LinearDict() {
			for(wd i = 0; i < slots; ++i) {
				delete [] dict[i];
			}
			delete [] dict;
		}
		bool insert(const char* word) {
			if(std::strlen(word) > MAX_WORD)
				return false;

			return true;
		}
};
