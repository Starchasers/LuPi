#include "lib/debug/dmesg.h"
#include <stdlib.h>
#include <stdio.h>

static int test_block(unsigned char* ptr, int length)
{
	if(ptr == NULL)return 0;
	for(int i = 0; i < length; i++)
	{
		ptr[i] = 0xa5;
	}
	for(int i = 0; i < length; i++)
	{
		if(ptr[i] != 0xa5)return 0;
	}
	for(int i = 0; i < length; i++)
	{
		ptr[i] = 0x5a;
	}
	for(int i = 0; i < length; i++)
	{
		if(ptr[i] != 0x5a)return 0;
	}
	return 1;
}


void malloc_test()
{
	kprint("Try malloc\n");
	
	unsigned char* mymem = malloc(4);
	mymem[0] = 0;
	mymem[1] = 1;
	mymem[2] = 0;
	mymem[3] = 1;
	
	char buf[32];
	sprintf(buf, "Addr: %p %s\n", mymem, test_block(mymem, 4)? "OK" : "FAILED");
	kprint(buf);
	free(mymem);
	
	kprint("repeat allocations(100 B)\n");
	
	for(int i = 0; i < 10; i++)
	{
		mymem = malloc(100);
		sprintf(buf, "Addr: %p %s\n", mymem, test_block(mymem, 100)? "OK" : "FAILED");
		kprint(buf);
		free(mymem);		
	}
	
	kprint("repeat allocations(30 KB)\n");
	
	for(int i = 0; i < 10; i++)
	{
		mymem = malloc(30000);
		sprintf(buf, "Addr: %p %s\n", mymem, test_block(mymem, 30000)? "OK" : "FAILED");
		kprint(buf);
		free(mymem);		
	}
	
	kprint("repeat allocations(120 KB)\n");
	
	for(int i = 0; i < 10; i++)
	{
		mymem = malloc(120000);
		sprintf(buf, "Addr: %p %s\n", mymem, test_block(mymem, 120000)? "OK" : "FAILED");
		kprint(buf);
		free(mymem);		
	}
	
	kprint("allocate 100 MB in 1MB blocks\n");
	
	unsigned char** memmap = malloc(100 * 4);
	
	sprintf(buf, "Map addr: %p %s\n", memmap, test_block((unsigned char*)memmap, 400)? "OK" : "FAILED");
	kprint(buf);
	
	for(int i = 0; i < 100; i++)
	{
		memmap[i] = malloc(1000000);
		sprintf(buf, "Addr: %p %s\n", memmap[i], test_block(memmap[i], 1000000)? "OK" : "FAILED");
		kprint(buf);
	}
	
	kprint("Freeing memory\n");
	
	for(int i = 0; i < 100; i++)
	{
		if(memmap[i])free(memmap[i]);
	}
	
	kprint("Redo test\n");
	
	for(int i = 0; i < 100; i++)
	{
		memmap[i] = malloc(100000);
		sprintf(buf, "Addr: %p %s\n", memmap[i], test_block(memmap[i], 1000000)? "OK" : "FAILED");
		kprint(buf);
	}
	
	kprint("Freeing memory\n");
	
	for(int i = 0; i < 100; i++)
	{
		if(memmap[i])free(memmap[i]);
	}
	
	kprint("Freeing map\n");
	
	free(memmap);
	
	kprint("malloc test done\n");
}

