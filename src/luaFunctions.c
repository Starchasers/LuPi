#include "luaFunctions.h"
#include "driver/timer/systemTimer.h"
#include "driver/gpio/gpio.h"
#include "gen/luares.h"
int luaFn_wait(lua_State *L) {
	_wait( ((int)luaL_checknumber(L, 1)) * 1000 );
	return 0;
}

int luaFn_setGpio(lua_State *L) {
	//_setGpio( ((int)luaL_checknumber(L, 1)), ((int)luaL_checknumber(L, 2)) );
	_setGpio(16, 0);
	return 0;
}

int luaFn_kprint(lua_State *L)
{
	int argc = lua_gettop(L);
	const char* s = lua_tostring(L,1);
	
	kprint(s);
	return 0;
}

