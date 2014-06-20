#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/debug/dmesg.h"
#include "driver/timer/systemTimer.h"
#include "types.h"

void* MemoryAllocate(int s) {return malloc(s);};
void MemoryDeallocate(void* ptr){free(ptr);};
void MemoryCopy(void* p1, void* p2, unsigned int size){memcpy(p1,p2,size);};
void LogPrint(const char* m){kprint(m);}
void MicroDelay(unsigned int t){_wait(t);}
void* MemoryReserve(unsigned int length, void* physicalAddress) {return physicalAddress;}

Result PowerOnUsb() {
	volatile u32* mailbox;
	u32 result;

	mailbox = (u32*)0x2000B880;
	while (mailbox[6] & 0x80000000);
	mailbox[8] = 0x80;
	do {
		while (mailbox[6] & 0x40000000);		
	} while (((result = mailbox[0]) & 0xf) != 0);
	return result == 0x80 ? OK : ErrorDevice;
}


