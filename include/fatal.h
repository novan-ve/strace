#ifndef ERROR_H
#define ERROR_H

#define PROGRAM_NAME "strace"

#define ERR_EXEC "exec failed"
#define ERR_FORK "fork failed"
#define ERR_WAITPID "waitpid failed"
#define ERR_MALLOC "malloc failed"

#define ERR_SYSCALL_ARG "unsupported syscall argument"
#define ERR_SYSCALL_RET "unsupported syscall return type"

#define ERR_PTRACE_SEIZE "PTRACE_SEIZE failed"
#define ERR_PTRACE_INTERRUPT "PTRACE_INTERRUPT failed"
#define ERR_PTRACE_SYSCALL "PTRACE_SYSCALL failed"
#define ERR_PTRACE_GETREGSET "PTRACE_GETREGSET failed"
#define ERR_PTRACE_GETSIGINFO "PTRACE_GETSIGINFO failed"
#define ERR_PTRACE_LISTEN "PTRACE_LISTEN failed"

void fatal(const char *description);

#endif
