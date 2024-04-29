#include <unistd.h>

int cmd_motd(int argc, char *argv[]) {
    const char *boot_msg =
        // clang-format off
"                                                                          \n"
"  :=:=                                            =:=:                    \n"
"   +=:                                            :=+                     \n"
"   +=      :::    =:=:            :=:=    :::      =+                     \n"
"   :*      ===    =*:              :*=    ===      *:                     \n"
"    =+     ==    =+:                :+=    ==     +=                      \n"
"     =+:   =+ :=+=                    =+=: +=   :+=                       \n"
"      :+=  :*+=:                        :=+*:  =+:                        \n"
"        :+==+*=::::                  ::::=*+==+:                          \n"
"           :: :====+=              =+====: ::                             \n"
"                    =+:          :+=                                      \n"
"              ****::  =+        +=  ::****                                \n"
"             *000000+: =+      += :+111111*                               \n"
"             *0000000*  ==    ==  *1111111*                               \n"
"              *000000*: :*:  :*: :*111111*                                \n"
"               *******=  :=::=:  :*******                                 \n"
"                     =+          +=                                       \n"
"                     :*          *:       .--.                  .-.   .-. \n"
"                      :*        *:       |                     |   | |    \n"
"                      =+        +=       |     .--. .--.  .-.  |   |  `-. \n"
"                      =+:      :+=       |     .--| |    |   | |   |     |\n"
"                        :*=++=*:          `--' `--' |     `-'|  `-'   `-' \n"
"                         :====:                           `--'            \n"
"                                                                          \n";
    // clang-format on

    char buf[512];
    size_t pos = 0;
    for (size_t i = 0; boot_msg[i] != '\0'; i++) {
        if (i == 0 || boot_msg[i] != boot_msg[i - 1]) {
            switch (boot_msg[i]) {
            case '=':
            case ':':
                buf[pos++] = '\x1B';
                buf[pos++] = '[';
                buf[pos++] = '0';
                buf[pos++] = ';';
                buf[pos++] = '9';
                buf[pos++] = '0';
                buf[pos++] = 'm';
                break;
            case '0':
                buf[pos++] = '\x1B';
                buf[pos++] = '[';
                buf[pos++] = '0';
                buf[pos++] = ';';
                buf[pos++] = '3';
                buf[pos++] = '6';
                buf[pos++] = 'm';
                break;
            case '1':
                buf[pos++] = '\x1B';
                buf[pos++] = '[';
                buf[pos++] = '0';
                buf[pos++] = ';';
                buf[pos++] = '3';
                buf[pos++] = '3';
                buf[pos++] = 'm';
                break;
            default:
                buf[pos++] = '\x1B';
                buf[pos++] = '[';
                buf[pos++] = '0';
                buf[pos++] = ';';
                buf[pos++] = '0';
                buf[pos++] = 'm';
                break;
            }
        }
        buf[pos++] = boot_msg[i];
        if (boot_msg[i] == '\n') {
            write(1, buf, pos);
            pos = 0;
        }
    }
    return 0;
}
