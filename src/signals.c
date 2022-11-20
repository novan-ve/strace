#include "../include/signals.h"

/*
 * si_code values
 */
const char *SIGCODES[129] = {
    "SI_USER",
    "SI_QUEUE",
    "SI_TIMER",
    "SI_MESGQ",
    "SI_ASYNCIO",
    "SI_SIGIO",
    "SI_TKILL",
    [60] = "SI_ASYNCNL",
    [128] = "SI_KERNEL"
};

const char *sigill_codes[13] = {
    "",
    "ILL_ILLOPC",
    "ILL_ILLOPN",
    "ILL_ILLADR",
    "ILL_ILLTRP",
    "ILL_PRVOPC",
    "ILL_PRVREG",
    "ILL_COPROC",
    "ILL_BADSTK",
    "ILL_BADIADDR",
    "__ILL_BREAK",
    "__ILL_BNDMOD"
};

const char *sigfpe_codes[17] = {
    "",
    "FPE_INTDIV",
    "FPE_INTOVF",
    "FPE_FLTDIV",
    "FPE_FLTOVF",
    "FPE_FLTUND",
    "FPE_FLTRES",
    "FPE_FLTINV",
    "FPE_FLTSUB",
    "__FPE_DECOVF",
    "__FPE_DECDIV",
    "__FPE_DECERR",
    "__FPE_INVASC",
    "__FPE_INVDEC",
    "FPE_FLTUNK",
    "FPE_CONDTRAP"
};

const char *sigsegv_codes[11] = {
    "",
    "SEGV_MAPERR",
    "SEGV_ACCERR",
    "SEGV_BNDERR",
#ifdef __ia64__
    "__SEGV_PSTKOVF",
#else
    "SEGV_PKUERR",
#endif
    "SEGV_ACCADI",
    "SEGV_ADIDERR",
    "SEGV_ADIPERR",
    "SEGV_MTEAERR",
    "SEGV_MTESERR"
};

const char *sigbus_codes[7] = {
    "",
    "BUS_ADRALN",
    "BUS_ADRERR",
    "BUS_OBJERR",
    "BUS_MCEERR_AR",
    "BUS_MCEERR_AO",
};

const char *sigtrap_codes[8] = {
    "",
    "TRAP_BRKPT",
    "TRAP_TRACE",
    "TRAP_BRANCH",
    "TRAP_HWBKPT",
    "TRAP_UNK",
    "TRAP_PERF"
};

const char *sigchld_codes[8] = {
    "",
    "CLD_EXITED",
    "CLD_KILLED",
    "CLD_DUMPED",
    "CLD_TRAPPED",
    "CLD_STOPPED",
    "CLD_CONTINUED"
};

const char *sigpoll_codes[8] = {
    "",
    "POLL_IN",
    "POLL_OUT",
    "POLL_MSG",
    "POLL_ERR",
    "POLL_PRI",
    "POLL_HUP"
};

const char *sigsys_codes[4] = {
    "",
    "SYS_SECCOMP",
    "SYS_USER_DISPATCH"
};

t_signal SIGNALS[MAX_SIGNAL + 1] = {
    [SIGHUP] = {"SIGHUP", 0, 0},
    [SIGINT] = {"SIGINT", 0, 0},
    [SIGQUIT] = {"SIGQUIT", 0, 0},
    [SIGILL] = {"SIGILL", sigill_codes, 12},
    [SIGTRAP] = {"SIGTRAP", sigtrap_codes, 7},
    [SIGABRT] = {"SIGABRT", 0, 0},
    [SIGBUS] = {"SIGBUS", sigbus_codes, 6},
    [SIGFPE] = {"SIGFPE", sigfpe_codes, 16},
    [SIGKILL] = {"SIGKILL", 0, 0},
    [SIGUSR1] = {"SIGUSR1", 0, 0},
    [SIGSEGV] = {"SIGSEGV", sigsegv_codes, 10},
    [SIGUSR2] = {"SIGUSR2", 0, 0},
    [SIGPIPE] = {"SIGPIPE", 0, 0},
    [SIGALRM] = {"SIGALRM", 0, 0},
    [SIGTERM] = {"SIGTERM", 0, 0},
    [SIGSTKFLT] = {"SIGSTKFLT", 0, 0},
    [SIGCHLD] = {"SIGCHLD", sigchld_codes, 7},
    [SIGCONT] = {"SIGCONT", 0, 0},
    [SIGSTOP] = {"SIGSTOP", 0, 0},
    [SIGTSTP] = {"SIGTSTP", 0, 0},
    [SIGTTIN] = {"SIGTTIN", 0, 0},
    [SIGTTOU] = {"SIGTTOU", 0, 0},
    [SIGURG] = {"SIGURG", 0, 0},
    [SIGXCPU] = {"SIGXCPU", 0, 0},
    [SIGXFSZ] = {"SIGXFSZ", 0, 0},
    [SIGVTALRM] = {"SIGVTALRM", 0, 0},
    [SIGPROF] = {"SIGPROF", 0, 0},
    [SIGWINCH] = {"SIGWINCH", 0, 0},
    [SIGPOLL] = {"SIGPOLL", sigpoll_codes, 7},
    [SIGPWR] = {"SIGPWR", 0, 0},
    [SIGSYS] = {"SIGSYS", sigsys_codes, 3},
    [__SIGRTMIN] = {"SIGRTMIN", 0, 0}
};
