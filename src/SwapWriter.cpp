/*
 * SwapWriter.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "SwapWriter.h"

SwapWriter::SwapWriter() {
	// TODO Auto-generated constructor stub
	PageBuffer page

}

SwapWriter::~SwapWriter() {
	// TODO Auto-generated destructor stub
}

// Writes a set number of pages to the offset in the file, assumes the page to be unprotected.
// Page needs to be protected later on.
size_t SwapWriter::swapOut (void * va, int np, int off){
	  FILE *f = fopen("swap.txt", "r");
	  fseek(f, off, SEEK_SET);
	  size_t len = fwrite(va, sizeof(char), np * PAGE_SIZE, f);
	  if (len == 0){
		  fputs ("Error writing swap file\n", stderr); fflush(stdout);
	  } else {
		  if (DEBUG){
			  printf("Read %d bytes from the file\n", len); fflush(stdout);
		  }
	  }
	  fclose (f);
	  return len;
}
