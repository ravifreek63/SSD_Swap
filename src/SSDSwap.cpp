/*
 * SSDSwap.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "SSDSwap.h"

void* SSDSwap::object_va_to_page_header (void *object_va) {
	  return (void *)((long)object_va & (~(PAGE_SIZE-1)));
}

// The handler to catch SIGSEGV faults on memory access
void SSDSwap::seg_handler (int sig, siginfo_t *si, void *unused){
  if (si->si_code == SEGV_ACCERR){
    void *page_header = SSDSwap::object_va_to_page_header(si->si_addr);
    if (mprotect (page_header, PAGE_SIZE, PROT_READ | PROT_WRITE) == -1){
    	printf ("error in protecting page %p\n", page_header);
    	fflush (stdout);
    } else {
    	SwapReader::swapIn(page_header, PAGE_SIZE, 0);
    }
  }
  else
    handle_error ("Segmentation fault, Code is different");
}

SSDSwap::SSDSwap(struct sigaction sa) {
	_page_buffer = new PageBuffer();
	_sa = sa;
	// defining the segmentation fault handler
	  sa.sa_flags = SA_SIGINFO; // The siginfo_t structure is passed as a second parameter to the user signal handler function
	  sigemptyset(&sa.sa_mask); // Emptying the signal set associated with the structure sigaction_t
	  sa.sa_sigaction = seg_handler; // Assigning the fault handler
	  if (sigaction(SIGSEGV, &sa, NULL) == -1) // Installs the function in sa taken on a segmentation fault
	    handle_error("sigaction");
}

SSDSwap::~SSDSwap() {
	// TODO Auto-generated destructor stub
}

void SSDSwap::swapOut(void *va){
	_page_buffer->pageOut(va, 1);
}
