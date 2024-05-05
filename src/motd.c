#include <stdio.h>

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

    for (size_t i = 0; boot_msg[i] != '\0'; i++) {
        switch (boot_msg[i]) {
        case '=':
        case ':':
            printf("\x1B[0;90m");
            break;
        case '0':
            printf("\x1B[0;36m");
            break;
        case '1':
            printf("\x1B[0;33m");
            break;
        default:
            printf("\x1B[0;0m");
            break;
        }
        printf("%c", boot_msg[i]);
    }

    return 0;
}
