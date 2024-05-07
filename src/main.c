#include <cmd.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <motd.h>
#include <stdio.h>
#include <string.h>

bool report(lua_State *l, int status) {
    if (status == LUA_OK)
        return false;

    fprintf(stderr, "\x1B[0;31m%s\x1B[0;0m\n", lua_tostring(l, -1));
    lua_pop(l, 1);
    return true;
}

int main(void) {
    print_motd();

    lua_State *l = luaL_newstate();
    luaL_openlibs(l);

    register_cmds(l);

    while (true) {
        printf("\x1B[0;36m>\x1B[0;0m>\x1B[0;33m>\x1B[0;0m ");

        char line[256];
        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        int status;

        const char *ret_line = lua_pushfstring(l, "return %s", line);
        if (luaL_loadbuffer(l, ret_line, strlen(ret_line), "=stdin") !=
            LUA_OK) {
            lua_pop(l, 2);
            status = luaL_loadbuffer(l, line, strlen(line), "=stdin");
            if (report(l, status))
                continue;
        } else {
            lua_remove(l, -2);
        }

        status = lua_pcall(l, 0, LUA_MULTRET, 0);
        report(l, status);

        int n = lua_gettop(l);
        if (n > 0) {
            lua_getglobal(l, "print");
            lua_insert(l, 1);
            lua_pcall(l, n, 0, 0);
        }
    }

    lua_close(l);
    return 0;
}
