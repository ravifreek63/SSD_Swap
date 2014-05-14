/*
 * PageBuffer.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "PageBuffer.h"
#include "SwapWriter.h"

PageBuffer::PageBuffer() {
	// TODO Auto-generated constructor stub
}

PageBuffer::~PageBuffer() {
	// TODO Auto-generated destructor stub
}

void PageBuffer::pageOut(void *va, int np) {
	// Writing the page out to swap
	SwapWriter::swapOut (va, np);
	// Protecting the swapped out page
	if (mprotect (va, np*PAGE_SIZE, PROT_NONE) == -1){
	    printf("Error In Protecting Page %p \n", va); fflush(stdout);
	}
	madvise (va, np*PAGE_SIZE, MADV_DONTNEED); // After swap out the page is advised to be not needed
}
