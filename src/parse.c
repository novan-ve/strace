#include "../include/strace.h"
#include "../include/fatal.h"
#include "../include/syscall.h"

#include <sys/ptrace.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

size_t get_data(struct user_regs_struct *regs, int arg) {
    switch (arg) {
    #ifdef __x86_64__
        case 0: return regs->rdi;
        case 1: return regs->rsi;
        case 2: return regs->rdx;
        case 3: return regs->r10;
        case 4: return regs->r8;
        case 5: return regs->r9;
    #else
        case 0: return regs->ebx;
        case 1: return regs->ecx;
        case 2: return regs->edx;
        case 3: return regs->esi;
        case 4: return regs->edi;
        case 5: return regs->esp;
    #endif  /* __x86_64__ */
    }
    fatal(ERR_SYSCALL_ARG);
    return (0);
}

char *get_program_from_env(const char *program, char *env_path) {
    char *token;
    char *resolved_path;

    token = strtok(env_path, ":");

    while (token) {
        char path[strlen(program) + strlen(env_path) + 2];

        sprintf(path, "%s/%s", token, program);
        resolved_path = realpath(path, NULL);
        if (!resolved_path) {
            resolved_path = strdup(path);
        }
        if (!access(resolved_path, F_OK)) {
            return (resolved_path);
        }
        free(resolved_path);
        token = strtok(NULL, ":");
    }
    return (NULL);
}

char *get_program_path(const char *program) {
    char *env_path;

    if (!program) {
        return (NULL);
    }
    if (program[0] == '.' || program[0] == '/') {
        if (!access(program, F_OK)) {
            return (strdup(program));
        }
        return (NULL);
    }
    env_path = getenv("PATH");
    if (!env_path) {
        return (NULL);
    }
    return (get_program_from_env(program, env_path));
}

void *get_ptr_data(pid_t child, size_t ptr, size_t len, int is_arr) {
    size_t tmp = 0;
    size_t allocated = 4096;
    size_t read = 0;
    size_t *data;

    if (!ptr) {
        return (NULL);
    }
    if (!(data = malloc(allocated))) {
        fatal(ERR_MALLOC);
    }
    while (read < len) {
        if (read + sizeof(tmp) > allocated) {
            allocated *= 2;
            size_t *tmp_str = realloc(data, allocated);
            if (!tmp_str) {
                free(data);
                fatal(ERR_MALLOC);
            }
            data = tmp_str;
        }
        tmp = ptrace(PTRACE_PEEKDATA, child, ptr + read);
        if (errno) {
            data[read] = '\0';
            break;
        }
        memcpy(data + read / sizeof(*data), &tmp, sizeof(tmp));
        if (len == (size_t)-1 && (!tmp || (!is_arr && memchr(&tmp, 0, sizeof(tmp))))) {
            break;
        }
        read += sizeof(tmp);
    }
    return ((void*)data);
}

size_t get_len_arg(struct user_regs_struct *regs, int arg) {
    char *syscalls_with_len[20] = {
        "read", "write", "pread64", "pwrite64", "setsockopt", "getsockopt",
        "sethostname", "setdomainname", "setxattr", "lsetxattr", "fsetxattr",
        "listxattr", "llistxattr", "flistxattr", "lookup_dcookie", "mq_timedsend",
        "mq_timedreceive", "readlinkat", "readlink", "syslog"
    };
    t_syscall syscall = SYSCALLS[SYSCALL_NB(regs)];

    if (arg < syscall.arg_count - 1) {
        arg_type next_arg = syscall.arg_type[arg + 1];

        if (next_arg != _str && next_arg != _str_arr) {
            for (int i = 0; i < 20; i++) {
                if (!strcmp(syscall.name, syscalls_with_len[i])) {
                    if (next_arg == _ptr) {
                        return(*((size_t*)get_data(regs, arg + 1)));
                    }
                    else {
                        return(get_data(regs, arg + 1));
                    }
                }
            }
        }
    }
    return(-1);
}

int has_empty_buffer(struct user_regs_struct *regs) {
    char *syscalls_with_empty_buf[11] = {
        "read", "pread64", "readlink", "getsockopt", "listxattr", "llistxattr",
        "flistxattr", "lookup_dcookie", "mq_timedreceive", "readlinkat", "getcwd",
    };

    if (SYSCALL_NB(regs) < NB_SYSCALLS) {
        const char *syscall = SYSCALLS[SYSCALL_NB(regs)].name;
        for (int i = 0; i < 11; i++) {
            if (!strcmp(syscall, syscalls_with_empty_buf[i])) {
                return (1);
            }
        }
    }
    return (0);
}

unsigned long long get_errno(struct user_regs_struct *regs) {
#ifdef __x86_64__
    return (__SIZE_MAX__ - regs->rax + 1);
#else
    return (__SIZE_MAX__ - regs->eax + 1);
#endif  /* __x86_64__ */
}
