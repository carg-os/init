#include <sys/reboot.h>

int cmd_reboot(int argc, char *argv[]) { reboot(REBOOT_REBOOT); }
