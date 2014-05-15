/*
 * SSDSwap.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "SSDSwap.h"

// The handler to catch SIGSEGV faults on memory access
void SSDSwap::seg_handler (int sig, siginfo_t *si, void *unused){
  if (DEBUG){
	  printf("seg_handler, fault on %p\n", si->si_addr); fflush(stdout);
  }
  if (si->si_code == SEGV_ACCERR){
	  SwapManager::remapPage(si->si_addr);
  } else
	handle_error ("Segmentation fault, Code is different");

}

SSDSwap::SSDSwap(struct sigaction sa) {
	_swap_manager = new SwapManager (sa);
	// defining the segmentation fault handler
	  sa.sa_flags = SA_SIGINFO; // The siginfo_t structure is passed as a second parameter to the user signal handler function
	  sigemptyset(&sa.sa_mask); // Emptying the signal set associated with the structure sigaction_t
	  sa.sa_sigaction = seg_handler; // Assigning the fault handler
	  if (sigaction(SIGSEGV, &sa, NULL) == -1) // Installs the function in sa taken on a segmentation fault
	    handle_error("Sig Action Error");
}

SSDSwap::~SSDSwap() {
	// TODO Auto-generated destructor stub
}

void SSDSwap::swapOut(void *va){
	_swap_manager->swapRange(va);
}
