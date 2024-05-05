#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stdio.h>
#include <string.h>

int cmd_motd(int argc, char *argv[]);

int main(void) {
    cmd_motd(0, nullptr);

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    char buff[256];
    printf("> ");
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        bool err = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
                   lua_pcall(L, 0, 0, 0);
        if (err) {
            fprintf(stderr, "%s", lua_tostring(L, -1));
            lua_pop(L, 1);
        }

        printf("> ");
    }

    lua_close(L);
    return 0;
}
