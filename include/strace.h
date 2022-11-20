#ifndef STRACE_H
#define STRACE_H

#include <sys/user.h>
#include <sys/wait.h>

#define MAX_STR_SIZE 32
#define PEEKDATA_ENABLED 1

typedef enum {
    e_exit,
    e_syscall,
    e_signal
} e_status;

void print_signal(const siginfo_t *sig);
size_t print_syscall(struct user_regs_struct *regs);
size_t print_args(pid_t child, struct user_regs_struct *regs,
                  int second_run, int signal);
void print_return(pid_t child, struct user_regs_struct *regs);
void print_padding(size_t len);
int print_exit(int status);

char *get_program_path(const char *program);
size_t get_data(struct user_regs_struct *regs, int arg);
size_t get_len_arg(struct user_regs_struct *regs, int arg);
void *get_ptr_data(pid_t child, size_t ptr, size_t len, int is_arr);
int has_empty_buffer(struct user_regs_struct *regs);
unsigned long long get_errno(struct user_regs_struct *regs);

#endif
