/*
 * SwapManager.cpp
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "SwapManager.h"
#include "SwapReader.h"

SwapManager::SwapManager(struct sigaction sa) {
	// TODO Auto-generated constructor stub
	_page_buffer = new PageBuffer();
	_sa = sa;
}

SwapManager::~SwapManager() {
	// TODO Auto-generated destructor stub
}

void SwapManager::remapPage (void *address){
  SwapRange swapRange = addressRegion(address);
  void *page_header = swapRange.getStartAddress();
  swapMapIter iter = _swap_map.find(page_header);
  if  (iter == _swap_map.end() ){
	  printf("Error, cannot swap in page %p does not exist in the page buffer \n", address); fflush(stdout);
	  return;
  }
  SSDRange ssdRange = iter->second;
  if (DEBUG){
 	  printf("seg_handler, page address on %p\n", page_header); fflush(stdout);
   }
  if (mprotect (page_header, PAGE_SIZE, PROT_READ | PROT_WRITE) == -1){
  	printf ("error in protecting page %p\n", page_header);  fflush (stdout);
  } else {
  	SwapReader::swapIn(page_header, swapRange.getNumPages(), ssdRange.getStart());
  }
}

SwapRange SwapManager::swapRange(void *va) {
	SwapRange* swapRange = addressRegion (va);
	SSDRange ssdRange = PageBuffer::pageOut(swapRange->getStartAddress(), swapRange->getNumPages());
	return swapRange;
}

void* SwapManager::object_va_to_page_header (void *object_va) {
	  return (void *)((long)object_va & (~(PAGE_SIZE-1)));
}

SwapRange* SwapManager::addressRegion(void *va){
	SwapRange* swapRange = new SwapRange (1, object_va_to_page_header (va));
	return swapRange;
}

void SwapManager::mapRange(void *va, int offset_s, int offset_e){
	SSDRange* ssdRange = new SSDRange (offset_s, offset_e);
	mapPair mPair = makePair (va, *ssdRange);
	_swap_map.insert(mPair);
}

mapPair SwapManager::makePair(void *va, SSDRange ssdRange){
	return mapPair(va, ssdRange);
}


