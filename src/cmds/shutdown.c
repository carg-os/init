#include <reboot.h>
#include <stdlib.h>

int cmd_shutdown(int argc, char *argv[]) { exit(reboot(REBOOT_SHUTDOWN)); }
