//
// Created by zhenbiao.cai on 2017/2/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int main(void)
{
    char buff[256];
    int error;
    //lua_State *L = lua_open();
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    //luaopen_base(L);
    //luaopen_table(L);
    //luaopen_string(L);
    //luaopen_math(L);

    while(fgets(buff, sizeof(buff), stdin) != NULL) {
        error = luaL_loadbuffer(L, buff, strlen(buff), "line") || lua_pcall(L, 0, 0, 0);
        if(error) {
            fprintf(stderr, "%s", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }

    lua_close(L);
    return 0;
}

