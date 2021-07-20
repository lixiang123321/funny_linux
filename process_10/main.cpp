//
// Created by rere on 2021/7/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

extern int create_process(char* program, char **arg_list);

int main() {
    char* arg_list[] = {
            "ls",
            "-l",
            "/",
            NULL
    };
    create_process("ls", arg_list);
    return 0;
}