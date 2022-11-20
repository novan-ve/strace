#include "../include/strace.h"
#include "../include/fatal.h"
#include "../include/syscall.h"
#include "../include/signals.h"
#include "../include/errno_names.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void print_padding(size_t len) {
    fprintf(stderr, ")");
    if (len < 38) {
        fprintf(stderr, "%*s", 38 - (int)len, " ");
    }
    fprintf(stderr, " ");
}

int print_exit(int status) {
    if (WIFSIGNALED(status)) {
        if (status >= MIN_SIGNAL && status <= MAX_SIGNAL) {
            fprintf(stderr, "+++ killed by %s +++\n", SIGNALS[status].name);
        }
        else {
            fprintf(stderr, "+++ killed by SIGRT_%d +++\n", status - MAX_SIGNAL);
        }
        raise(status);
    }
    if (WIFEXITED(status)) {
        fprintf(stderr, "+++ exited with %d +++\n", WEXITSTATUS(status));
    }
    return (WEXITSTATUS(status));
}

size_t print_syscall(struct user_regs_struct *regs) {
    if (SYSCALL_NB(regs) < NB_SYSCALLS && SYSCALLS[SYSCALL_NB(regs)].name) {
        t_syscall syscall = SYSCALLS[SYSCALL_NB(regs)];
        return(fprintf(stderr, "%s(", syscall.name));
    }
    else {
        return(fprintf(stderr, "syscall_0x%llx", SYSCALL_NB(regs)));
    }
}

void print_signal(const siginfo_t *sig) {
    fprintf(stderr, "--- ");
    if (sig->si_signo >= MIN_SIGNAL && sig->si_signo <= MAX_SIGNAL) {
        fprintf(stderr, "%s ", SIGNALS[sig->si_signo].name);
        fprintf(stderr, "{si_signo=%s", SIGNALS[sig->si_signo].name);
    }
    else {
        fprintf(stderr, "SIGRT_%d ", sig->si_signo - MAX_SIGNAL);
        fprintf(stderr, "{si_signo=%d", sig->si_signo);
    }

    if ((sig->si_code <= 0 && abs(sig->si_code) <= MAX_SIGNAL_CODE) ||
        sig->si_code == SI_KERNEL || sig->si_code == SI_ASYNCNL) {
        fprintf(stderr, ", si_code=%s", SIGCODES[abs(sig->si_code)]);
    }
    else if (sig->si_code > 0 && sig->si_code < SIGNALS[sig->si_signo].code_count) {
        fprintf(stderr, ", si_code=%s", SIGNALS[sig->si_signo].codes[sig->si_code]);
    }
    else {
        fprintf(stderr, ", si_code=%d", sig->si_code);
    }

    if (sig->si_signo == SIGSEGV || sig->si_signo == SIGBUS) {
        fprintf(stderr, ", si_addr=0x%p", sig->si_addr);
    }
    else if (sig->si_signo != SIGTSTP && sig->si_signo != SIGWINCH) {
        fprintf(stderr, ", si_pid=%d, si_uid=%d", sig->si_pid, sig->si_uid);
        if (sig->si_signo == SIGCHLD) {
            if (sig->si_status >= MIN_SIGNAL && sig->si_status <= MAX_SIGNAL) {
                fprintf(stderr, ", si_status=%s", SIGNALS[sig->si_status].name);
            }
            else {
                fprintf(stderr, ", si_status=%d", sig->si_status);
            }
            fprintf(stderr, ", si_utime=%ld, si_stime=%ld", sig->si_utime, sig->si_stime);
        }
    }
    fprintf(stderr, "} ---\n");
}

void print_return(pid_t child, struct user_regs_struct *regs) {
    arg_type ret_type = SYSCALLS[SYSCALL_NB(regs)].ret_type;
#ifdef __x86_64__
    size_t ret = regs->rax;
#else
    size_t ret = regs->eax;
#endif  /* __x86_64__ */

    fprintf(stderr, "= ");
    if (ret_type == _void) {
        fprintf(stderr, "0\n");
    }
    else {
        int errno_nb = __SIZE_MAX__ - ret + 1;
        if (errno_nb >= MIN_SIGNAL_ERRNO && errno_nb <= MAX_SIGNAL_ERRNO) {
            fprintf(stderr, "? %s ", ERRNO_NAMES[errno_nb]);
            if (errno_nb >= 512 && errno_nb <= 514) {
                fprintf(stderr, "(To be restarted if SA_RESTART is set)\n");
            }
            else if (errno_nb == 516) {
                fprintf(stderr, "(Interrupted by signal)\n");
            }
            else {
                fprintf(stderr, "(%s)\n", strerror(errno_nb));
            }
        }
        else if (errno_nb >= MIN_SYSCALL_ERRNO && errno_nb <= MAX_SYSCALL_ERRNO) {
            fprintf(stderr, "-1 ");
            fprintf(stderr, "%s ", ERRNO_NAMES[errno_nb]);
            fprintf(stderr, "(%s)\n", strerror(errno_nb));
        }
        else if (ret_type == _int) {
            fprintf(stderr, "%d\n", (int)ret);
        }
        else if (ret_type == _uint) {
            fprintf(stderr, "%u\n", (unsigned int)ret);
        }
        else if (ret_type == _long) {
            fprintf(stderr, "%ld\n", (long)ret);
        }
        else if (ret_type == _ulong) {
            fprintf(stderr, "%lu\n", ret);
        }
        else if (ret_type == _str) {
            if (ret)
                fprintf(stderr, "%lu\n", strlen(get_ptr_data(child, ret, -1, 1)));
            else
                fprintf(stderr, "NULL\n");
        }
        else if (ret_type == _ptr || ret == _str_arr) {
            if (ret)
                fprintf(stderr, "%p\n", (void*)ret);
            else
                fprintf(stderr, "NULL\n");
        }
        else {
            fatal(ERR_SYSCALL_RET);
        }
    }
}
