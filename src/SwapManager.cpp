/*
 * SwapManager.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "SwapManager.h"

SwapManager::SwapManager(struct sigaction sa) {
	// TODO Auto-generated constructor stub
	_page_buffer = new PageBuffer();
	_sa = sa;
}

SwapManager::~SwapManager() {
	// TODO Auto-generated destructor stub
}

static void SwapManager::remapPage (void *address){
  SwapRange swapRange = addressRegion(address);
  void *page_header = swapRange.getStartAddress();
  SSDRange ssdRange = swapMap.get(page_header);
  if (DEBUG){
 	  printf("seg_handler, page address on %p\n", page_header); fflush(stdout);
   }
  if (mprotect (page_header, PAGE_SIZE, PROT_READ | PROT_WRITE) == -1){
  	printf ("error in protecting page %p\n", page_header);  fflush (stdout);
  } else {
  	SwapReader::swapIn(page_header, swapRange.getNumPages(), ssdRange.getStart());
  }
}

static int SwapManager::swapRange(void *va) {
	SwapRange swapRange = addressRegion (va);
	SSDRange ssdRange = _page_buffer->pageOut(swapRange.getStartAddress(), swapRange.getNumPages());
	return swapRange;
}

static void* SwapManager::object_va_to_page_header (void *object_va) {
	  return (void *)((long)object_va & (~(PAGE_SIZE-1)));
}

static SwapRange SwapManager::addressRegion(void *va){
	SwapRange swapRange(object_va_to_page_header (va), 1);
	return swapRange;
}

void SwapManager::mapRange(void *va, int offset_s, int offset_e){
	SSDRange ssdRange(offset_s, offset_e);
	mapPair mPair = makePair (va, ssdRange);
	swapMap.insert(mPair);
}

static mapPair SwapManager::makePair(void *va, SSDRange ssdRange){
	return mapPair(va, ssdRange);
}


