/*
 * SSDSwap.h
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include "swap_global.h"
#include "PageBuffer.h"
#include "SwapManager.h"
#include "SwapWriter.h"
#include "SwapReader.h"

using namespace std;

#ifndef SSDSWAP_H_
#define SSDSWAP_H_

// Stores the mapping from virtual address to file offset


class SSDSwap {
private:
	SwapManager* _swap_manager;
	struct sigaction _sa;

public:
	SSDSwap(struct sigaction sa);
	virtual ~SSDSwap();
	static void seg_handler (int sig, siginfo_t *si, void *unused);
	// Function which converts an object's location to the location where its page header resides
	static void *object_va_to_page_header(void *object_va);
	void swapOut(void *va);
};

class SwapRange {

private:
	int _num_pages;
	void *_start_address;
public:
	SwapRange(){
		_num_pages = -1;
		_start_address = NULL;
	}
	SwapRange(int n, void *a){
		_num_pages = n;
		_start_address = a;
	}
	int getNumPages (){
		return _num_pages;
	}
	void *getStartAddress(){
		return _start_address;
	}
};

class SSDRange {
private:
	int _start_off;
	int _end_off;

public:
	SSDRange(){
		_start_off = -1;
		_end_off = -1;
	}

	SSDRange(int s, int e){
		_start_off = s;
		_end_off = e;
	}
	int getStart(){
		return _start_off;
	}
	int getEnd(){
		return _end_off;
	}
};

#endif /* SSDSWAP_H_ */
