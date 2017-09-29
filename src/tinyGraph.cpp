#include <cstdio>
#include <cstring>

// 4 byte u_int = 32 bits
// 512b field = 512 bits = 512 vertex 
// 1kb field = 1024 bits = 1024 vertex

// 4 for 32 bit, 8 for 64 bit
typedef unsigned long wd;
#define WS_BY ((wd)(sizeof(wd))) 	// word size (bytes)
#define WS_BI ((wd)(WS_BY<<3))		// word size (bits)
#define BS_BI ((wd)512)						// block size (bits)
#define BS_BY ((wd)(BS_BI>>3))		// block size (bytes)
#define BSC ((wd)(BS_BY/WS_BY))		// slot count (whole number)
#define SS_BI ((wd)(BS_BI/BSC))		// slot size (bits)
#define SS_BY ((wd)(BS_BY/BSC))		// slot size (bytes)

class Block {
	private:
		wd* arr;
	public:
		Block() {
			arr = new wd[BSC];
			std::memset((void*)arr, 0, BS_BY);
		}
		~Block() {
			delete [] arr;
		}
		void setBit(wd bit) {
			wd sl = bit/WS_BI;
			wd sl_bit = bit%WS_BI;
			arr[sl] |= (1 << sl_bit);
		}
		void clearBit(wd bit) {
			wd sl = bit/WS_BI;
			wd sl_bit = bit%WS_BI;
			arr[sl] &= ~(1 << sl_bit);
		}
		bool isSet(wd bit) {
			wd sl = bit/WS_BI;
			wd sl_bit = bit%WS_BI;
			return (arr[sl] & (1 << sl_bit));
		}
		void print() {
			for(wd i = 0; i < BSC; ++i) {
				printf("Slot %lu: %lu\n",i,arr[i]);
			}
		}
};

class UWDigraph {
	private:
		wd* arr;
	public:
		UWDigraph() {

		}
};

int main() {
	printf("Word size: %lu bytes\n",WS_BY);
	printf("Word size: %lu bits\n",WS_BI);
	printf("Block size: %lu bytes\n",BS_BY);
	printf("Block size: %lu bits\n",BS_BI);
	printf("Block slot size: %lu bytes\n",SS_BY);
	printf("Block slot size: %lu bits\n",SS_BI);
	printf("Block slot count: %lu slots\n",BSC);
	Block a;
	a.print();
	a.setBit(12);
	a.setBit(31);
	a.setBit(32);
	a.setBit(33);
	a.setBit(55);
	a.setBit(63);
	a.setBit(64);
	a.setBit(65);
	a.print();
	if(a.isSet(12)) {
		printf("good\n");
	}
	if(a.isSet(31)) {
		printf("good\n");
	}
	if(a.isSet(32)) {
		printf("good\n");
	}
	if(a.isSet(33)) {
		printf("good\n");
	}
	if(a.isSet(55)) {
		printf("good\n");
	}
	if(a.isSet(63)) {
		printf("good\n");
	}
	if(a.isSet(64)) {
		printf("good\n");
	}
	if(a.isSet(65)) {
		printf("good\n");
	}
	a.clearBit(12);
	a.clearBit(31);
	a.clearBit(32);
	a.clearBit(33);
	a.clearBit(55);
	a.clearBit(63);
	a.clearBit(64);
	a.clearBit(65);
	a.print();
	if(a.isSet(12)) {
		printf("good\n");
	}
	if(a.isSet(31)) {
		printf("good\n");
	}
	if(a.isSet(32)) {
		printf("good\n");
	}
	if(a.isSet(33)) {
		printf("good\n");
	}
	if(a.isSet(55)) {
		printf("good\n");
	}
	if(a.isSet(63)) {
		printf("good\n");
	}
	if(a.isSet(64)) {
		printf("good\n");
	}
	if(a.isSet(65)) {
		printf("good\n");
	}
}
