//
// Created by zhenbiao.cai on 2017/3/7.
//

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/*
 *  l_28_1 lua 在调用 array.set 时，传进来的指针不一定合法
 *  例如 array.set(io.stdin, 1, 0)
 *  io.stdin 中的值是一个带有指向流的指针的 userdatum，所以参数合法，不过程序运行可能会因为内存操作不当引起 core dump 或者 越界访问
 *  lua 有一个接口是 void *luaL_checkudata (lua_State *L, int arg, const char *tname);
 *  会检查 arg 参数是不是 tname 类型的 userdata，如果是返回对应的 userdata 地址
 *  tname 是 userdata 的 metatable 的名字，所以可以为 userdata 设置一个 metatable
 *
 *  结果：如果是在 l_28_1 中使用 io.stdin，是可以得到指针的，而有了 metatable 之后，就会报错“bad argument #1 to 'get' (LuaBook.array expected, got userdata)”
 */

typedef struct NumArray {
    int size;
    double values[1];
} NumArray;

static int newarray (lua_State *L) {
    int n = luaL_checkint(L, 1);
    size_t nbytes = sizeof(NumArray) + (n - 1) * sizeof(double);
    NumArray *a = (NumArray *) lua_newuserdata(L, nbytes);

    // 在这之前，得先创建 LuaBook.array 这个 metatable
    luaL_getmetatable(L, "LuaBook.array");
    // 把栈顶的 metatable 作为 -2 位置的 metatable，并弹出栈顶
    lua_setmetatable(L, -2);

    a->size = n;
    return 1;
}

static NumArray *checkarray (lua_State *L ) {
    void *ud = luaL_checkudata(L, 1, "LuaBook.array");
    luaL_argcheck(L, NULL != ud, 1, "'array' expected");
    return (NumArray *) ud;
}

static int getsize (lua_State *L) {
    NumArray *a = checkarray(L);
    lua_pushnumber(L, a->size);
    return 1;
}

static double *getelem (lua_State *L) {
    NumArray *a = checkarray(L);
    int index = luaL_checkint(L, 2);

    luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

    return &a->values[index -1];
}

static int setarray (lua_State *L) {
    double newvalue = luaL_checknumber(L, 3);
    *getelem(L) = newvalue;
    return 0;
}

static int getarray (lua_State *L) {
    lua_pushnumber(L, *getelem(L));
    return 1;
}

static const struct luaL_Reg arraylib[] = {
        {"new", newarray},
        {"set", setarray},
        {"get", getarray},
        {"size", getsize},
        {NULL, NULL}
};

int luaopen_array(lua_State *L) {
    luaL_newmetatable(L, "LuaBook.array");
    luaL_newlib(L, arraylib);
    return 1;
}