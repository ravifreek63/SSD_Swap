/*
 * SwapReader.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "SwapReader.h"


SwapReader::SwapReader() {
	// TODO Auto-generated constructor stub

}

SwapReader::~SwapReader() {
	// TODO Auto-generated destructor stub
}

// Reads the page from the offset in the file, assumes the page to be unprotected
void SwapReader::swapIn (void * va, int np, int off){
	  FILE *f = fopen("swap.txt", "r");
	  fseek(f, off, SEEK_SET);
	  size_t len = fread(va, sizeof(char), np*PAGE_SIZE, f);
	  if (len == 0){
		  fputs ("Error reading swap file\n", stderr); fflush(stdout);
	  } else {
		  if (DEBUG){
			  printf("Read %d bytes from the file\n", len); fflush(stdout);
		  }
	  }
	  fclose (f);
}
