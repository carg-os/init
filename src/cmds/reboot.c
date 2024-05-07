#include <reboot.h>
#include <stdlib.h>

int cmd_reboot(int argc, char *argv[]) { _Exit(reboot(REBOOT_TYPE_REBOOT)); }
