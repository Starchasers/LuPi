#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <stdlib.h>
//#include <lualib.h>

#include "luaFunctions.h"

#include "driver/timer/systemTimer.h"
#include "driver/gpio/gpio.h"
#include "lib/term/gputerm.h"
#include "lib/debug/dmesg.h"

void waitMiliseconds(unsigned int t)
{
	_wait(t*1000);
}

void run(void)
{
	
	dmesg_enable_uart(9600);
	kprint("Hello world\n");
	kprint("Init GPU driver\n");
	
	gputerm_init();
	gputerm_writeln("Hello world");
	
	kprint("Start LED\n");
	
	_setGpioFunction(1,16);
	_setGpio(16, 1);	
	
	kprint("Try malloc\n");
	
	unsigned char* mymem = malloc(4);
	mymem[0] = 0;
	mymem[1] = 1;
	mymem[2] = 0;
	mymem[3] = 1;
	
	char buf[20];
	sprintf(buf, "0x%p", mymem);
	
	gputerm_writeln(buf);
	gputerm_writeln("I still work");
	
	kprint("Test addr: ");
	kprint(buf);
	kprint("\n");
	
	for (int i = 0; i < 16; i++)
	{
		_setGpio(16, mymem[i%4]);
		waitMiliseconds(100);
	}
	_setGpio(16, 0);
	
	kprint("Start LUA\n");
	
	lua_State *L = luaL_newstate();
	
	lua_pushcfunction(L, luaFn_wait);
	lua_setglobal(L, "wait");
	
	lua_pushcfunction(L, luaFn_setGpio);
	lua_setglobal(L, "setGpio");
	_setGpio(16, 1);
	luaL_dostring(L, "while true do setGpio(16,0)wait(750)setGpio(16,1)wait(750) end");
	gputerm_writeln("fuck..");
	
	
	lua_close(L);
	
}
