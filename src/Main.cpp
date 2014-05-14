/*
 * Main.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "swap_global.h"
#include "SSDSwap.h"

struct sigaction sa;

int main(int argc, char *argv[]){
 char * ar;
 posix_memalign ((void **)&(ar), PAGE_SIZE, PAGE_SIZE);
 char str1[]="Sample string";
 SSDSwap * ssdSwap = new SSDSwap (sa);
 ssdSwap->swapOut((void *)ar);
 strcpy(ar, str1);
 printf("%s", ar);
 return 0;
}
