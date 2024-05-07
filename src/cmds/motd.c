#include <motd.h>
#include <stdlib.h>

int cmd_motd(int argc, char *argv[]) {
    print_motd();
    _Exit(EXIT_SUCCESS);
}
