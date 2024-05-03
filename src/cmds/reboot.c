#include <reboot.h>
#include <stdlib.h>

int cmd_reboot(int argc, char *argv[]) { exit(reboot(REBOOT_REBOOT)); }
