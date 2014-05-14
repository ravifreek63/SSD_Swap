/*
 * SSDSwap.h
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "swap_global.h"

using namespace std;

#ifndef SSDSWAP_H_
#define SSDSWAP_H_

// Stores the mapping from virtual address to file offset
//typedef std::unordered_map <void *,int> swapMap;

class SSDSwap {
private:
	PageBuffer _page_buffer;
	SwapManager _swap_manager;

public:
	SSDSwap();
	virtual ~SSDSwap();
	void seg_handler (int sig, siginfo_t *si, void *unused);
	// Function which converts an object's location to the location where its page header resides
	void *object_va_to_page_header(void *object_va);
	void swapOut(void *va);
};

#endif /* SSDSWAP_H_ */
