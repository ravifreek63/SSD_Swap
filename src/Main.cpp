/*
 * Main.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "swap_global.h"
#include "SSDSwap.h"

struct sigaction sa;

SSDSwap* ssdSwap;
void* seg_handler(int sig, siginfo_t *si, void *unused){
	  if (DEBUG){
		  printf("seg_handler, fault on %p\n", si->si_addr); fflush(stdout);
	  }
	  if (si->si_code == SEGV_ACCERR){
		  ssdSwap->seg_handler(si->si_addr);
	  } else
		handle_error ("Segmentation fault, Code is different");
}

void sig_init (){
	// defining the segmentation fault handler
	  sa.sa_flags = SA_SIGINFO; // The siginfo_t structure is passed as a second parameter to the user signal handler function
	  sigemptyset(&sa.sa_mask); // Emptying the signal set associated with the structure sigaction_t
	  sa.sa_sigaction = seg_handler; // Assigning the fault handler
	  if (sigaction(SIGSEGV, &sa, NULL) == -1){ // Installs the function in sa taken on a segmentation fault
	    perror("error :");
	  }
}

void init(){
	sig_init();
	ssdSwap = new SSDSwap();
}

int main(int argc, char *argv[]){
 init ();
 char * ar;
 posix_memalign ((void **)&(ar), PAGE_SIZE, PAGE_SIZE);
 char str1[]="Sample string";
 ssdSwap->swapOut((void *)ar);
 strcpy(ar, str1);
 printf("%s", ar);
 return 0;
}
