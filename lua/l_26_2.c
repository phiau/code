//
// Created by zhenbiao.cai on 2017/2/24.
//
#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int add(lua_State *L) {
    int a = lua_tonumber(L, 1);
    lua_pushnumber(L, a + 5);
    return 1;
}

static luaL_Reg mylib [] = {
        {"add", add},
        {NULL, NULL}
};

static void stackDump(lua_State *L) {
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; ++i) {
        int t = lua_type(L, i);
        switch (t) {

            case LUA_TSTRING:
                printf("'%s'", lua_tostring(L, i));
                break;

            case LUA_TBOOLEAN:
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:
                printf("%g", lua_tonumber(L, i));
                break;

            default:
                printf("%s", lua_typename(L, t));
                break;
        }
        printf("  ");
    }
    printf("\n");
}

int main(void) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);
    luaL_setfuncs(L, mylib, 0);

    if(luaL_dofile(L, "add.lua")) {
        stackDump(L);
    }

    lua_close(L);
}

