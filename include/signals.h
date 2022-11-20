#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>

#define MIN_SIGNAL 1
#define MAX_SIGNAL __SIGRTMIN
#define MAX_SIGNAL_CODE 6

typedef struct  s_signal
{
    const char  *name;
    const char  **codes;
    int         code_count;
}               t_signal;

extern t_signal SIGNALS[MAX_SIGNAL + 1];
extern const char *SIGCODES[];

#endif
