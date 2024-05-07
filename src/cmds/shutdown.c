#include <reboot.h>
#include <stdlib.h>

int cmd_shutdown(int argc, char *argv[]) {
    _Exit(reboot(REBOOT_TYPE_SHUTDOWN));
}
