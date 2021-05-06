#pragma once
extern "C" {
# include "lua5.2/lua.h"
# include "lua5.2/lauxlib.h"
# include "lua5.2/lualib.h"
}
#include <LuaBridge.h>

using namespace luabridge;


template <class arrayType>
arrayType* getLuaArray(LuaRef value, int size)
{
	arrayType* array = new arrayType[size];
	for (int i = 0; i < size; i++)
	{
		array[i] = value[i+1];
	}
	return array;
}