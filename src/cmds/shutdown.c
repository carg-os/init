#include <sys/reboot.h>

int cmd_shutdown(int argc, char *argv[]) { reboot(REBOOT_SHUTDOWN); }
