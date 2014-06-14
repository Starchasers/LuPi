#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
//#include <lualib.h>

#include "luaFunctions.h"

#include "driver/timer/systemTimer.h"
#include "driver/gpio/gpio.h"
#include "driver/gpu/frameBuffer.h"
#include "driver/gpu/colors.h"
#include "driver/gpu/drawing.h"

void waitMiliseconds(unsigned int t)
{
	_wait(t*1000);
}

void run(void)
{
	FrameBuferDescription* fbd = InitialiseFrameBuffer(1024,768,16);
	SetGraphicsAddress(fbd);
	
	SetForeColour(Orange);
	DrawLine(0,0,1024,768);
	
	SetForeColour(GreenYellow);
	DrawLine(0,768,1024,0);

	_setGpioFunction(1,16);
	_setGpio(16, 1);	
	
	unsigned char* mymem = malloc(4);
	mymem[0] = 0;
	mymem[1] = 1;
	mymem[2] = 0;
	mymem[3] = 1;
	
	for (int i = 0; i < 16; i++)
	{
		_setGpio(16, mymem[i%4]);
		waitMiliseconds(100);

	}
	_setGpio(16, 0);
	lua_State *L = luaL_newstate();
	
	lua_pushcfunction(L, luaFn_wait);
	lua_setglobal(L, "wait");
	
	lua_pushcfunction(L, luaFn_setGpio);
	lua_setglobal(L, "setGpio");
	_setGpio(16, 1);
	luaL_dostring(L, "while true do setGpio(16,0)wait(750)setGpio(16,1)wait(750) end");
	
	
	
	lua_close(L);
	
}
