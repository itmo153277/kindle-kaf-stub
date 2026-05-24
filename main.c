/*
    kaf-stub
    Copyright (C) 2026  Viktor Ivanov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <openlipc.h>

#define USAGE "Usage: kaf-stub\n\n" \
    "Create a kindle framework substitute service\n\n" \
    "Report bugs to <viktprog@gmail.com>\n"

#define LOG_PREFIX "[kaf-stub] "

void printUsage() {
    fputs(USAGE, stderr);
}

volatile sig_atomic_t signalStatus = 0;

void handleSignal(int status) {
    signalStatus = status;
}

LIPCcode frameworkStarted(LIPC *lipc, const char *property, void *value, void *data) {
    LIPC_GETTER_VTOI(value) = 1;
    return LIPC_OK;
}

int main(int argc, char **argv) {
    LIPC *lipc;

    if (argc != 1) {
        printUsage();
        return EXIT_FAILURE;
    }
    signal(SIGINT, handleSignal);
    lipc = LipcOpen("com.lab126.kaf");
    if (lipc == NULL) {
        fputs("Failed to open lipc\n", stderr);
        return EXIT_FAILURE;
    }
    if (LipcRegisterIntProperty(lipc, "frameworkStarted", frameworkStarted,
        NULL, NULL) != LIPC_OK) {
        fputs("Failed to register property\n", stderr);
        goto fail;
    }
    while (signalStatus == 0) {
        pause();
    }
    fputs(LOG_PREFIX "Exiting...\n", stderr);
    LipcClose(lipc);
    return EXIT_SUCCESS;
fail:
    LipcClose(lipc);
    return EXIT_FAILURE;
}
