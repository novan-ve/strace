#include "../include/syscall.h"

#ifdef __x86_64__

t_syscall SYSCALLS[NB_SYSCALLS] = {
    {"read", _long, {_int, _str, _ulong}, 3, 1},
    {"write", _long, {_int, _str, _ulong}, 3, 3},
    {"open", _int, {_str, _int, _uint}, 3, 3},
    {"close", _int, {_int}, 1, 1},
    {"stat", _int, {_str, _ptr}, 2, 1},
    {"fstat", _int, {_int, _ptr}, 2, 1},
    {"lstat", _int, {_str, _ptr}, 2, 1},
    {"poll", _int, {_ptr, _uint, _int}, 3, 3},
    {"lseek", _long, {_int, _long, _int}, 3, 3},
    {"mmap", _ptr, {_ptr, _ulong, _int, _int, _int, _long}, 6, 6},
    {"mprotect", _int, {_ptr, _ulong, _int}, 3, 3},
    {"munmap", _int, {_ptr, _ulong}, 2, 2},
    {"brk", _ptr, {_ptr}, 1, 1},
    {"rt_sigaction", _long, {_int, _ptr, _ptr, _ulong}, 4, 2},
    {"rt_sigprocmask", _long, {_int, _ptr, _ptr, _ulong}, 4, 4},
    {"rt_sigreturn", _long, {}, 0, 0},
    {"ioctl", _int, {_int, _long, _ulong}, 3, 3},
    {"pread64", _long, {_int, _str, _ulong, _long}, 4, 1},
    {"pwrite64", _long, {_int, _str, _ulong, _long}, 4, 4},
    {"readv", _long, {_int, _ptr, _int}, 3, 1},
    {"writev", _long, {_int, _ptr, _int}, 3, 3},
    {"access", _int, {_str, _int}, 2, 2},
    {"pipe", _int, {_ptr}, 1, 1},
    {"select", _int, {_int, _ptr, _ptr, _ptr, _ptr}, 5, 5},
    {"sched_yield", _int, {}, 0, 0},
    {"mremap", _ptr, {_ptr, _ulong, _ulong, _int, _ptr}, 5, 5},
    {"msync", _int, {_ptr, _ulong, _int}, 3, 3},
    {"mincore", _int, {_ptr, _ulong, _str}, 3, 3},
    {"madvise", _int, {_ptr, _ulong, _int}, 3, 3},
    {"shmget", _int, {_int, _ulong, _int}, 3, 3},
    {"shmat", _ptr, {_int, _ptr, _int}, 3, 3},
    {"shmctl", _int, {_int, _int, _ptr}, 3, 3},
    {"dup", _int, {_int}, 1, 1},
    {"dup2", _int, {_int, _int}, 2, 2},
    {"pause", _int, {}, 0, 0},
    {"nanosleep", _int, {_ptr, _ptr}, 2, 1},
    {"getitimer", _int, {_int, _ptr}, 2, 1},
    {"alarm", _uint, {_uint}, 1, 1},
    {"setitimer", _int, {_int, _ptr, _ptr}, 3, 2},
    {"getpid", _int, {}, 0, 0},
    {"sendfile", _long, {_int, _int, _ptr, _ulong}, 4, 4},
    {"socket", _int, {_int, _int, _int}, 3, 3},
    {"connect", _int, {_int, _ptr, _int}, 3, 3},
    {"accept", _int, {_int, _ptr, _ptr}, 3, 1},
    {"sendto", _long, {_int, _ptr, _ulong, _int, _ptr, _int}, 6, 6},
    {"recvfrom", _long, {_int, _ptr, _ulong, _int, _ptr, _ptr}, 6, 1},
    {"sendmsg", _long, {_int, _ptr, _int}, 3, 3},
    {"recvmsg", _long, {_int, _ptr, _int}, 3, 1},
    {"shutdown", _int, {_int, _int}, 2, 2},
    {"bind", _int, {_int, _ptr, _int}, 3, 3},
    {"listen", _int, {_int, _int}, 2, 2},
    {"getsockname", _int, {_int, _ptr, _ptr}, 3, 1},
    {"getpeername", _int, {_int, _ptr, _ptr}, 3, 1},
    {"socketpair", _int, {_int, _int, _int, _ptr}, 4, 4},
    {"setsockopt", _int, {_int, _int, _int, _str, _int}, 5, 5},
    {"getsockopt", _int, {_int, _int, _int, _str, _ptr}, 5, 4},
    {"clone", _int, {_ulong, _ulong, _ptr, _ptr, _int}, 5, 5},
    {"fork", _int, {}, 0, 0},
    {"vfork", _int, {}, 0, 0},
    {"execve", _int, {_str, _str_arr, _str_arr}, 3, 3},
    {"exit", _void, {_int}, 1, 1},
    {"wait4", _int, {_int, _ptr, _int, _ptr}, 4, 1},
    {"kill", _int, {_int, _int}, 2, 2},
    {"uname", _int, {_ptr}, 1, 0},
    {"semget", _int, {_int, _int, _int}, 3, 3},
    {"semop", _int, {_int, _ptr, _ulong}, 3, 3},
    {"semctl", _int, {_int, _int, _int, _ulong}, 4, 4},
    {"shmdt", _int, {_ptr}, 1, 1},
    {"msgget", _int, {_int, _int}, 2, 2},
    {"msgsnd", _int, {_int, _ptr, _ulong, _int}, 4, 4},
    {"msgrcv", _long, {_int, _ptr, _ulong, _long, _int}, 5, 5},
    {"msgctl", _int, {_int, _int, _ptr}, 3, 3},
    {"fcntl", _int, {_int, _int, _ulong}, 3, 3},
    {"flock", _int, {_int, _int}, 2, 2},
    {"fsync", _int, {_int}, 1, 1},
    {"fdatasync", _int, {_int}, 1, 1},
    {"truncate", _int, {_str, _long}, 2, 2},
    {"ftruncate", _int, {_int, _long}, 2, 2},
    {"getdents", _long, {_uint, _ptr, _uint}, 3, 1},
    {"getcwd", _str, {_str, _ulong}, 2, 2},
    {"chdir", _int, {_str}, 1, 1},
    {"fchdir", _int, {_int}, 1, 1},
    {"rename", _int, {_str, _str}, 2, 2},
    {"mkdir", _int, {_str, _uint}, 2, 2},
    {"rmdir", _int, {_str}, 1, 1},
    {"creat", _int, {_str, _uint}, 2, 2},
    {"link", _int, {_str, _str}, 2, 2},
    {"unlink", _int, {_str}, 1, 1},
    {"symlink", _int, {_str, _str}, 2, 2},
    {"readlink", _long, {_str, _str, _ulong}, 3, 1},
    {"chmod", _int, {_str, _uint}, 2, 2},
    {"fchmod", _int, {_int, _uint}, 2, 2},
    {"chown", _int, {_str, _uint, _uint}, 3, 3},
    {"fchown", _int, {_int, _uint, _uint}, 3, 3},
    {"lchown", _int, {_str, _uint, _uint}, 3, 3},
    {"umask", _long, {_long}, 1, 1},
    {"gettimeofday", _int, {_ptr, _ptr}, 2, 1},
    {"getrlimit", _int, {_int, _ptr}, 2, 1},
    {"getrusage", _int, {_int, _ptr}, 2, 1},
    {"sysinfo", _int, {_ptr}, 1, 0},
    {"times", _ulong, {_ptr}, 1, 0},
    {"ptrace", _long, {_long, _int, _ptr, _ptr}, 4, 4},
    {"getuid", _uint, {}, 0, 0},
    {"syslog", _int, {_int, _str, _int}, 3, 3},
    {"getgid", _uint, {}, 0, 0},
    {"setuid", _int, {_uint}, 1, 1},
    {"setgid", _int, {_uint}, 1, 1},
    {"geteuid", _uint, {}, 0, 0},
    {"getegid", _uint, {}, 0, 0},
    {"setpgid", _int, {_int, _int}, 2, 2},
    {"getppid", _int, {}, 0, 0},
    {"getpgrp", _int, {}, 0, 0},
    {"setsid", _int, {}, 0, 0},
    {"setreuid", _int, {_uint, _uint}, 2, 2},
    {"setregid", _int, {_uint, _uint}, 2, 2},
    {"getgroups", _int, {_int, _ptr}, 2, 1},
    {"setgroups", _int, {_int, _ptr}, 2, 2},
    {"setresuid", _int, {_uint, _uint, _uint}, 3, 3},
    {"getresuid", _int, {_ptr, _ptr, _ptr}, 3, 0},
    {"setresgid", _int, {_uint, _uint, _uint}, 3, 3},
    {"getresgid", _int, {_ptr, _ptr, _ptr}, 3, 0},
    {"getpgid", _int, {_int}, 1, 1},
    {"setfsuid", _int, {_uint}, 1, 1},
    {"setfsgid", _int, {_uint}, 1, 1},
    {"getsid", _int, {_int}, 1, 1},
    {"capget", _int, {_ptr, _ptr}, 2, 0},
    {"capset", _int, {_ptr, _ptr}, 2, 2},
    {"rt_sigpending", _long, {_ptr, _ulong}, 2, 2},
    {"rt_sigtimedwait", _long, {_ptr, _ptr, _ptr, _ulong}, 4, 4},
    {"rt_sigqueueinfo", _int, {_int, _int, _ptr}, 3, 2},
    {"rt_sigsuspend", _long, {_ptr, _ulong}, 2, 2},
    {"sigaltstack", _int, {_ptr, _ptr}, 2, 0},
    {"utime", _int, {_str, _ptr}, 2, 2},
    {"mknod", _int, {_str, _uint, _uint}, 3, 3},
    {"uselib", _int, {_str}, 1, 1},
    {"personality", _int, {_ulong}, 1, 1},
    {"ustat", _int, {_uint, _ptr}, 2, 1},
    {"statfs", _int, {_str, _ptr}, 2, 1},
    {"fstatfs", _int, {_uint, _ptr}, 2, 1},
    {"sysfs", _int, {_int, _uint, _str}, 3, 3},
    {"getpriority", _int, {_int, _int}, 2, 2},
    {"setpriority", _int, {_int, _int, _int}, 3, 3},
    {"sched_setparam", _int, {_int, _ptr}, 2, 2},
    {"sched_getparam", _int, {_int, _ptr}, 2, 1},
    {"sched_setscheduler", _int, {_int, _int, _ptr}, 3, 3},
    {"sched_getscheduler", _int, {_int}, 1, 1},
    {"sched_get_priority_max", _int, {_int}, 1, 1},
    {"sched_get_priority_min", _int, {_int}, 1, 1},
    {"sched_rr_get_interval", _int, {_int, _ptr}, 2, 1},
    {"mlock", _int, {_ptr, _ulong}, 2, 2},
    {"munlock", _int, {_ptr, _ulong}, 2, 2},
    {"mlockall", _int, {_int}, 1, 1},
    {"munlockall", _int, {}, 0, 0},
    {"vhangup", _int, {}, 0, 0},
    {"modify_ldt", _int, {_int, _ptr, _ulong}, 3, 1},
    {"pivot_root", _int, {_str, _str}, 2, 2},
    {"_sysctl", _int, {_ptr}, 1, 1},
    {"prctl", _int, {_int, _ulong, _ulong, _ulong, _ulong}, 5, 5},
    {"arch_prctl", _int, {_int, _ulong}, 2, 2},
    {"adjtimex", _int, {_ptr}, 1, 1},
    {"setrlimit", _int, {_int, _ptr}, 2, 2},
    {"chroot", _int, {_str}, 1, 1},
    {"sync", _void, {}, 0, 0},
    {"acct", _int, {_str}, 1, 1},
    {"settimeofday", _int, {_ptr, _ptr}, 2, 2},
    {"mount", _int, {_str, _str, _str, _ulong, _ptr}, 5, 5},
    {"umount2", _int, {_str, _int}, 2, 2},
    {"swapon", _int, {_str, _int}, 2, 2},
    {"swapoff", _int, {_str}, 1, 1},
    {"reboot", _int, {_int, _int, _int, _ptr}, 4, 4},
    {"sethostname", _int, {_str, _ulong}, 2, 2},
    {"setdomainname", _int, {_str, _ulong}, 2, 2},
    {"iopl", _int, {_int}, 1, 1},
    {"ioperm", _int, {_ulong, _ulong, _int}, 3, 3},
    {"create_module", _ulong, {}, 0, 0},
    {"init_module", _int, {_ptr, _ulong, _str}, 3, 3},
    {"delete_module", _int, {_str, _int}, 2, 2},
    {"get_kernel_syms", _int, {_ptr}, 1, 0},
    {"query_module", _long, {}, 0, 0},
    {"quotactl", _int, {_int, _str, _int, _ptr}, 4, 4},
    {"nfsservctl", _long, {}, 0, 0},
    {"getpmsg", _long, {}, 0, 0},
    {"putpmsg", _long, {}, 0, 0},
    {"afs_syscall", _long, {}, 0, 0},
    {"tuxcall", _long, {}, 0, 0},
    {"security", _long, {}, 0, 0},
    {"gettid", _int, {}, 0, 0},
    {"readahead", _long, {_int, _long, _ulong}, 3, 3},
    {"setxattr", _int, {_str, _str, _str, _ulong, _int}, 5, 5},
    {"lsetxattr", _int, {_str, _str, _str, _ulong, _int}, 5, 5},
    {"fsetxattr", _int, {_int, _str, _str, _ulong, _int}, 5, 5},
    {"getxattr", _long, {_str, _str, _ptr, _ulong}, 4, 2},
    {"lgetxattr", _long, {_str, _str, _ptr, _ulong}, 4, 2},
    {"fgetxattr", _long, {_int, _str, _ptr, _ulong}, 4, 2},
    {"listxattr", _long, {_str, _str, _ulong}, 3, 1},
    {"llistxattr", _long, {_str, _str, _ulong}, 3, 1},
    {"flistxattr", _long, {_int, _str, _ulong}, 3, 1},
    {"removexattr", _int, {_str, _str}, 2, 2},
    {"lremovexattr", _int, {_str, _str}, 2, 2},
    {"fremovexattr", _int, {_int, _str}, 2, 2},
    {"tkill", _int, {_int, _int}, 2, 2},
    {"time", _ulong, {_ptr}, 1, 0},
    {"futex", _long, {_ptr, _int, _uint, _ptr, _ptr, _uint}, 6, 6},
    {"sched_setaffinity", _int, {_int, _ulong, _ptr}, 3, 3},
    {"sched_getaffinity", _int, {_int, _ulong, _ptr}, 3, 2},
    {"set_thread_area", _int, {_ptr}, 1, 1},
    {"io_setup", _int, {_uint, _ptr}, 2, 1},
    {"io_destroy", _int, {_ulong}, 1, 1},
    {"io_getevents", _int, {_ulong, _long, _long, _ptr, _ptr}, 5, 5},
    {"io_submit", _int, {_ulong, _long, _ptr}, 3, 2},
    {"io_cancel", _int, {_ulong, _ptr, _ptr}, 3, 2},
    {"get_thread_area", _int, {_ptr}, 1, 0},
    {"lookup_dcookie", _int, {_ulong, _str, _ulong}, 3, 1},
    {"epoll_create", _int, {_int}, 1, 1},
    {"epoll_ctl_old", _long, {}, 0, 0},
    {"epoll_wait_old", _long, {}, 0, 0},
    {"remap_file_pages", _int, {_ptr, _ulong, _ulong, _ulong, _int}, 5, 5},
    {"getdents64", _long, {_uint, _ptr, _uint}, 3, 1},
    {"set_tid_address", _int, {_ptr}, 1, 1},
    {"restart_syscall", _long, {}, 0, 0},
    {"semtimedop", _int, {_int, _ptr, _ulong, _ptr}, 4, 1},
    {"fadvise64", _long, {_int, _long, _long, _int}, 4, 4},
    {"timer_create", _int, {_int, _ptr, _ptr}, 3, 3},
    {"timer_settime", _int, {_ulong, _int, _ptr, _ptr}, 4, 4},
    {"timer_gettime", _int, {_ulong, _ptr}, 2, 1},
    {"timer_getoverrun", _int, {_ulong}, 1, 1},
    {"timer_delete", _int, {_ulong}, 1, 1},
    {"clock_settime", _int, {_int, _ptr}, 2, 2},
    {"clock_gettime", _int, {_int, _ptr}, 2, 1},
    {"clock_getres", _int, {_int, _ptr}, 2, 1},
    {"clock_nanosleep", _int, {_int, _int, _ptr, _ptr}, 4, 3},
    {"exit_group", _void, {_int}, 1, 1},
    {"epoll_wait", _int, {_int, _ptr, _int, _int}, 4, 4},
    {"epoll_ctl", _int, {_int, _int, _int, _ptr}, 4, 4},
    {"tgkill", _int, {_int, _int, _int}, 3, 3},
    {"utimes", _int, {_str, _ptr}, 2, 2},
    {"vserver", _long, {}, 0, 0},
    {"mbind", _long, {_ptr, _ulong, _int, _ptr, _ulong, _uint}, 6, 6},
    {"set_mempolicy", _long, {_int, _ptr, _ulong}, 3, 3},
    {"get_mempolicy", _int, {_ptr, _ptr, _ulong, _ptr, _ulong}, 5, 3},
    {"mq_open", _long, {_str, _int, _uint, _ptr}, 4, 4},
    {"mq_unlink", _int, {_str}, 1, 1},
    {"mq_timedsend", _int, {_int, _str, _ulong, _uint, _ptr}, 5, 5},
    {"mq_timedreceive", _long, {_int, _str, _ulong, _ptr, _ptr}, 5, 1},
    {"mq_notify", _int, {_int, _ptr}, 2, 2},
    {"mq_getsetattr", _int, {_long, _ptr, _ptr}, 3, 2},
    {"kexec_load", _long, {_ulong, _ulong, _ptr, _ulong}, 4, 2},
    {"waitid", _int, {_int, _int, _ptr, _int, _ptr}, 5, 5},
    {"add_key", _int, {_str, _str, _ptr, _ulong, _int}, 5, 5},
    {"request_key", _int, {_str, _str, _str, _int}, 4, 4},
    {"keyctl", _long, {_int, _ulong, _ulong, _ulong, _ulong}, 5, 5},
    {"ioprio_set", _int, {_int, _int, _int}, 3, 3},
    {"ioprio_get", _int, {_int, _int}, 2, 2},
    {"inotify_init", _int, {}, 0, 0},
    {"inotify_add_watch", _int, {_int, _str, _uint}, 3, 3},
    {"inotify_rm_watch", _int, {_int, _int}, 2, 2},
    {"migrate_pages", _long, {_int, _ulong, _ptr, _ptr}, 4, 4},
    {"openat", _int, {_int, _str, _int}, 3, 3},
    {"mkdirat", _int, {_int, _str, _uint}, 3, 3},
    {"mknodat", _int, {_int, _str, _uint, _ulong}, 4, 4},
    {"fchownat", _int, {_int, _str, _uint, _uint, _int}, 5, 5},
    {"futimesat", _int, {_int, _str, _ptr}, 3, 3},
    {"newfstatat", _int, {_int, _str, _ptr, _int}, 4, 2},
    {"unlinkat", _int, {_int, _str, _int}, 3, 3},
    {"renameat", _int, {_int, _str, _int, _str}, 4, 4},
    {"linkat", _int, {_int, _str, _int, _str, _int}, 5, 5},
    {"symlinkat", _int, {_str, _int, _str}, 3, 3},
    {"readlinkat", _long, {_int, _str, _str, _ulong}, 4, 2},
    {"fchmodat", _int, {_int, _str, _uint}, 3, 3},
    {"faccessat", _int, {_int, _str, _int}, 3, 3},
    {"pselect6", _long, {_int, _ptr, _ptr, _ptr, _ptr, _ptr}, 6, 6},
    {"ppoll", _int, {_ptr, _uint, _ptr, _ptr, _ptr}, 5, 5},
    {"unshare", _int, {_int}, 1, 1},
    {"set_robust_list", _long, {_ptr, _ulong}, 2, 2},
    {"get_robust_list", _long, {_int, _ptr, _ptr}, 3, 1},
    {"splice", _long, {_int, _ptr, _int, _ptr, _ulong, _uint}, 6, 3},
    {"tee", _long, {_int, _int, _ulong, _uint}, 4, 4},
    {"sync_file_range", _int, {_int, _long, _long, _uint}, 4, 4},
    {"vmsplice", _long, {_int, _ptr, _ulong, _uint}, 4, 1},
    {"move_pages", _long, {_int, _ulong, _ptr, _ptr, _ptr, _int}, 6, 6},
    {"utimensat", _int, {_int, _str, _ptr, _int}, 4, 4},
    {"epoll_pwait", _int, {_int, _ptr, _int, _int, _ptr}, 5, 5},
    {"signalfd", _int, {_int, _ptr, _int}, 3, 3},
    {"timerfd_create", _int, {_int, _int}, 2, 2},
    {"eventfd", _int, {_uint, _int}, 2, 2},
    {"fallocate", _int, {_int, _int, _long, _long}, 4, 4},
    {"timerfd_settime", _int, {_int, _int, _ptr, _ptr}, 4, 4},
    {"timerfd_gettime", _int, {_int, _ptr}, 2, 1},
    {"accept4", _int, {_int, _ptr, _ptr, _int}, 4, 1},
    {"signalfd4", _int, {_int, _ptr, _int}, 3, 3},
    {"eventfd2", _long, {_uint, _int}, 2, 2},
    {"epoll_create1", _int, {_int}, 1, 1},
    {"dup3", _int, {_int, _int, _int}, 3, 3},
    {"pipe2", _int, {_ptr, _int}, 2, 2},
    {"inotify_init1", _int, {_int}, 1, 1},
    {"preadv", _long, {_int, _ptr, _int, _long}, 4, 1},
    {"pwritev", _long, {_int, _ptr, _int, _long}, 4, 4},
    {"rt_tgsigqueueinfo", _int, {_int, _int, _int, _ptr}, 4, 4},
    {"perf_event_open", _int, {_ptr, _int, _int, _int, _ulong}, 5, 5},
    {"recvmmsg", _int, {_int, _ptr, _uint, _int, _ptr}, 5, 1},
    {"fanotify_init", _int, {_uint, _uint}, 2, 2},
    {"fanotify_mark", _int, {_int, _uint, _ulong, _int, _str}, 5, 5},
    {"prlimit64", _long, {_int, _uint, _ptr, _ptr}, 4, 2},
    {"name_to_handle_at", _int, {_int, _str, _ptr, _ptr, _int}, 5, 3},
    {"open_by_handle_at", _int, {_int, _ptr, _int}, 3, 3},
    {"clock_adjtime", _int, {_int, _ptr}, 2, 1},
    {"syncfs", _int, {_int}, 1, 1},
    {"sendmmsg", _int, {_int, _ptr, _uint, _int}, 4, 4},
    {"setns", _int, {_int, _int}, 2, 2},
    {"getcpu", _int, {_ptr, _ptr, _ptr}, 3, 0},
    {"process_vm_readv", _long, {_int, _ptr, _ulong, _ptr, _ulong, _ulong}, 6, 1},
    {"process_vm_writev", _long, {_int, _ptr, _ulong, _ptr, _ulong, _ulong}, 6, 6},
    {"kcmp", _int, {_int, _int, _int, _ulong, _ulong}, 5, 5},
    {"finit_module", _int, {_int, _str, _int}, 3, 3},
    {"sched_setattr", _int, {_int, _ptr, _uint}, 3, 3},
    {"sched_getattr", _int, {_int, _ptr, _uint, _uint}, 4, 1},
    {"renameat2", _int, {_int, _str, _int, _str, _uint}, 5, 5},
    {"seccomp", _int, {_uint, _uint, _ptr}, 3, 3},
    {"getrandom", _long, {_ptr, _ulong, _uint}, 3, 0},
    {"memfd_create", _int, {_str, _uint}, 2, 2},
    {"kexec_file_load", _long, {_ulong, _ulong, _ptr, _ulong}, 4, 4},
    {"bpf", _int, {_int, _ptr, _uint}, 3, 1},
    {"execveat", _int, {_int, _str, _str_arr, _str_arr, _int}, 5, 5},
    {"userfaultfd", _int, {_int}, 1, 1},
    {"membarrier", _int, {_int, _uint, _int}, 3, 3},
    {"mlock2", _int, {_ptr, _ulong, _int}, 3, 3},
    {"copy_file_range", _long, {_int, _ptr, _int, _ptr, _ulong, _uint}, 6, 1},
    {"preadv2", _long, {_int, _ptr, _int, _int, _int}, 5, 1},
    {"pwritev2", _long, {_int, _ptr, _int, _int, _int}, 5, 5},
    {"pkey_mprotect", _int, {_ptr, _long, _int, _int}, 4, 4},
    {"pkey_alloc", _int, {_uint, _uint}, 2, 2},
    {"pkey_free", _int, {_int}, 1, 1},
    {"statx", _int, {_int, _str, _int, _uint, _ptr}, 5, 4},
    {"io_pgetevents", _int, {_int, _long, _long, _ptr, _ptr, _ptr}, 6, 3},
    {"rseq", _int, {_ptr, _uint, _int, _uint}, 4, 4},
    {"pidfd_send_signal", _int, {_int, _int, _ptr, _uint}, 4, 4},
    {"io_uring_setup", _int, {_uint, _ptr}, 2, 2},
    {"io_uring_enter", _int, {_int, _uint, _uint, _uint, _ptr}, 5, 5},
    {"io_uring_register", _int, {_int, _uint, _ptr, _uint}, 4, 4},
    {"open_tree", _int, {_int, _str, _uint}, 3, 3},
    {"move_mount", _int, {_int, _str, _int, _str, _uint}, 5, 5},
    {"fsopen", _int, {_str, _uint}, 2, 2},
    {"fsconfig", _int, {_int, _uint, _str, _ptr, _int}, 5, 5},
    {"fsmount", _int, {_int, _uint, _uint}, 3, 3},
    {"fspick", _int, {_int, _str, _uint}, 3, 3},
    {"pidfd_open", _int, {_int, _uint}, 2, 2},
    {"clone3", _long, {_ptr, _ulong}, 2, 2},
    {"close_range", _int, {_uint, _uint, _uint}, 3, 3},
    {"openat2", _int, {_int, _str, _ptr, _ulong}, 4, 4},
    {"pidfd_getfd", _int, {_int, _int, _uint}, 3, 3},
    {"faccessat2", _int, {_int, _str, _int, _int}, 4, 4},
    {"process_madvise", _int, {_int, _ptr, _ulong, _int, _uint}, 5, 1}
};
#else
t_syscall SYSCALLS[NB_SYSCALLS] = {
    {"restart_syscall", _long, {}, 0, 0},
    {"exit", _void, {_int}, 1, 1},
    {"fork", _long, {}, 0, 0},
    {"read", _long, {_uint, _str, _ulong}, 3, 1},
    {"write", _long, {_uint, _str, _ulong}, 3, 3},
    {"open", _int, {_str, _int, _uint}, 3, 3},
    {"close", _long, {_uint}, 1, 1},
    {"waitpid", _int, {_ptr}, 1, 1},
    {"creat", _int, {_str, _uint}, 2, 2},
    {"link", _int, {_str, _str}, 2, 2},
    {"unlink", _int, {_str}, 1, 1},
    {"execve", _int, {_str, _str_arr, _str_arr}, 3, 3},
    {"chdir", _int, {_str}, 1, 1},
    {"time", _ulong, {_ptr}, 1, 0},
    {"mknod", _int, {_str, _uint, _uint}, 3, 3},
    {"chmod", _int, {_str, _uint}, 2, 2},
    {"lchown16", _int, {_str, _uint, _uint}, 3, 3},
    {NULL, _void, {}, 0, 0},
    {"stat", _int, {_str, _ptr}, 2, 1},
    {"lseek", _long, {_uint, _long, _uint}, 3, 3},
    {"getpid", _long, {}, 0, 0},
    {"mount", _int, {_str, _str, _str, _ulong, _ptr}, 5, 5},
    {"oldumount", _int, {_str}, 1, 1},
    {"setuid16", _int, {_uint}, 1, 1},
    {"getuid16", _long, {}, 0, 0},
    {"stime", _int, {_ptr}, 1, 1},
    {"ptrace", _long, {_long, _long, _ulong, _ulong}, 4, 4},
    {"alarm", _uint, {_uint}, 1, 1},
    {"fstat", _int, {_uint, _ptr}, 2, 1},
    {"pause", _long, {}, 0, 0},
    {"utime", _int, {_str, _ptr}, 2, 2},
    {NULL, _void, {}, 0, 0},
    {NULL, _void, {}, 0, 0},
    {"access", _int, {_str, _int}, 2, 2},
    {"nice", _int, {_int}, 1, 1},
    {NULL, _void, {}, 0, 0},
    {"sync", _long, {}, 0, 0},
    {"kill", _int, {_int, _int}, 2, 2},
    {"rename", _int, {_str, _str}, 2, 2},
    {"mkdir", _int, {_str, _uint}, 2, 2},
    {"rmdir", _int, {_str}, 1, 1},
    {"dup", _int, {_uint}, 1, 1},
    {"pipe", _int, {_ptr}, 1, 1},
    {"times", _ulong, {_ptr}, 1, 0},
    {NULL, _void, {}, 0, 0},
    {"brk", _ptr, {_ptr}, 1, 1},
    {"setgid16", _int, {_uint}, 1, 1},
    {"getgid16", _long, {}, 0, 0},
    {"signal", _ptr, {_int, _ptr}, 2, 2},
    {"geteuid16", _long, {}, 0, 0},
    {"getegid", _long, {}, 0, 0},
    {"acct", _int, {_str}, 1, 1},
    {"umount", _int, {_str}, 1, 1},
    {NULL, _void, {}, 0, 0},
    {"ioctl", _int, {_uint, _uint, _ulong}, 3, 3},
    {"fcntl", _int, {_uint, _uint, _ulong}, 3, 3},
    {NULL, _void, {}, 0, 0},
    {"setpgid", _int, {_int, _int}, 2, 2},
    {NULL, _void, {}, 0, 0},
    {"olduname", _int, {_ptr}, 1, 1},
    {"umask", _long, {_int}, 1, 1},
    {"chroot", _int, {_str}, 1, 1},
    {"ustat", _int, {_uint, _ptr}, 2, 1},
    {"dup2", _int, {_uint, _uint}, 2, 2},
    {"getppid", _long, {}, 0, 0},
    {"getpgrp", _int, {}, 0, 0},
    {"setsid", _long, {}, 0, 0},
    {"sigaction", _int, {_int, _ptr, _ptr}, 3, 3},
    {"sgetmask", _long, {}, 0, 0},
    {"ssetmask", _long, {_int}, 1, 1},
    {"setreuid16", _int, {_uint, _uint}, 2, 2},
    {"setregid16", _int, {_uint, _uint}, 2, 2},
    {"sigsuspend", _int, {_ptr}, 1, 1},
    {"sigpending", _int, {_ptr}, 1, 1},
    {"sethostname", _int, {_str, _int}, 2, 2},
    {"setrlimit", _long, {_uint, _ptr}, 2, 2},
    {"old_getrlimit", _long, {_uint, _ptr}, 2, 2},
    {"getrusage", _int, {_int, _ptr}, 2, 1},
    {"gettimeofday", _int, {_ptr, _ptr}, 2, 1},
    {"settimeofday", _int, {_ptr, _ptr}, 2, 2},
    {"getgroups16", _int, {_int, _ptr}, 2, 1},
    {"setgroups16", _int, {_int, _ptr}, 2, 2},
    {"old_select", _int, {_ptr}, 1, 1},
    {"symlink", _int, {_str, _str}, 2, 2},
    {"lstat", _int, {_str, _ptr}, 2, 1},
    {"readlink", _long, {_str, _str, _int}, 3, 1},
    {"uselib", _int, {_str}, 1, 1},
    {"swapon", _int, {_str, _int}, 2, 2},
    {"reboot", _int, {_int, _int, _uint, _ptr}, 4, 4},
    {"old_readdir", _int, {_uint, _ptr, _uint}, 3, 3},
    {"old_mmap", _ptr, {_ptr}, 1, 1},
    {"munmap", _int, {_ulong, _ulong}, 2, 2},
    {"truncate", _int, {_str, _long}, 2, 2},
    {"ftruncate", _int, {_uint, _ulong}, 2, 2},
    {"fchmod", _int, {_uint, _uint}, 2, 2},
    {"fchown16", _int, {_uint, _uint, _uint}, 3, 3},
    {"getpriority", _int, {_int, _int}, 2, 2},
    {"setpriority", _int, {_int, _int, _int}, 3, 3},
    {NULL, _void, {}, 0, 0},
    {"statfs", _int, {_str, _ptr}, 2, 1},
    {"fstatfs", _int, {_uint, _ptr}, 2, 1},
    {"ioperm", _int, {_ulong, _ulong, _int}, 3, 3},
    {"socketcall", _int, {_int, _ulong}, 2, 2},
    {"syslog", _int, {_int, _str, _int}, 3, 3},
    {"setitimer", _int, {_int, _ptr, _ptr}, 3, 2},
    {"getitimer", _int, {_int, _ptr}, 2, 1},
    {"newstat", _long, {_str, _ptr}, 2, 2},
    {"newlstat", _long, {_str, _ptr}, 2, 2},
    {"newfstat", _long, {_uint, _ptr}, 2, 2},
    {"uname", _int, {_ptr}, 1, 0},
    {"iopl", _int, {_uint}, 1, 1},
    {"vhangup", _long, {}, 0, 0},
    {NULL, _void, {}, 0, 0},
    {"vm86old", _int, {_ptr}, 1, 1},
    {"wait4", _int, {_int, _ptr, _int, _ptr}, 4, 1},
    {"swapoff", _int, {_str}, 1, 1},
    {"sysinfo", _long, {_ptr}, 1, 0},
    {"ipc", _int, {_uint, _int, _int, _int, _ptr, _long}, 6, 6},
    {"fsync", _int, {_uint}, 1, 1},
    {"sigreturn", _int, {}, 0, 0},
    {"clone", _int, {_ulong, _ulong, _ptr, _ptr, _int}, 5, 5},
    {"setdomainname", _long, {_str, _int}, 2, 2},
    {"newuname", _int, {_ptr}, 1, 1},
    {"modify_ldt", _int, {_int, _ptr, _ulong}, 3, 1},
    {"adjtimex", _int, {_ptr}, 1, 1},
    {"mprotect", _int, {_ulong, _ulong, _ulong}, 3, 3},
    {"sigprocmask", _long, {_int, _ptr, _ptr}, 3, 3},
    {NULL, _void, {}, 0, 0},
    {"init_module", _int, {_ptr, _ulong, _str}, 3, 3},
    {"delete_module", _int, {_str, _uint}, 2, 2},
    {NULL, _void, {}, 0, 0},
    {"quotactl", _int, {_uint, _str, _uint, _ptr}, 4, 4},
    {"getpgid", _int, {_int}, 1, 1},
    {"fchdir", _int, {_uint}, 1, 1},
    {"bdflush", _int, {_int, _long}, 2, 2},
    {"sysfs", _int, {_int, _ulong, _ulong}, 3, 3},
    {"personality", _int, {_uint}, 1, 1},
    {NULL, _void, {}, 0, 0},
    {"setfsuid16", _int, {_uint}, 1, 1},
    {"setfsgid16", _int, {_uint}, 1, 1},
    {"llseek", _int, {_uint, _ulong, _ulong, _ptr, _uint}, 5, 5},
    {"getdents", _int, {_uint, _ptr, _uint}, 3, 1},
    {"select", _int, {_int, _ptr, _ptr, _ptr, _ptr}, 5, 5},
    {"flock", _int, {_uint, _uint}, 2, 2},
    {"msync", _int, {_ulong, _ulong, _int}, 3, 3},
    {"readv", _long, {_ulong, _ptr, _ulong}, 3, 1},
    {"writev", _long, {_ulong, _ptr, _ulong}, 3, 3},
    {"getsid", _int, {_int}, 1, 1},
    {"fdatasync", _int, {_uint}, 1, 1},
    {"sysctl", _int, {_ptr}, 1, 1},
    {"mlock", _int, {_ulong, _ulong}, 2, 2},
    {"munlock", _int, {_ulong, _ulong}, 2, 2},
    {"mlockall", _int, {_int}, 1, 1},
    {"munlockall", _long, {}, 0, 0},
    {"sched_setparam", _int, {_int, _ptr}, 2, 2},
    {"sched_getparam", _int, {_int, _ptr}, 2, 1},
    {"sched_setscheduler", _int, {_int, _int, _ptr}, 3, 3},
    {"sched_getscheduler", _int, {_int}, 1, 1},
    {"sched_yield", _long, {}, 0, 0},
    {"sched_get_priority_max", _int, {_int}, 1, 1},
    {"sched_get_priority_min", _int, {_int}, 1, 1},
    {"sched_rr_get_interval", _int, {_int, _ptr}, 2, 1},
    {"nanosleep", _int, {_ptr, _ptr}, 2, 1},
    {"mremap", _ptr, {_ulong}, 1, 1},
    {"setresuid", _int, {_uint, _uint, _uint}, 3, 3},
    {"getresuid", _int, {_ptr, _ptr, _ptr}, 3, 3},
    {"vm86", _int, {_ulong, _ulong}, 2, 2},
    {NULL, _void, {}, 0, 0},
    {"poll", _int, {_ptr, _uint, _int}, 3, 3},
    {NULL, _void, {}, 0, 0},
    {"setresgid16", _int, {_uint, _uint, _uint}, 3, 3},
    {"getresgid16", _int, {_ptr, _ptr, _ptr}, 3, 3},
    {"prctl", _int, {_int, _ulong, _ulong, _ulong, _ulong}, 5, 5},
    {"rt_sigreturn", _long, {}, 0, 0},
    {"rt_sigaction", _long, {_int, _ptr, _ptr, _ulong}, 4, 2},
    {"rt_sigprocmask", _long, {_int, _ptr, _ptr, _ulong}, 4, 4},
    {"rt_sigpending", _long, {_ptr, _ulong}, 2, 2},
    {"rt_sigtimedwait", _long, {_ptr, _ptr, _ptr, _ulong}, 4, 4},
    {"rt_sigqueueinfo", _int, {_int, _int, _ptr}, 3, 2},
    {"rt_sigsuspend", _long, {_ptr, _ulong}, 2, 2},
    {"pread64", _long, {_uint, _str, _ulong, _long}, 4, 1},
    {"pwrite64", _long, {_uint, _str, _ulong, _long}, 4, 4},
    {"chown16", _int, {_str, _uint, _uint}, 3, 3},
    {"getcwd", _long, {_str, _ulong}, 2, 2},
    {"capget", _int, {_ptr, _ptr}, 2, 0},
    {"capset", _int, {_ptr, _ptr}, 2, 2},
    {"sigaltstack", _int, {_ptr, _ptr}, 2, 0},
    {"sendfile", _long, {_int, _int, _ptr, _ulong}, 4, 4},
    {NULL, _void, {}, 0, 0},
    {NULL, _void, {}, 0, 0},
    {"vfork", _long, {}, 0, 0},
    {"getrlimit", _long, {_uint, _ptr}, 2, 1},
    {"mmap_pgoff", _ulong, {_ptr, _ulong, _ulong, _ulong, _ulong, _ulong}, 6, 6},
    {"truncate16", _int, {_str, _long}, 2, 2},
    {"ftruncate16", _int, {_uint, _ulong}, 2, 2},
    {"stat16", _int, {_str, _ptr}, 2, 2},
    {"fstat16", _int, {_uint, _ptr}, 2, 2},
    {"lstat16", _int, {_str, _ptr}, 2, 2},
    {"lchown", _int, {_str, _uint, _uint}, 3, 3},
    {"getuid", _long, {}, 0, 0},
    {"getgid", _long, {}, 0, 0},
    {"geteuid", _long, {}, 0, 0},
    {"getegid", _long, {}, 0, 0},
    {"setreuid", _int, {_uint, _uint}, 2, 2},
    {"setregid", _int, {_uint, _uint}, 2, 2},
    {"getgroups", _int, {_int, _ptr}, 2, 1},
    {"setgroups", _int, {_int, _ptr}, 2, 2},
    {"fchown", _int, {_uint, _uint, _uint}, 3, 3},
    {"setresuid", _int, {_uint, _uint, _uint}, 3, 3},
    {"getresuid", _int, {_ptr, _ptr, _ptr}, 3, 0},
    {"setresgid", _int, {_uint, _uint, _uint}, 3, 3},
    {"getresgid", _int, {_ptr, _ptr, _ptr}, 3, 0},
    {"chown", _int, {_str, _uint, _uint}, 3, 3},
    {"setuid", _int, {_uint}, 1, 1},
    {"setgid", _int, {_uint}, 1, 1},
    {"setfsuid", _int, {_uint}, 1, 1},
    {"setfsgid", _int, {_uint}, 1, 1},
    {"pivot_root", _int, {_str, _str}, 2, 2},
    {"mincore", _int, {_ulong, _ulong, _str}, 3, 3},
    {"madvise", _long, {_ulong, _ulong, _int}, 3, 3},
    {"getdents64", _long, {_uint, _ptr, _uint}, 3, 1},
    {"fcntl64", _int, {_uint, _uint, _ulong}, 3, 3},
    {NULL, _void, {}, 0, 0},
    {NULL, _void, {}, 0, 0},
    {"gettid", _long, {}, 0, 0},
    {"readahead", _long, {_int, _long, _ulong}, 3, 3},
    {"setxattr", _long, {_str, _str, _ptr, _ulong, _int}, 5, 5},
    {"lsetxattr", _long, {_str, _str, _ptr, _ulong, _int}, 5, 5},
    {"fsetxattr", _long, {_int, _str, _ptr, _ulong, _int}, 5, 5},
    {"getxattr", _long, {_str, _str, _ptr, _ulong}, 4, 2},
    {"lgetxattr", _long, {_str, _str, _ptr, _ulong}, 4, 2},
    {"fgetxattr", _long, {_int, _str, _ptr, _ulong}, 4, 2},
    {"listxattr", _long, {_str, _str, _ulong}, 3, 1},
    {"llistxattr", _long, {_str, _str, _ulong}, 3, 1},
    {"flistxattr", _long, {_int, _str, _ulong}, 3, 1},
    {"removexattr", _long, {_str, _str}, 2, 2},
    {"lremovexattr", _long, {_str, _str}, 2, 2},
    {"fremovexattr", _long, {_int, _str}, 2, 2},
    {"tkill", _int, {_int, _int}, 2, 2},
    {"sendfile64", _long, {_int, _int, _ptr, _ulong}, 4, 4},
    {"futex", _int, {_ptr, _int, _uint, _ptr, _ptr, _uint}, 6, 6},
    {"sched_setaffinity", _int, {_int, _uint, _ptr}, 3, 3},
    {"sched_getaffinity", _int, {_int, _uint, _ptr}, 3, 2},
    {"set_thread_area", _int, {_ptr}, 1, 1},
    {"get_thread_area", _int, {_ptr}, 1, 0},
    {"io_setup", _int, {_uint, _ptr}, 2, 1},
    {"io_destroy", _int, {_ulong}, 1, 1},
    {"io_getevents", _int, {_ulong, _long, _long, _ptr, _ptr}, 5, 5},
    {"io_submit", _int, {_ulong, _long, _ptr}, 3, 2},
    {"io_cancel", _int, {_ulong, _ptr, _ptr}, 3, 2},
    {"fadvise64", _long, {_int, _long, _ulong, _int}, 4, 4},
    {NULL, _void, {}, 0, 0},
    {"exit_group", _void, {_int}, 1, 1},
    {"lookup_dcookie", _int, {_ulong, _str, _ulong}, 3, 1},
    {"epoll_create", _int, {_int}, 1, 1},
    {"epoll_ctl", _int, {_int, _int, _int, _ptr}, 4, 4},
    {"epoll_wait", _int, {_int, _ptr, _int, _int}, 4, 4},
    {"remap_file_pages", _int, {_ulong, _ulong, _ulong, _ulong, _ulong}, 5, 5},
    {"set_tid_address", _long, {_ptr}, 1, 1},
    {"timer_create", _int, {_int, _ptr, _ptr}, 3, 3},
    {"timer_settime", _int, {_ulong, _int, _ptr, _ptr}, 4, 4},
    {"timer_gettime", _int, {_ulong, _ptr}, 2, 1},
    {"timer_getoverrun", _int, {_ulong}, 1, 1},
    {"timer_delete", _int, {_ulong}, 1, 1},
    {"clock_settime", _int, {_int, _ptr}, 2, 2},
    {"clock_gettime", _int, {_int, _ptr}, 2, 1},
    {"clock_getres", _int, {_int, _ptr}, 2, 1},
    {"clock_nanosleep", _int, {_int, _int, _ptr, _ptr}, 4, 3},
    {"statfs64", _int, {_str, _ulong, _ptr}, 3, 2},
    {"fstatfs64", _int, {_uint, _ulong, _ptr}, 3, 2},
    {"tgkill", _int, {_int, _int, _int}, 3, 3},
    {"utimes", _int, {_str, _ptr}, 2, 2},
    {"fadvise64_64", _long, {_int, _long, _ulong, _int}, 4, 4},
    {NULL, _void, {}, 0, 0},
    {"mbind", _int, {_ulong, _ulong, _ulong, _ptr, _ulong, _uint}, 6, 6},
    {"get_mempolicy", _int, {_ptr, _ptr, _ulong, _ulong, _ulong}, 5, 3},
    {"set_mempolicy", _long, {_int, _ptr, _ulong}, 3, 3},
    {"mq_open", _long, {_str, _int, _uint, _ptr}, 4, 4},
    {"mq_unlink", _long, {_str}, 1, 1},
    {"mq_timedsend", _long, {_ulong, _str, _ulong, _uint, _ptr}, 5, 5},
    {"mq_timedreceive", _long, {_ulong, _str, _ulong, _ptr, _ptr}, 5, 1},
    {"mq_notify", _long, {_ulong, _ptr}, 2, 2},
    {"mq_getsetattr", _int, {_ulong, _ptr, _ptr}, 3, 2},
    {"kexec_load", _long, {_ulong, _ulong, _ptr, _ulong}, 4, 2},
    {"waitid", _int, {_int, _int, _ptr, _int, _ptr}, 5, 5},
    {NULL, _void, {}, 0, 0},
    {"add_key", _int, {_str, _str, _ptr, _ulong, _int}, 5, 5},
    {"request_key", _int, {_str, _str, _str, _int}, 4, 4},
    {"keyctl", _long, {_int, _ulong, _ulong, _ulong, _ulong}, 5, 5},
    {"ioprio_set", _int, {_int, _int, _int}, 3, 3},
    {"ioprio_get", _int, {_int, _int}, 2, 2},
    {"inotify_init", _long, {}, 0, 0},
    {"inotify_add_watch", _int, {_int, _str, _uint}, 3, 3},
    {"inotify_rm_watch", _int, {_int, _int}, 2, 2},
    {"migrate_pages", _long, {_int, _ulong, _ptr, _ptr}, 4, 4},
    {"openat", _int, {_int, _str, _int}, 3, 3},
    {"mkdirat", _int, {_int, _str, _uint}, 3, 3},
    {"mknodat", _int, {_int, _str, _uint, _uint}, 4, 4},
    {"fchownat", _int, {_int, _str, _uint, _uint, _int}, 5, 5},
    {"futimesat", _int, {_int, _str, _ptr}, 3, 3},
    {"fstatat64", _long, {_int, _str, _ptr, _int}, 4, 4},
    {"unlinkat", _int, {_int, _str, _int}, 3, 3},
    {"renameat", _int, {_int, _str, _int, _str}, 4, 4},
    {"linkat", _int, {_int, _str, _int, _str, _int}, 5, 5},
    {"symlinkat", _int, {_str, _int, _str}, 3, 3},
    {"readlinkat", _int, {_int, _str, _str, _int}, 4, 2},
    {"fchmodat", _int, {_int, _str, _uint}, 3, 3},
    {"faccessat", _int, {_int, _str, _int}, 3, 3},
    {"pselect6", _long, {_int, _ptr, _ptr, _ptr, _ptr, _ptr}, 6, 6},
    {"ppoll", _int, {_ptr, _uint, _ptr, _ptr, _ulong}, 5, 5},
    {"unshare", _int, {_ulong}, 1, 1},
    {"set_robust_list", _long, {_ptr, _ulong}, 2, 2},
    {"get_robust_list", _long, {_int, _ptr, _ptr}, 3, 1},
    {"splice", _long, {_int, _ptr, _int, _ptr, _ulong, _uint}, 6, 3},
    {"sync_file_range", _int, {_int, _long, _long, _uint}, 4, 4},
    {"tee", _long, {_int, _int, _ulong, _uint}, 4, 4},
    {"vmsplice", _long, {_int, _ptr, _ulong, _uint}, 4, 1},
    {"move_pages", _long, {_int, _ulong, _ptr, _ptr, _ptr, _int}, 6, 6},
    {"getcpu", _int, {_uint, _uint, _ptr}, 3, 2},
    {"epoll_pwait", _int, {_int, _ptr, _int, _int, _ptr, _ulong}, 6, 6},
    {"utimensat", _int, {_int, _str, _ptr, _int}, 4, 4},
    {"signalfd", _int, {_int, _ptr, _ulong}, 3, 3},
    {"timerfd_create", _int, {_int, _int}, 2, 2},
    {"eventfd", _int, {_uint}, 1, 1},
    {"fallocate", _int, {_int, _int, _long, _long}, 4, 4},
    {"timerfd_settime", _int, {_int, _int, _ptr, _ptr}, 4, 4},
    {"timerfd_gettime", _int, {_int, _ptr}, 2, 1},
    {"signalfd4", _long, {_int, _ptr, _ulong, _int}, 4, 4},
    {"eventfd2", _long, {_uint, _int}, 2, 2},
    {"epoll_create1", _int, {_int}, 1, 1},
    {"dup3", _int, {_uint, _uint, _int}, 3, 3},
    {"pipe2", _int, {_ptr, _int}, 2, 2},
    {"inotify_init1", _int, {_int}, 1, 1},
    {"preadv", _long, {_ulong, _ptr, _ulong, _ulong, _ulong}, 5, 1},
    {"pwritev", _long, {_ulong, _ptr, _ulong, _ulong, _ulong}, 5, 5},
    {"rt_tgsigqueueinfo", _int, {_int, _int, _int, _ptr}, 4, 4},
    {"perf_event_open", _int, {_ptr, _int, _int, _int, _ulong}, 5, 5},
    {"recvmmsg", _int, {_int, _ptr, _uint, _uint, _ptr}, 5, 1},
    {"fanotify_init", _long, {_uint, _uint}, 2, 2},
    {"fanotify_mark", _long, {_int, _uint, _ulong, _int, _str}, 5, 5},
    {"prlimit64", _long, {_int, _uint, _ptr, _ptr}, 4, 2},
    {"name_to_handle_at", _long, {_int, _str, _ptr, _ptr, _int}, 5, 3},
    {"open_by_handle_at", _long, {_int, _ptr, _int}, 3, 3},
    {"clock_adjtime", _long, {_int, _ptr}, 2, 1},
    {"syncfs", _int, {_int}, 1, 1},
    {"sendmmsg", _int, {_int, _ptr, _uint, _uint}, 4, 4},
    {"setns", _int, {_int, _int}, 2, 2},
    {"process_vm_readv", _long, {_int, _ptr, _ulong, _ptr, _ulong, _ulong}, 6, 1},
    {"process_vm_writev", _long, {_int, _ptr, _ulong, _ptr, _ulong, _ulong}, 6, 6},
    {"kcmp", _int, {_int, _int, _int, _ulong, _ulong}, 5, 5},
    {"finit_module", _int, {_int, _str, _int}, 3, 3},
    {"sched_setattr", _int, {_long, _ptr, _uint}, 3, 3},
    {"sched_getattr", _int, {_long, _ptr, _uint, _uint}, 4, 1},
    {"renameat2", _int, {_int, _str, _int, _str, _uint}, 5, 5},
    {"seccomp", _int, {_uint, _uint, _ptr}, 3, 3},
    {"getrandom", _long, {_ptr, _ulong, _uint}, 3, 0},
    {"memfd_create", _int, {_str, _uint}, 2, 2},
    {"bpf", _int, {_int, _ptr, _uint}, 3, 1},
    {"execveat", _int, {_int, _str, _str_arr, _str_arr, _int}, 5, 5},
    {"socket", _int, {_int, _int, _int}, 3, 3},
    {"socketpair", _int, {_int, _int, _int, _ptr}, 4, 4},
    {"bind", _int, {_int, _ptr, _int}, 3, 3},
    {"connect", _int, {_int, _ptr, _int}, 3, 3},
    {"listen", _int, {_int, _int}, 2, 2},
    {"accept4", _int, {_int, _ptr, _ptr, _int}, 4, 1},
    {"getsockopt", _int, {_int, _int, _int, _str, _ptr}, 5, 4},
    {"setsockopt", _int, {_int, _int, _int, _str, _int}, 5, 5},
    {"getsockname", _int, {_int, _ptr, _ptr}, 3, 1},
    {"getpeername", _int, {_int, _ptr, _ptr}, 3, 1},
    {"sendto", _long, {_int, _ptr, _ulong, _uint, _ptr, _int}, 6, 6},
    {"sendmsg", _long, {_int, _ptr, _uint}, 3, 3},
    {"recvfrom", _long, {_int, _ptr, _ulong, _uint, _ptr, _ptr}, 6, 1},
    {"recvmsg", _long, {_int, _ptr, _uint}, 3, 1},
    {"shutdown", _int, {_int, _int}, 2, 2},
    {"userfaultfd", _int, {_int}, 1, 1},
    {"membarrier", _int, {_int, _int}, 2, 2},
    {"mlock2", _int, {_ptr, _ulong, _int}, 3, 3},
    {"copy_file_range", _long, {_int, _ptr, _int, _ptr, _ulong, _uint}, 6, 1},
    {"preadv2", _long, {_int, _ptr, _int, _int, _int}, 5, 1},
    {"pwritev2", _long, {_int, _ptr, _int, _int, _int}, 5, 5},
    {"pkey_mprotect", _int, {_ptr, _long, _int, _int}, 4, 4},
    {"pkey_alloc", _int, {_uint, _uint}, 2, 2},
    {"pkey_free", _int, {_int}, 1, 1},
    {"statx", _int, {_int, _str, _int, _uint, _ptr}, 5, 4},
    {"arch_prctl", _int, {_ptr, _ulong}, 2, 2}
};
#endif  /* __x86_64__ */
