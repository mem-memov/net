#include "Scan.h"
#include <stdlib.h>

struct Scan
{
	unsigned char * bytes;
};

struct Scan * Scan_construct(unsigned char * bytes)
{
	struct Scan * this = malloc(sizeof(struct Scan));

	this->bytes = bytes;
	
	return this;
}

void Scan_destruct(struct Scan * this)
{
	free(this);
	this = NULL;
}

size_t Scan_findGaps(struct Scan * this)
{
//	if ( 0 == (*this->gapCount)) {
//		return;
//	}
	
	size_t count = 0;
//	size_t place;
//	
//	for ( place = this->entrySize; place < (*this->nextPlace); place++ ) {
//		
//		Entry_read(this->entry, place);
//		
//		if ( Entry_isEmpty(this->entry) ) {
//			Gaps_addGap(this->gaps, place);
//			count++;
//		}
//		
//		if ( count == (*this->gapCount) ) {
//			return;
//		}
//	}
	
	return count;
}