//
// lua UserData
// Created by zhenbiao.cai on 2017/3/7.
//

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/*
 *  C 调用 Lua 的接口进行内存申请，Lua 调用 C 的接口操作这片内存
 */

typedef struct NumArray {
    int size;
    double values[1];
} NumArray;

static int newarray (lua_State *L) {
    int n = luaL_checkint(L, 1);
    size_t nbytes = sizeof(NumArray) + (n - 1) * sizeof(double);
    NumArray *a = (NumArray *) lua_newuserdata(L, nbytes);
    a->size = n;
    return 1;
}

static int setarray (lua_State *L) {
    NumArray *a  = (NumArray *) lua_touserdata(L, 1);
    int index = luaL_checkint(L, 2);
    double value = luaL_checknumber(L, 3);

    luaL_argcheck(L, NULL != a, 1, "'array' expected");

    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

    a->values[index - 1] = value;
    return 0;
}

static int getarray (lua_State *L) {
    NumArray *a = (NumArray *) lua_touserdata(L, 1);
    int index = luaL_checkint(L, 2);

    luaL_argcheck(L, NULL != a, 1, "'array' expected");

    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

    lua_pushnumber(L, a->values[index-1]);
    return 1;
}

static int getsize (lua_State *L) {
    NumArray *a = (NumArray *) lua_touserdata(L, 1);

    luaL_argcheck(L, NULL != a, 1, "'array' expected");

    lua_pushnumber(L, a->size);
    return 1;
}

static const struct luaL_Reg arraylib[] = {
        {"new", newarray},
        {"set", setarray},
        {"get", getarray},
        {"size", getsize},
        {NULL, NULL}
};

// 格式已经固定了，就是 luaopen_***，*** 是生成的动态库的名字
// gcc l_28_1.c -fPIC -shared -o array.so
int luaopen_array(lua_State *L) {
    luaL_newlib(L, arraylib);
    return 1;
}
