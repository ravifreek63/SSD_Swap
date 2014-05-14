/*
 * PageBuffer.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "PageBuffer.h"

PageBuffer::PageBuffer() {
	// TODO Auto-generated constructor stub
}

PageBuffer::~PageBuffer() {
	// TODO Auto-generated destructor stub
}

void PageBuffer::pageOut(void *va) {
	// Writing the page out to swap
	SwapWriter::swapOut (va, 1, 0);
	// Protecting the swapped out page
	if (mprotect (va, PAGE_SIZE, PROT_NONE) == -1){
	    printf("Error In Protecting Page %p \n", va); fflush(stdout);
	}
}
