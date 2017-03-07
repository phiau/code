//
// lua 调用 C 生成的动态库
// Created by zhenbiao.cai on 2017/3/2.
//

#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static int add(lua_State *L) {
    int a, b, c;
    a = lua_tonumber(L,1);
    b = lua_tonumber(L,2);
    c = a + b;
    lua_pushnumber(L, c);
    return 1;
}

static const struct luaL_Reg lib[] = {
        {"add", add},
        {NULL, NULL}
};

// 格式已经固定了，就是 luaopen_***，*** 是生成的动态库的名字
// gcc luaCallCSo.c -fPIC -shared -o libname.so
int luaopen_libname(lua_State *L) {
    luaL_newlib(L, lib);
    return 1;
}

/*
m = require("libname")
c = m.add(14, 11)
print(c)
 */

//然后直接运行上面的 lua 文件，就可以了
