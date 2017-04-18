## Lua 协程 ##

- 参考文档：
 - www.luachina.net 翻译组在 2005 年基于 Lua5.0 翻译的 《Lua程序设计.chm》  
 - [http://ouonline.net/programming-in-lua-12](http://ouonline.net/programming-in-lua-12)
 - [http://lua-users.org/lists/lua-l/2013-01/msg00504.html](http://lua-users.org/lists/lua-l/2013-01/msg00504.html)

第二个链接是提出了在 “写协程例子” 的时候遇到的问题 “attempt to yield across a C-call boundary.”。而第一个例子是一个正常的例子，最后发现第二个的问题。

其实协程没什么特别的，就是多了几个接口，根据官网的文档说明就可以了。

### 直接上代码 ###
#### C 代码 Coroutine.c ####
	#include <stdio.h>
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
	
	int running = 1;
	
	int lua_sleep(lua_State *L) {
		printf("  调用 C API 挂起\n");
		return lua_yield(L, 0);
	}
	
	int lua_finish(lua_State *L) {
		printf("程序结束\n");
		running = 0;
		return 0;
	}
	
	int main(void)
	{
		int i, nr_args;
		lua_State *L, *l1;
	
		L = luaL_newstate();
		luaL_openlibs(L);
	
		lua_register(L, "sleep", lua_sleep);
		lua_register(L, "finish", lua_finish);
	
		l1 = lua_newthread(L);
	
		if (0 != luaL_loadfile(l1, "./foo.lua"))
		{
			fprintf(stderr, "luaL_loadfile err: %s. \n", lua_tostring(l1, -1));
			goto end;
		}
	
		while (running)
		{
			int status = lua_resume(l1, NULL, 0);
			if (LUA_YIELD == status)
			{
				printf("   程序刚才是被挂起，现在唤醒程序\n");
			}
			else
			{
				running = 0;
				printf("    程序不是被挂起.\n");
				if (LUA_ERRRUN == status && lua_isstring(l1, -1))
				{
					printf("lua_resume err: %s\n", lua_tostring(l1, -1));
					lua_pop(l1, -1);
					break;
				}
			}
	
		}
	end:
		lua_close(L);
		getchar();
		return 0;
	}

#### Lua 代码 foo.lua ####
	print("foo.lua")
	
	local i = 0
	while true do
		print("循环运行第："..i .." 次")
		sleep()
		print("    被挂起后，继续循环运行："..i)
		i = i + 1
		if 3 == i then
			break
		end
	end
	
	finish()

#### 运行结果 ####
	foo.lua
	循环运行第：0 次
	  调用 C API 挂起
	   程序刚才是被挂起，现在唤醒程序
	    被挂起后，继续循环运行：0
	循环运行第：1 次
	  调用 C API 挂起
	   程序刚才是被挂起，现在唤醒程序
	    被挂起后，继续循环运行：1
	循环运行第：2 次
	  调用 C API 挂起
	   程序刚才是被挂起，现在唤醒程序
	    被挂起后，继续循环运行：2
	程序结束
	    程序不是被挂起.