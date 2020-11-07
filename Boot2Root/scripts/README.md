# Boot2root

**Starring :**

mbenjell : https://github.com/MehdiBenjelloun<br/>
ilarbi : https://github.com/IsmaheneLarbi<br/>
rmarracc : https://github.com/0auBSQ<br/>
jergauth : https://github.com/jeremie-gauthier<br/>

## Liste des exploits

Les exploits sont des continuations de la Branche 0 ([web2ssh](0-Boot2SSH/README.md))

- [1# Intended route](1-IntendedRoute/README.md)
- [2# Dirty COW (Copy-on-Write)](2-DirtyCOW/README.md)
- [3# Shellcode variant](3-ShellcodeVariant/README.md)

## Infos additionnelles 

Searchsploit (exploitdb) track for kernel version (3.2) :
```
---------------------------------------------------------------------------------------------------------------- ---------------------------------
 Exploit Title                                                                                                  |  Path
---------------------------------------------------------------------------------------------------------------- ---------------------------------
Linux Kernel (Solaris 10 / < 5.10 138888-01) - Local Privilege Escalation                                       | solaris/local/15962.c
Linux Kernel 2.6.22 < 3.9 (x86/x64) - 'Dirty COW /proc/self/mem' Race Condition Privilege Escalation (SUID Meth | linux/local/40616.c
Linux Kernel 2.6.22 < 3.9 - 'Dirty COW /proc/self/mem' Race Condition Privilege Escalation (/etc/passwd Method) | linux/local/40847.cpp
Linux Kernel 2.6.22 < 3.9 - 'Dirty COW PTRACE_POKEDATA' Race Condition (Write Access Method)                    | linux/local/40838.c
Linux Kernel 2.6.22 < 3.9 - 'Dirty COW' 'PTRACE_POKEDATA' Race Condition Privilege Escalation (/etc/passwd Meth | linux/local/40839.c
Linux Kernel 2.6.22 < 3.9 - 'Dirty COW' /proc/self/mem Race Condition (Write Access Method)                     | linux/local/40611.c
Linux Kernel 2.6.39 < 3.2.2 (Gentoo / Ubuntu x86/x64) - 'Mempodipper' Local Privilege Escalation (1)            | linux/local/18411.c
Linux Kernel 2.6.39 < 3.2.2 (x86/x64) - 'Mempodipper' Local Privilege Escalation (2)                            | linux/local/35161.c
Linux Kernel 3.0 < 3.3.5 - 'CLONE_NEWUSER|CLONE_FS' Local Privilege Escalation                                  | linux/local/38390.c
Linux Kernel 3.14-rc1 < 3.15-rc4 (x64) - Raw Mode PTY Echo Race Condition Privilege Escalation                  | linux_x86-64/local/33516.c
Linux Kernel 3.2.0-23/3.5.0-23 (Ubuntu 12.04/12.04.1/12.04.2 x64) - 'perf_swevent_init' Local Privilege Escalat | linux_x86-64/local/33589.c
Linux Kernel 3.2.x - 'uname()' System Call Local Information Disclosure                                         | linux/local/37937.c
Linux Kernel 3.4 < 3.13.2 (Ubuntu 13.04/13.10 x64) - 'CONFIG_X86_X32=y' Local Privilege Escalation (3)          | linux_x86-64/local/31347.c
Linux Kernel 3.4 < 3.13.2 (Ubuntu 13.10) - 'CONFIG_X86_X32' Arbitrary Write (2)                                 | linux/local/31346.c
Linux Kernel 4.8.0 UDEV < 232 - Local Privilege Escalation                                                      | linux/local/41886.c
Linux Kernel < 3.16.1 - 'Remount FUSE' Local Privilege Escalation                                               | linux/local/34923.c
Linux Kernel < 3.16.39 (Debian 8 x64) - 'inotfiy' Local Privilege Escalation                                    | linux_x86-64/local/44302.c
Linux Kernel < 3.2.0-23 (Ubuntu 12.04 x64) - 'ptrace/sysret' Local Privilege Escalation                         | linux_x86-64/local/34134.c
Linux Kernel < 3.4.5 (Android 4.2.2/4.4 ARM) - Local Privilege Escalation                                       | arm/local/31574.c
Linux Kernel < 3.5.0-23 (Ubuntu 12.04.2 x64) - 'SOCK_DIAG' SMEP Bypass Local Privilege Escalation               | linux_x86-64/local/44299.c
Linux Kernel < 3.8.9 (x86-64) - 'perf_swevent_init' Local Privilege Escalation (2)                              | linux_x86-64/local/26131.c
Linux Kernel < 3.8.x - open-time Capability 'file_ns_capable()' Local Privilege Escalation                      | linux/local/25450.c
Linux kernel < 4.10.15 - Race Condition Privilege Escalation                                                    | linux/local/43345.c
Linux Kernel < 4.11.8 - 'mq_notify: double sock_put()' Local Privilege Escalation                               | linux/local/45553.c
Linux Kernel < 4.13.9 (Ubuntu 16.04 / Fedora 27) - Local Privilege Escalation                                   | linux/local/45010.c
Linux Kernel < 4.15.4 - 'show_floppy' KASLR Address Leak                                                        | linux/local/44325.c
Linux Kernel < 4.4.0-116 (Ubuntu 16.04.4) - Local Privilege Escalation                                          | linux/local/44298.c
Linux Kernel < 4.4.0-21 (Ubuntu 16.04 x64) - 'netfilter target_offset' Local Privilege Escalation               | linux_x86-64/local/44300.c
Linux Kernel < 4.4.0-83 / < 4.8.0-58 (Ubuntu 14.04/16.04) - Local Privilege Escalation (KASLR / SMEP)           | linux/local/43418.c
Linux Kernel < 4.4.0/ < 4.8.0 (Ubuntu 14.04/16.04 / Linux Mint 17/18 / Zorin) - Local Privilege Escalation (KAS | linux/local/47169.c
---------------------------------------------------------------------------------------------------------------- ---------------------------------
```
