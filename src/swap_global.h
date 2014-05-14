/*
 * global.h
 *
 *  Created on: May 14, 2014
 *      Author: ravitandon
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "errno.h"
#include <sys/mman.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "assert.h"
#include "string.h"
#include <unordered_map>
#define DEBUG true

#ifndef GLOBAL_H_
#define GLOBAL_H_

int PAGE_SIZE =  sysconf(_SC_PAGE_SIZE); // Each page in page buffer is of size 4KB
struct sigaction sa;
#define handle_error(msg) \
  do {perror (msg); exit(EXIT_FAILURE);} while (0)

#endif /* GLOBAL_H_ */
