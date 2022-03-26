#ifndef SHA256_H
#define SHA256_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned long WORD;             // 32-bit word, change to "long" for 16-bit machines

class Sha256 {
    public:
	void init();
	void update(size_t len);
	void final(BYTE hash[]);
//    private:
	BYTE data[64];
        WORD datalen;
	unsigned long long bitlen;
	WORD state[8];
	void transform();
};

#endif   // SHA256_H
