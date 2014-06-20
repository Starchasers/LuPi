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
#include "lib/debug/selftests/malloc.h"
#include "gen/luares.h"
#include "usbd/usbd.h"

#include "driver/uart/uart.h"
#include "driver/keyboard/keyboard.h"


void waitMiliseconds(unsigned int t)
{
	_wait(t*1000);
}

void run(void)
{
	
	dmesg_enable_uart(115200);
	kprint("\n\n\n-----------------\n");
	kprint("Booting LuPI\n");
	
	kprint("Init USB driver\n");
	
	UsbInitialise();
	
	kprint("Init GPU driver\n");
	
	gputerm_init();
	gputerm_writeln("Hello world");	
	
	kprint("Start LED\n");
	
	_setGpioFunction(1,16);
	_setGpio(16, 1);	
	
	gputerm_writeln("sdsvjslkdvnj");
	
	//malloc_test();
	
	kprint("\n");
	
	for (int i = 0; i < 16; i++)
	{
		_setGpio(16, i%2);
		waitMiliseconds(100);
	}
	_setGpio(16, 1);
	
	kprint("Keyboard test loop\nQ to quit\n");
	
	while(1)
	{
		KeyboardUpdate();
		char c = KeyboardGetChar();
		uart_putc(c);
	}
	
	kprint("Start LUA\n");
	
	lua_State *L = luaL_newstate();
	kprint("Start LUA1\n");
	//lua_pushcfunction(L, luaFn_wait);
	//lua_setglobal(L, "wait");
	kprint("Start LUA2\n");	
	
	lua_pushcfunction(L, luaFn_kprint);
	lua_setglobal(L, "kprint");
	
	kprint("Start LUA3\n");
	//_setGpio(16, 1);
	//luaL_dostring(L, "");
	//char buf[123];
	//sprintf(buf, "A:%p, %hd, %hd, %hd\n", &linc_main_lua, (*(char*)(&linc_main_lua + 0x12)), (*(char*)(&linc_main_lua + 0x13)), (*(char*)(&linc_main_lua + 0x14)));
	luaL_loadstring(L, lua_main);
	//kprint("Start LUA4\n");
	lua_call(L, 0, 0);

	gputerm_writeln("fuck.. yeah\n");
	
	while(1){}
	
	lua_close(L);
	
}
