#include "../include/strace.h"
#include "../include/fatal.h"
#include "../include/syscall.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

void print_escaped(char c) {
    const char escape_chars[] =
        {'\a', '\b', '\t', '\n', '\v', '\f', '\r', '\"', '\\'};
    const char *escape_strs[] =
        {"\\a", "\\b", "\\t", "\\n", "\\v", "\\f", "\\r", "\\\"", "\\\\"};

    for (int i = 0; i < 9; i++) {
        if (c == escape_chars[i]) {
            fprintf(stderr, "%s", escape_strs[i]);
            break;
        }
    }
}

size_t print_str_arg(const unsigned char *str, size_t len) {
    size_t bytes_printed = 0;
    int is_file = !access((char*)str, F_OK);
    size_t i = 0;

    if (!str) {
        return(fprintf(stderr, "NULL"));
    }
    if (len == (size_t)-1) {
        len = 0;
        while (str[len]) {
            len++;
        }
    }
    for (i = 0; i < len; i++) {
        if (str[i] != '\0') {
            break;
        }
    }
    if (i == len) {
        return (fprintf(stderr, "\"\""));
    }
    bytes_printed += fprintf(stderr, "\"");
    for (i = 0; i < len && (i < MAX_STR_SIZE || is_file); i++) {
        if (str[i] == '\\' || str[i] == '\"' || (str[i] >= 8 && str[i] <= 15)) {
            print_escaped(str[i]);
            bytes_printed += 2;
        }
        else if (isprint(str[i])) {
            bytes_printed += fprintf(stderr, "%c", str[i]);
        }
        else {
            bytes_printed += fprintf(stderr, "\\%o", (int)str[i]);
        }
    }
    bytes_printed += fprintf(stderr, "\"");
    if (len > MAX_STR_SIZE && access((char*)str, F_OK)) {
        bytes_printed += fprintf(stderr, "...");
    }
    return (bytes_printed);
}

size_t print_str_arr(pid_t child, struct user_regs_struct *regs, size_t arg) {
    size_t i = 0;
    size_t bytes_printed = 0;
    size_t ptr = get_data(regs, arg);
    size_t *strs = get_ptr_data(child, ptr, -1, 1);
    int is_env = arg && SYSCALLS[SYSCALL_NB(regs)].arg_type[arg - 1] == _str_arr;

    if (!is_env) {
        bytes_printed += fprintf(stderr, "[");
    }
    while (strs[i]) {
        if (!is_env && i < MAX_STR_SIZE) {
            unsigned char *str = get_ptr_data(child, strs[i], -1, 1);
            bytes_printed += print_str_arg(str, -1);
            free(str);
            if (strs[i + 1]) {
                bytes_printed += fprintf(stderr, ", ");
            }
        }
        i++;
    }
    if (is_env) {
        bytes_printed += fprintf(stderr, "%p /* %lu vars */", (void*)ptr, i);
    }
    else {
        bytes_printed += fprintf(stderr, "]");
    }
    free(strs);
    return (bytes_printed);
}

size_t print_args(pid_t child, struct user_regs_struct *regs,
                  int second_run, int signal) {
    size_t bytes_printed = 0;
    size_t data = 0;
    int end = 0;
    int i = 0;

    if (SYSCALL_NB(regs) < NB_SYSCALLS && SYSCALLS[SYSCALL_NB(regs)].name) {
        t_syscall syscall = SYSCALLS[SYSCALL_NB(regs)];

        i = second_run ? syscall.uninit_arg : 0;
        end = second_run ? syscall.arg_count : syscall.uninit_arg;
        while (i < end) {
            data = get_data(regs, i);

            if (syscall.arg_type[i] == _int) {
                bytes_printed += fprintf(stderr, "%d", (int)data);
            }
            else if (syscall.arg_type[i] == _uint) {
                bytes_printed += fprintf(stderr, "%u", (unsigned int)data);
            }
            else if (syscall.arg_type[i] == _long) {
                bytes_printed += fprintf(stderr, "%ld", (long)data);
            }
            else if (syscall.arg_type[i] == _ulong) {
                bytes_printed += fprintf(stderr, "%lu", (unsigned long)data);
            }
            else {
                if (!data) {
                    bytes_printed += fprintf(stderr, "NULL");
                }
                else if (PEEKDATA_ENABLED && !signal && syscall.arg_type[i] == _str) {
                    size_t len = get_len_arg(regs, i);
                    unsigned char *str = get_ptr_data(child, data, len, 0);
                    bytes_printed += print_str_arg(str, len);
                    if (str) {
                        free(str);
                    }
                }
                else if (PEEKDATA_ENABLED && !signal && syscall.arg_type[i] == _str_arr) {
                    bytes_printed += print_str_arr(child, regs, i);
                }
                else {
                    bytes_printed += fprintf(stderr, "%p", (void*)data);
                }
            }
            if (i + 1 != syscall.arg_count) {
                bytes_printed += fprintf(stderr, ", ");
            }
            i++;
        }
    }
    else {
        for (size_t i = 0; i < 6; i++) {
            bytes_printed += fprintf(stderr, "%p", (void*)get_data(regs, i));
            if (i != 5) {
                bytes_printed += fprintf(stderr, ", ");
            }
        }
    }
    return (bytes_printed);
}