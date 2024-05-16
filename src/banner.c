#include <stdio.h>

void print_banner(void) {
    const char *banner =
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

    char last = ' ';
    for (size_t i = 0; banner[i] != '\0'; i++) {
        if (banner[i] != last) {
            switch (banner[i]) {
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
            last = banner[i];
        }
        printf("%c", banner[i]);
    }
}
