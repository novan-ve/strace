# Strace

Reimplementation of the strace command in C.

```bash
$ make
$ ./ft_strace /bin/pwd
execve("/bin/pwd", ["/bin/pwd"], 0x7ffdb9f8df40 /* 52 vars */) = 0
brk(NULL)                               = 0x55e9fec4b000
access("/etc/ld.so.preload", 4)         = -1 ENOENT (No such file or directory)
openat(-100, "/etc/ld.so.cache", 524288) = 3
fstat(3, 0x7ffe5c33c290)                = 0
mmap(NULL, 117081, 1, 2, 3, 0)          = 0x7f093c4b6000
close(3)                                = 0
openat(-100, "/lib/x86_64-linux-gnu/libc.so.6", 524288) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0@>\2\0\0\0\0\0"..., 832) = 832
fstat(3, 0x7ffe5c33c2e0)                = 0
mmap(NULL, 8192, 3, 34, -1, 0)          = 0x7f093c4b4000
mmap(NULL, 1918592, 1, 2050, 3, 0)      = 0x7f093c2df000
mmap(0x7f093c301000, 1417216, 5, 2066, 3, 139264) = 0x7f093c301000
mmap(0x7f093c45b000, 323584, 1, 2066, 3, 1556480) = 0x7f093c45b000
mmap(0x7f093c4aa000, 24576, 3, 2066, 3, 1875968) = 0x7f093c4aa000
mmap(0x7f093c4b0000, 13952, 3, 50, -1, 0) = 0x7f093c4b0000
close(3)                                = 0
arch_prctl(4098, 139677643003264)       = 0
mprotect(0x7f093c4aa000, 16384, 1)      = 0
mprotect(0x55e9fe074000, 4096, 1)       = 0
mprotect(0x7f093c4fd000, 4096, 1)       = 0
munmap(0x7f093c4b6000, 117081)          = 0
brk(NULL)                               = 0x55e9fec4b000
brk(0x55e9fec6c000)                     = 0x55e9fec6c000
openat(-100, "/usr/lib/locale/locale-archive", 524288) = 3
fstat(3, 0x7f093c4afaa0)                = 0
mmap(NULL, 3041456, 1, 2, 3, 0)         = 0x7f093bff8000
close(3)                                = 0
getcwd("", 4096)                        = 0
fstat(1, 0x7ffe5c33cf80)                = 0
write(1, "/home/user/strace\n", 18/home/user/strace
) = 30
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
```
