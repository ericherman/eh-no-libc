/*
eh-no-libc - exploring coding without the standard library
Copyright (C) 2017 Eric Herman

This work is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later
version.

This work is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License (COPYING) along with this library; if not, see:

        https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
*/
#ifndef SYSCALLS_H
#define SYSCALLS_H

/*
cat ~/src/linux/arch/x86/entry/syscalls/syscall_64.tbl  | awk '/^[0-9]/ { nr=$1; abi=$2; name=$3; entry=$4; printf("#define SYS_%s_%s\t%d\t/: %s :/\n", name, abi, nr, entry); }' | sort | sed -e 's/_common//g' | sed -e 's/_64//g' | sed -e 's@:@*@g' >> src/linux-amd64/syscalls.h
*/

#define SYS__sysctl	156	/* sys_sysctl */
#define SYS_accept4	288	/* sys_accept4 */
#define SYS_accept	43	/* sys_accept */
#define SYS_access	21	/* sys_access */
#define SYS_acct	163	/* sys_acct */
#define SYS_add_key	248	/* sys_add_key */
#define SYS_adjtimex	159	/* sys_adjtimex */
#define SYS_afs_syscall	183	/*  */
#define SYS_alarm	37	/* sys_alarm */
#define SYS_arch_prctl	158	/* sys_arch_prctl */
#define SYS_bind	49	/* sys_bind */
#define SYS_bpf	321		/* sys_bpf */
#define SYS_brk	12		/* sys_brk */
#define SYS_capget	125	/* sys_capget */
#define SYS_capset	126	/* sys_capset */
#define SYS_chdir	80	/* sys_chdir */
#define SYS_chmod	90	/* sys_chmod */
#define SYS_chown	92	/* sys_chown */
#define SYS_chroot	161	/* sys_chroot */
#define SYS_clock_adjtime	305	/* sys_clock_adjtime */
#define SYS_clock_getres	229	/* sys_clock_getres */
#define SYS_clock_gettime	228	/* sys_clock_gettime */
#define SYS_clock_nanosleep	230	/* sys_clock_nanosleep */
#define SYS_clock_settime	227	/* sys_clock_settime */
#define SYS_clone	56	/* sys_clone/ptregs */
#define SYS_close	3	/* sys_close */
#define SYS_connect	42	/* sys_connect */
#define SYS_copy_file_range	326	/* sys_copy_file_range */
#define SYS_creat	85	/* sys_creat */
#define SYS_create_module	174	/*  */
#define SYS_delete_module	176	/* sys_delete_module */
#define SYS_dup2	33	/* sys_dup2 */
#define SYS_dup3	292	/* sys_dup3 */
#define SYS_dup	32		/* sys_dup */
#define SYS_epoll_create1	291	/* sys_epoll_create1 */
#define SYS_epoll_create	213	/* sys_epoll_create */
#define SYS_epoll_ctl	233	/* sys_epoll_ctl */
#define SYS_epoll_ctl_old	214	/*  */
#define SYS_epoll_pwait	281	/* sys_epoll_pwait */
#define SYS_epoll_wait	232	/* sys_epoll_wait */
#define SYS_epoll_wait_old	215	/*  */
#define SYS_eventfd2	290	/* sys_eventfd2 */
#define SYS_eventfd	284	/* sys_eventfd */
#define SYS_execve	59	/* sys_execve/ptregs */
#define SYS_execve_x32	520	/* compat_sys_execve/ptregs */
#define SYS_execveat	322	/* sys_execveat/ptregs */
#define SYS_execveat_x32	545	/* compat_sys_execveat/ptregs */
#define SYS_exit	60	/* sys_exit */
#define SYS_exit_group	231	/* sys_exit_group */
#define SYS_faccessat	269	/* sys_faccessat */
#define SYS_fadvise64	221	/* sys_fadvise64 */
#define SYS_fallocate	285	/* sys_fallocate */
#define SYS_fanotify_init	300	/* sys_fanotify_init */
#define SYS_fanotify_mark	301	/* sys_fanotify_mark */
#define SYS_fchdir	81	/* sys_fchdir */
#define SYS_fchmod	91	/* sys_fchmod */
#define SYS_fchmodat	268	/* sys_fchmodat */
#define SYS_fchown	93	/* sys_fchown */
#define SYS_fchownat	260	/* sys_fchownat */
#define SYS_fcntl	72	/* sys_fcntl */
#define SYS_fdatasync	75	/* sys_fdatasync */
#define SYS_fgetxattr	193	/* sys_fgetxattr */
#define SYS_finit_module	313	/* sys_finit_module */
#define SYS_flistxattr	196	/* sys_flistxattr */
#define SYS_flock	73	/* sys_flock */
#define SYS_fork	57	/* sys_fork/ptregs */
#define SYS_fremovexattr	199	/* sys_fremovexattr */
#define SYS_fsetxattr	190	/* sys_fsetxattr */
#define SYS_fstat	5	/* sys_newfstat */
#define SYS_fstatfs	138	/* sys_fstatfs */
#define SYS_fsync	74	/* sys_fsync */
#define SYS_ftruncate	77	/* sys_ftruncate */
#define SYS_futex	202	/* sys_futex */
#define SYS_futimesat	261	/* sys_futimesat */
#define SYS_get_kernel_syms	177	/*  */
#define SYS_get_mempolicy	239	/* sys_get_mempolicy */
#define SYS_get_robust_list	274	/* sys_get_robust_list */
#define SYS_get_robust_list_x32	531	/* compat_sys_get_robust_list */
#define SYS_get_thread_area	211	/*  */
#define SYS_getcpu	309	/* sys_getcpu */
#define SYS_getcwd	79	/* sys_getcwd */
#define SYS_getdents64	217	/* sys_getdents64 */
#define SYS_getdents	78	/* sys_getdents */
#define SYS_getegid	108	/* sys_getegid */
#define SYS_geteuid	107	/* sys_geteuid */
#define SYS_getgid	104	/* sys_getgid */
#define SYS_getgroups	115	/* sys_getgroups */
#define SYS_getitimer	36	/* sys_getitimer */
#define SYS_getpeername	52	/* sys_getpeername */
#define SYS_getpgid	121	/* sys_getpgid */
#define SYS_getpgrp	111	/* sys_getpgrp */
#define SYS_getpid	39	/* sys_getpid */
#define SYS_getpmsg	181	/*  */
#define SYS_getppid	110	/* sys_getppid */
#define SYS_getpriority	140	/* sys_getpriority */
#define SYS_getrandom	318	/* sys_getrandom */
#define SYS_getresgid	120	/* sys_getresgid */
#define SYS_getresuid	118	/* sys_getresuid */
#define SYS_getrlimit	97	/* sys_getrlimit */
#define SYS_getrusage	98	/* sys_getrusage */
#define SYS_getsid	124	/* sys_getsid */
#define SYS_getsockname	51	/* sys_getsockname */
#define SYS_getsockopt	55	/* sys_getsockopt */
#define SYS_getsockopt_x32	542	/* compat_sys_getsockopt */
#define SYS_gettid	186	/* sys_gettid */
#define SYS_gettimeofday	96	/* sys_gettimeofday */
#define SYS_getuid	102	/* sys_getuid */
#define SYS_getxattr	191	/* sys_getxattr */
#define SYS_init_module	175	/* sys_init_module */
#define SYS_inotify_add_watch	254	/* sys_inotify_add_watch */
#define SYS_inotify_init1	294	/* sys_inotify_init1 */
#define SYS_inotify_init	253	/* sys_inotify_init */
#define SYS_inotify_rm_watch	255	/* sys_inotify_rm_watch */
#define SYS_io_cancel	210	/* sys_io_cancel */
#define SYS_io_destroy	207	/* sys_io_destroy */
#define SYS_io_getevents	208	/* sys_io_getevents */
#define SYS_io_setup	206	/* sys_io_setup */
#define SYS_io_setup_x32	543	/* compat_sys_io_setup */
#define SYS_io_submit	209	/* sys_io_submit */
#define SYS_io_submit_x32	544	/* compat_sys_io_submit */
#define SYS_ioctl	16	/* sys_ioctl */
#define SYS_ioctl_x32	514	/* compat_sys_ioctl */
#define SYS_ioperm	173	/* sys_ioperm */
#define SYS_iopl	172	/* sys_iopl/ptregs */
#define SYS_ioprio_get	252	/* sys_ioprio_get */
#define SYS_ioprio_set	251	/* sys_ioprio_set */
#define SYS_kcmp	312	/* sys_kcmp */
#define SYS_kexec_file_load	320	/* sys_kexec_file_load */
#define SYS_kexec_load	246	/* sys_kexec_load */
#define SYS_kexec_load_x32	528	/* compat_sys_kexec_load */
#define SYS_keyctl	250	/* sys_keyctl */
#define SYS_kill	62	/* sys_kill */
#define SYS_lchown	94	/* sys_lchown */
#define SYS_lgetxattr	192	/* sys_lgetxattr */
#define SYS_link	86	/* sys_link */
#define SYS_linkat	265	/* sys_linkat */
#define SYS_listen	50	/* sys_listen */
#define SYS_listxattr	194	/* sys_listxattr */
#define SYS_llistxattr	195	/* sys_llistxattr */
#define SYS_lookup_dcookie	212	/* sys_lookup_dcookie */
#define SYS_lremovexattr	198	/* sys_lremovexattr */
#define SYS_lseek	8	/* sys_lseek */
#define SYS_lsetxattr	189	/* sys_lsetxattr */
#define SYS_lstat	6	/* sys_newlstat */
#define SYS_madvise	28	/* sys_madvise */
#define SYS_mbind	237	/* sys_mbind */
#define SYS_membarrier	324	/* sys_membarrier */
#define SYS_memfd_create	319	/* sys_memfd_create */
#define SYS_migrate_pages	256	/* sys_migrate_pages */
#define SYS_mincore	27	/* sys_mincore */
#define SYS_mkdir	83	/* sys_mkdir */
#define SYS_mkdirat	258	/* sys_mkdirat */
#define SYS_mknod	133	/* sys_mknod */
#define SYS_mknodat	259	/* sys_mknodat */
#define SYS_mlock2	325	/* sys_mlock2 */
#define SYS_mlock	149	/* sys_mlock */
#define SYS_mlockall	151	/* sys_mlockall */
#define SYS_mmap	9	/* sys_mmap */
#define SYS_modify_ldt	154	/* sys_modify_ldt */
#define SYS_mount	165	/* sys_mount */
#define SYS_move_pages	279	/* sys_move_pages */
#define SYS_move_pages_x32	533	/* compat_sys_move_pages */
#define SYS_mprotect	10	/* sys_mprotect */
#define SYS_mq_getsetattr	245	/* sys_mq_getsetattr */
#define SYS_mq_notify	244	/* sys_mq_notify */
#define SYS_mq_notify_x32	527	/* compat_sys_mq_notify */
#define SYS_mq_open	240	/* sys_mq_open */
#define SYS_mq_timedreceive	243	/* sys_mq_timedreceive */
#define SYS_mq_timedsend	242	/* sys_mq_timedsend */
#define SYS_mq_unlink	241	/* sys_mq_unlink */
#define SYS_mremap	25	/* sys_mremap */
#define SYS_msgctl	71	/* sys_msgctl */
#define SYS_msgget	68	/* sys_msgget */
#define SYS_msgrcv	70	/* sys_msgrcv */
#define SYS_msgsnd	69	/* sys_msgsnd */
#define SYS_msync	26	/* sys_msync */
#define SYS_munlock	150	/* sys_munlock */
#define SYS_munlockall	152	/* sys_munlockall */
#define SYS_munmap	11	/* sys_munmap */
#define SYS_name_to_handle_at	303	/* sys_name_to_handle_at */
#define SYS_nanosleep	35	/* sys_nanosleep */
#define SYS_newfstatat	262	/* sys_newfstatat */
#define SYS_nfsservctl	180	/*  */
#define SYS_open_by_handle_at	304	/* sys_open_by_handle_at */
#define SYS_open	2	/* sys_open */
#define SYS_openat	257	/* sys_openat */
#define SYS_pause	34	/* sys_pause */
#define SYS_perf_event_open	298	/* sys_perf_event_open */
#define SYS_personality	135	/* sys_personality */
#define SYS_pipe2	293	/* sys_pipe2 */
#define SYS_pipe	22	/* sys_pipe */
#define SYS_pivot_root	155	/* sys_pivot_root */
#define SYS_pkey_alloc	330	/* sys_pkey_alloc */
#define SYS_pkey_free	331	/* sys_pkey_free */
#define SYS_pkey_mprotect	329	/* sys_pkey_mprotect */
#define SYS_poll	7	/* sys_poll */
#define SYS_ppoll	271	/* sys_ppoll */
#define SYS_prctl	157	/* sys_prctl */
#define SYS_pread64	17	/* sys_pread64 */
#define SYS_preadv2	327	/* sys_preadv2 */
#define SYS_preadv2_x32	546	/* compat_sys_preadv64v2 */
#define SYS_preadv	295	/* sys_preadv */
#define SYS_preadv_x32	534	/* compat_sys_preadv64 */
#define SYS_prlimit64	302	/* sys_prlimit64 */
#define SYS_process_vm_readv	310	/* sys_process_vm_readv */
#define SYS_process_vm_readv_x32	539	/* compat_sys_process_vm_readv */
#define SYS_process_vm_writev	311	/* sys_process_vm_writev */
#define SYS_process_vm_writev_x32	540	/* compat_sys_process_vm_writev */
#define SYS_pselect6	270	/* sys_pselect6 */
#define SYS_ptrace	101	/* sys_ptrace */
#define SYS_ptrace_x32	521	/* compat_sys_ptrace */
#define SYS_putpmsg	182	/*  */
#define SYS_pwrite64	18	/* sys_pwrite64 */
#define SYS_pwritev2	328	/* sys_pwritev2 */
#define SYS_pwritev2_x32	547	/* compat_sys_pwritev64v2 */
#define SYS_pwritev	296	/* sys_pwritev */
#define SYS_pwritev_x32	535	/* compat_sys_pwritev64 */
#define SYS_query_module	178	/*  */
#define SYS_quotactl	179	/* sys_quotactl */
#define SYS_read	0	/* sys_read */
#define SYS_readahead	187	/* sys_readahead */
#define SYS_readlink	89	/* sys_readlink */
#define SYS_readlinkat	267	/* sys_readlinkat */
#define SYS_readv	19	/* sys_readv */
#define SYS_readv_x32	515	/* compat_sys_readv */
#define SYS_reboot	169	/* sys_reboot */
#define SYS_recvfrom	45	/* sys_recvfrom */
#define SYS_recvfrom_x32	517	/* compat_sys_recvfrom */
#define SYS_recvmmsg	299	/* sys_recvmmsg */
#define SYS_recvmmsg_x32	537	/* compat_sys_recvmmsg */
#define SYS_recvmsg	47	/* sys_recvmsg */
#define SYS_recvmsg_x32	519	/* compat_sys_recvmsg */
#define SYS_remap_file_pages	216	/* sys_remap_file_pages */
#define SYS_removexattr	197	/* sys_removexattr */
#define SYS_rename	82	/* sys_rename */
#define SYS_renameat2	316	/* sys_renameat2 */
#define SYS_renameat	264	/* sys_renameat */
#define SYS_request_key	249	/* sys_request_key */
#define SYS_restart_syscall	219	/* sys_restart_syscall */
#define SYS_rmdir	84	/* sys_rmdir */
#define SYS_rt_sigaction	13	/* sys_rt_sigaction */
#define SYS_rt_sigaction_x32	512	/* compat_sys_rt_sigaction */
#define SYS_rt_sigpending	127	/* sys_rt_sigpending */
#define SYS_rt_sigpending_x32	522	/* compat_sys_rt_sigpending */
#define SYS_rt_sigprocmask	14	/* sys_rt_sigprocmask */
#define SYS_rt_sigqueueinfo	129	/* sys_rt_sigqueueinfo */
#define SYS_rt_sigqueueinfo_x32	524	/* compat_sys_rt_sigqueueinfo */
#define SYS_rt_sigreturn	15	/* sys_rt_sigreturn/ptregs */
#define SYS_rt_sigreturn_x32	513	/* sys32_x32_rt_sigreturn */
#define SYS_rt_sigsuspend	130	/* sys_rt_sigsuspend */
#define SYS_rt_sigtimedwait	128	/* sys_rt_sigtimedwait */
#define SYS_rt_sigtimedwait_x32	523	/* compat_sys_rt_sigtimedwait */
#define SYS_rt_tgsigqueueinfo	297	/* sys_rt_tgsigqueueinfo */
#define SYS_rt_tgsigqueueinfo_x32	536	/* compat_sys_rt_tgsigqueueinfo */
#define SYS_sched_get_priority_max	146	/* sys_sched_get_priority_max */
#define SYS_sched_get_priority_min	147	/* sys_sched_get_priority_min */
#define SYS_sched_getaffinity	204	/* sys_sched_getaffinity */
#define SYS_sched_getattr	315	/* sys_sched_getattr */
#define SYS_sched_getparam	143	/* sys_sched_getparam */
#define SYS_sched_getscheduler	145	/* sys_sched_getscheduler */
#define SYS_sched_rr_get_interval	148	/* sys_sched_rr_get_interval */
#define SYS_sched_setaffinity	203	/* sys_sched_setaffinity */
#define SYS_sched_setattr	314	/* sys_sched_setattr */
#define SYS_sched_setparam	142	/* sys_sched_setparam */
#define SYS_sched_setscheduler	144	/* sys_sched_setscheduler */
#define SYS_sched_yield	24	/* sys_sched_yield */
#define SYS_seccomp	317	/* sys_seccomp */
#define SYS_security	185	/*  */
#define SYS_select	23	/* sys_select */
#define SYS_semctl	66	/* sys_semctl */
#define SYS_semget	64	/* sys_semget */
#define SYS_semop	65	/* sys_semop */
#define SYS_semtimedop	220	/* sys_semtimedop */
#define SYS_sendfile	40	/* sys_sendfile64 */
#define SYS_sendmmsg	307	/* sys_sendmmsg */
#define SYS_sendmmsg_x32	538	/* compat_sys_sendmmsg */
#define SYS_sendmsg	46	/* sys_sendmsg */
#define SYS_sendmsg_x32	518	/* compat_sys_sendmsg */
#define SYS_sendto	44	/* sys_sendto */
#define SYS_set_mempolicy	238	/* sys_set_mempolicy */
#define SYS_set_robust_list	273	/* sys_set_robust_list */
#define SYS_set_robust_list_x32	530	/* compat_sys_set_robust_list */
#define SYS_set_thread_area	205	/*  */
#define SYS_set_tid_address	218	/* sys_set_tid_address */
#define SYS_setdomainname	171	/* sys_setdomainname */
#define SYS_setfsgid	123	/* sys_setfsgid */
#define SYS_setfsuid	122	/* sys_setfsuid */
#define SYS_setgid	106	/* sys_setgid */
#define SYS_setgroups	116	/* sys_setgroups */
#define SYS_sethostname	170	/* sys_sethostname */
#define SYS_setitimer	38	/* sys_setitimer */
#define SYS_setns	308	/* sys_setns */
#define SYS_setpgid	109	/* sys_setpgid */
#define SYS_setpriority	141	/* sys_setpriority */
#define SYS_setregid	114	/* sys_setregid */
#define SYS_setresgid	119	/* sys_setresgid */
#define SYS_setresuid	117	/* sys_setresuid */
#define SYS_setreuid	113	/* sys_setreuid */
#define SYS_setrlimit	160	/* sys_setrlimit */
#define SYS_setsid	112	/* sys_setsid */
#define SYS_setsockopt	54	/* sys_setsockopt */
#define SYS_setsockopt_x32	541	/* compat_sys_setsockopt */
#define SYS_settimeofday	164	/* sys_settimeofday */
#define SYS_setuid	105	/* sys_setuid */
#define SYS_setxattr	188	/* sys_setxattr */
#define SYS_shmat	30	/* sys_shmat */
#define SYS_shmctl	31	/* sys_shmctl */
#define SYS_shmdt	67	/* sys_shmdt */
#define SYS_shmget	29	/* sys_shmget */
#define SYS_shutdown	48	/* sys_shutdown */
#define SYS_sigaltstack	131	/* sys_sigaltstack */
#define SYS_sigaltstack_x32	525	/* compat_sys_sigaltstack */
#define SYS_signalfd4	289	/* sys_signalfd4 */
#define SYS_signalfd	282	/* sys_signalfd */
#define SYS_socket	41	/* sys_socket */
#define SYS_socketpair	53	/* sys_socketpair */
#define SYS_splice	275	/* sys_splice */
#define SYS_stat	4	/* sys_newstat */
#define SYS_statfs	137	/* sys_statfs */
#define SYS_statx	332	/* sys_statx */
#define SYS_swapoff	168	/* sys_swapoff */
#define SYS_swapon	167	/* sys_swapon */
#define SYS_symlink	88	/* sys_symlink */
#define SYS_symlinkat	266	/* sys_symlinkat */
#define SYS_sync	162	/* sys_sync */
#define SYS_sync_file_range	277	/* sys_sync_file_range */
#define SYS_syncfs	306	/* sys_syncfs */
#define SYS_sysfs	139	/* sys_sysfs */
#define SYS_sysinfo	99	/* sys_sysinfo */
#define SYS_syslog	103	/* sys_syslog */
#define SYS_tee	276		/* sys_tee */
#define SYS_tgkill	234	/* sys_tgkill */
#define SYS_time	201	/* sys_time */
#define SYS_timer_create	222	/* sys_timer_create */
#define SYS_timer_create_x32	526	/* compat_sys_timer_create */
#define SYS_timer_delete	226	/* sys_timer_delete */
#define SYS_timer_getoverrun	225	/* sys_timer_getoverrun */
#define SYS_timer_gettime	224	/* sys_timer_gettime */
#define SYS_timer_settime	223	/* sys_timer_settime */
#define SYS_timerfd_create	283	/* sys_timerfd_create */
#define SYS_timerfd_gettime	287	/* sys_timerfd_gettime */
#define SYS_timerfd_settime	286	/* sys_timerfd_settime */
#define SYS_times	100	/* sys_times */
#define SYS_tkill	200	/* sys_tkill */
#define SYS_truncate	76	/* sys_truncate */
#define SYS_tuxcall	184	/*  */
#define SYS_umask	95	/* sys_umask */
#define SYS_umount2	166	/* sys_umount */
#define SYS_uname	63	/* sys_newuname */
#define SYS_unlink	87	/* sys_unlink */
#define SYS_unlinkat	263	/* sys_unlinkat */
#define SYS_unshare	272	/* sys_unshare */
#define SYS_uselib	134	/*  */
#define SYS_userfaultfd	323	/* sys_userfaultfd */
#define SYS_ustat	136	/* sys_ustat */
#define SYS_utime	132	/* sys_utime */
#define SYS_utimensat	280	/* sys_utimensat */
#define SYS_utimes	235	/* sys_utimes */
#define SYS_vfork	58	/* sys_vfork/ptregs */
#define SYS_vhangup	153	/* sys_vhangup */
#define SYS_vmsplice	278	/* sys_vmsplice */
#define SYS_vmsplice_x32	532	/* compat_sys_vmsplice */
#define SYS_vserver	236	/*  */
#define SYS_wait4	61	/* sys_wait4 */
#define SYS_waitid	247	/* sys_waitid */
#define SYS_waitid_x32	529	/* compat_sys_waitid */
#define SYS_write	1	/* sys_write */
#define SYS_writev	20	/* sys_writev */
#define SYS_writev_x32	516	/* compat_sys_writev */

#endif /* SYSCALLS_H */
