#ifndef SYSCALL_H
#define SYSCALL_H

#include <stddef.h>

typedef enum {
    _void,
    _str,
    _str_arr,
    _ptr,
    _int,
    _uint,
    _long,
    _ulong,
} arg_type;

typedef struct  s_syscall
{
    const char  *name;
    arg_type    ret_type;
    arg_type    arg_type[6];
    int         arg_count;
    int         uninit_arg;
}               t_syscall;

#ifdef __x86_64__
  #define NB_SYSCALLS 352
  #define SYSCALL_NB(regs) regs->orig_rax
#else
  #define NB_SYSCALLS 385
  #define SYSCALL_NB(regs) regs->orig_eax
#endif  /* __x86_64__ */

extern t_syscall SYSCALLS[NB_SYSCALLS];

#endif  /* SYSCALL_H */
