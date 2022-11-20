#include "../include/strace.h"
#include "../include/signals.h"
#include "../include/syscall.h"
#include "../include/errno_names.h"
#include "../include/fatal.h"

#include <sys/ptrace.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <elf.h>

extern char **environ;

e_status wait_for_syscall(pid_t child, int *status) {
    while (1) {
        if (ptrace(PTRACE_SYSCALL, child, 0, 0) < 0) {
            fatal(ERR_PTRACE_SYSCALL);
        }
        if (waitpid(child, status, 0) < 0) {
            fatal(ERR_WAITPID);
        }
        if (WIFSTOPPED(*status)) {
            if (WSTOPSIG(*status) & 0x80) {
                return (e_syscall);
            }
            return (e_signal);
        }
        if (WIFEXITED(*status) || WIFSIGNALED(*status)) {
            return (e_exit);
        }
    }
}

unsigned long long syscall_nb(pid_t child) {
    struct iovec iov;
    struct user_regs_struct regs;

    memset(&regs, 0, sizeof(regs));
    iov.iov_len = sizeof(regs);
    iov.iov_base = &regs;

    if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, &iov) < 0) {
        fatal(ERR_PTRACE_GETREGSET);
    }
    return(SYSCALL_NB((&regs)));
}

void signal_caught(pid_t child) {
    siginfo_t sig;
    int status;

    if (ptrace(PTRACE_GETSIGINFO, child, 0, &sig) < 0) {
        fatal(ERR_PTRACE_GETSIGINFO);
    }
    if (!(sig.si_pid == child && (sig.si_signo == SIGTRAP || sig.si_signo == SIGSTOP))) {
        print_signal(&sig);
        if (sig.si_signo == SIGSTOP || sig.si_signo == SIGTSTP ||
            sig.si_signo == SIGTTIN || sig.si_signo == SIGTTOU) {
            fprintf(stderr, "--- stopped by %s ---\n", SIGNALS[sig.si_signo].name);

            if (ptrace(PTRACE_SYSCALL, child, 0, sig.si_signo) < 0) {
                fatal(ERR_PTRACE_SYSCALL);
            }
            if (waitpid(child, &status, WUNTRACED) < 0) {
                fatal(ERR_WAITPID);
            }
            if (ptrace(PTRACE_LISTEN, child, 0, 0) < 0) {
                fatal(ERR_PTRACE_LISTEN);
            }
            if (waitpid(child, &status, WCONTINUED) < 0) {
                fatal(ERR_WAITPID);
            }
        }
        else if (sig.si_signo != SIGCHLD && sig.si_signo != SIGCONT &&
            sig.si_signo != SIGURG && sig.si_signo != SIGWINCH) {
            if (sig.si_signo >= MIN_SIGNAL && sig.si_signo <= MAX_SIGNAL) {
                fprintf(stderr, "+++ killed by %s +++\n", SIGNALS[sig.si_signo].name);
                if (sig.si_signo == MAX_SIGNAL) {
                    exit(160);
                }
            }
            else {
                fprintf(stderr, "+++ killed by SIGRT_%d +++\n", sig.si_signo - MAX_SIGNAL);
                if (sig.si_signo == MAX_SIGNAL + 1) {
                    raise(SIGSEGV);
                }
            }
            kill(child, sig.si_signo);
            raise(sig.si_signo);
        }
    }
}

int syscall_caught(pid_t child, unsigned long long *last_syscall, int *status) {
    unsigned long long errno_nb;
    struct user_regs_struct regs;
    struct iovec iov;
    size_t nb;
    size_t len;
    e_status ret;

    memset(&regs, 0, sizeof(regs));
    iov.iov_len = sizeof(regs);
    iov.iov_base = &regs;

    if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, &iov) < 0) {
        fatal(ERR_PTRACE_GETREGSET);
    }
    len = print_syscall(&regs);
    len += print_args(child, &regs, 0, 0);
    nb = SYSCALL_NB((&regs));
    if (nb < NB_SYSCALLS && !strcmp(SYSCALLS[nb].name, "restart_syscall")) {
        if (*last_syscall < NB_SYSCALLS) {
            len += fprintf(stderr, "<... resuming interrupted %s ...>",
                SYSCALLS[*last_syscall].name);
        }
        else {
            len += fprintf(stderr, "<... resuming interrupted syscall_0x%llx ...>",
                *last_syscall);
        }
    }
    ret = wait_for_syscall(child, status);
    if (ret == e_exit) {
        if (nb < NB_SYSCALLS && SYSCALLS[nb].arg_count != SYSCALLS[nb].uninit_arg) {
            len += fprintf(stderr, " <unfinished ...>");
        }
        print_padding(len);
        fprintf(stderr, "= ?\n");
        return (0);
    }
    else if (ret == e_syscall) {
        if (ptrace(PTRACE_GETREGSET, child, NT_PRSTATUS, &iov) < 0) {
            fatal(ERR_PTRACE_GETREGSET);
        }
        errno_nb = get_errno(&regs);
        len += print_args(child, &regs, 1,
            errno_nb >= MIN_SIGNAL_ERRNO && errno_nb <= MAX_SIGNAL_ERRNO);
        print_padding(len);
        print_return(child, &regs);
        *last_syscall = SYSCALL_NB((&regs));
    }
    else if (ret == e_signal) {
        signal_caught(child);
    }
    return (1);
}

int start_tracing(pid_t child) {
    unsigned long long nb;
    unsigned long long last_syscall;
    e_status ret;
    int status;

    if (ptrace(PTRACE_SEIZE, child, 0, PTRACE_O_TRACESYSGOOD) < 0) {
        fatal(ERR_PTRACE_SEIZE);
    }
    if (ptrace(PTRACE_INTERRUPT, child, 0, 0) < 0) {
        fatal(ERR_PTRACE_INTERRUPT);
    }
    if (waitpid(child, &status, 0) < 0) {
        fatal(ERR_WAITPID);
    }
    while (1) {
        if (wait_for_syscall(child, &status) == e_exit) {
            return (print_exit(status));
        }
        nb = syscall_nb(child);
        if (wait_for_syscall(child, &status) == e_exit) {
            return (print_exit(status));
        }
        if (nb < NB_SYSCALLS && !strcmp(SYSCALLS[nb].name, "kill")) {
            break;
        }
    }
    while (1) {
        ret = wait_for_syscall(child, &status);
        if (ret == e_exit) {
            break;
        }
        else if (ret == e_syscall) {
            if (!syscall_caught(child, &last_syscall, &status)) {
                break;
            }
        }
        else if (ret == e_signal) {
            signal_caught(child);
        }
    }
    return (print_exit(status));
}

int main(int argc, char **argv) {
    char *program;
    pid_t child;
    int status;

    if (argc < 2) {
        fprintf(stderr, "%s: must have PROG\n", argv[0]);
        return (1);
    }
    program = get_program_path(argv[1]);
    if (!program) {
        fprintf(
            stderr,
            "%s: Can't stat '%s', No such file or directory\n",
            argv[0], argv[1]
        );
        return (1);
    }
    child = fork();
    if (child == -1) {
        fatal(ERR_FORK);
    }
    else if (child == 0) {
        kill(getpid(), SIGSTOP);
        execve(program, argv + 1, environ);
        fatal(ERR_EXEC);
    }
    else {
        status = start_tracing(child);
        free(program);
        return (status);
    }
}
