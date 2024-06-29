#include <cmd.h>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>

static bool report(lua_State *lua, int status) {
    if (status == LUA_OK)
        return false;
    fprintf(stderr, "\x1B[0;31m%s\x1B[0;0m\n", lua_tostring(lua, -1));
    lua_pop(lua, 1);
    return true;
}

static bool push_line(lua_State *lua, bool first) {
    if (!first) {
        printf("    ");
        fflush(stdout);
    }
    char buffer[256];
    if (!fgets(buffer, sizeof(buffer), stdin))
        return false;
    for (size_t i = 0; buffer[i]; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
    }
    lua_pushlstring(lua, buffer, strlen(buffer));
    return true;
}

#define EOFMARK "<eof>"

static bool incomplete(lua_State *lua, int status) {
    if (status != LUA_ERRSYNTAX)
        return false;
    size_t len;
    const char *msg = lua_tolstring(lua, -1, &len);
    if (len < strlen(EOFMARK) ||
        strcmp(msg + len - strlen(EOFMARK), EOFMARK) != 0)
        return false;
    lua_pop(lua, 1);
    return true;
}

static int load_multiline(lua_State *lua) {
    while (true) {
        size_t len;
        const char *line = lua_tolstring(lua, 1, &len);
        int status = luaL_loadbuffer(lua, line, len, "=stdin");
        if (!incomplete(lua, status) || !push_line(lua, false))
            return status;
        lua_pushliteral(lua, "\n");
        lua_insert(lua, -2);
        lua_concat(lua, 3);
    }
}

static int load_retline(lua_State *lua) {
    const char *line = lua_tostring(lua, -1);
    const char *retline = lua_pushfstring(lua, "return %s;", line);
    int status = luaL_loadbuffer(lua, retline, strlen(retline), "=stdin");
    if (status == LUA_OK) {
        lua_remove(lua, -2);
    } else {
        lua_pop(lua, 2);
    }
    return status;
}

static int load_line(lua_State *lua) {
    if (!push_line(lua, true))
        return -1;
    int status = load_retline(lua);
    if (status != LUA_OK)
        status = load_multiline(lua);
    lua_remove(lua, 1);
    return status;
}

void shell(void) {
    print_banner();

    lua_State *lua = luaL_newstate();
    if (!lua) {
        fprintf(stderr, "failed to intialize Lua state\n");
        return;
    }
    luaL_openlibs(lua);

    register_cmds(lua);

    while (true) {
        printf("\x1B[0;36m>\x1B[0;0m>\x1B[0;33m>\x1B[0;0m ");

        int status = load_line(lua);
        report(lua, status);

        status = lua_pcall(lua, 0, LUA_MULTRET, 0);
        report(lua, status);

        int n = lua_gettop(lua);
        if (n > 0) {
            lua_getglobal(lua, "print");
            lua_insert(lua, 1);
            lua_pcall(lua, n, 0, 0);
        }
    }

    lua_close(lua);
}
