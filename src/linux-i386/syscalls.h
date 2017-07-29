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
cat ~/src/linux/arch/x86/entry/syscalls/syscall_32.tbl  | awk '/^[0-9]/ { nr=$1; abi=$2; name=$3; entry=$4; printf("#define SYS_%s\t%d\t/: %s %s :/\n", name, nr, abi, entry); }' | sort | sed -e 's@:@*@g' >> src/linux-i386/syscalls.h
*/

#define SYS__llseek	140	/* i386 sys_llseek */
#define SYS__newselect	142	/* i386 sys_select */
#define SYS__sysctl	149	/* i386 sys_sysctl */
#define SYS_accept4	364	/* i386 sys_accept4 */
#define SYS_access	33	/* i386 sys_access */
#define SYS_acct	51	/* i386 sys_acct */
#define SYS_add_key	286	/* i386 sys_add_key */
#define SYS_adjtimex	124	/* i386 sys_adjtimex */
#define SYS_afs_syscall	137	/* i386  */
#define SYS_alarm	27	/* i386 sys_alarm */
#define SYS_arch_prctl	384	/* i386 sys_arch_prctl */
#define SYS_bdflush	134	/* i386 sys_bdflush */
#define SYS_bind	361	/* i386 sys_bind */
#define SYS_bpf	357		/* i386 sys_bpf */
#define SYS_break	17	/* i386  */
#define SYS_brk	45		/* i386 sys_brk */
#define SYS_capget	184	/* i386 sys_capget */
#define SYS_capset	185	/* i386 sys_capset */
#define SYS_chdir	12	/* i386 sys_chdir */
#define SYS_chmod	15	/* i386 sys_chmod */
#define SYS_chown	182	/* i386 sys_chown16 */
#define SYS_chown32	212	/* i386 sys_chown */
#define SYS_chroot	61	/* i386 sys_chroot */
#define SYS_clock_adjtime	343	/* i386 sys_clock_adjtime */
#define SYS_clock_getres	266	/* i386 sys_clock_getres */
#define SYS_clock_gettime	265	/* i386 sys_clock_gettime */
#define SYS_clock_nanosleep	267	/* i386 sys_clock_nanosleep */
#define SYS_clock_settime	264	/* i386 sys_clock_settime */
#define SYS_clone	120	/* i386 sys_clone */
#define SYS_close	6	/* i386 sys_close */
#define SYS_connect	362	/* i386 sys_connect */
#define SYS_copy_file_range	377	/* i386 sys_copy_file_range */
#define SYS_creat	8	/* i386 sys_creat */
#define SYS_create_module	127	/* i386  */
#define SYS_delete_module	129	/* i386 sys_delete_module */
#define SYS_dup	41		/* i386 sys_dup */
#define SYS_dup2	63	/* i386 sys_dup2 */
#define SYS_dup3	330	/* i386 sys_dup3 */
#define SYS_epoll_create	254	/* i386 sys_epoll_create */
#define SYS_epoll_create1	329	/* i386 sys_epoll_create1 */
#define SYS_epoll_ctl	255	/* i386 sys_epoll_ctl */
#define SYS_epoll_pwait	319	/* i386 sys_epoll_pwait */
#define SYS_epoll_wait	256	/* i386 sys_epoll_wait */
#define SYS_eventfd	323	/* i386 sys_eventfd */
#define SYS_eventfd2	328	/* i386 sys_eventfd2 */
#define SYS_execve	11	/* i386 sys_execve */
#define SYS_execveat	358	/* i386 sys_execveat */
#define SYS_exit	1	/* i386 sys_exit */
#define SYS_exit_group	252	/* i386 sys_exit_group */
#define SYS_faccessat	307	/* i386 sys_faccessat */
#define SYS_fadvise64	250	/* i386 sys_fadvise64 */
#define SYS_fadvise64_64	272	/* i386 sys_fadvise64_64 */
#define SYS_fallocate	324	/* i386 sys_fallocate */
#define SYS_fanotify_init	338	/* i386 sys_fanotify_init */
#define SYS_fanotify_mark	339	/* i386 sys_fanotify_mark */
#define SYS_fchdir	133	/* i386 sys_fchdir */
#define SYS_fchmod	94	/* i386 sys_fchmod */
#define SYS_fchmodat	306	/* i386 sys_fchmodat */
#define SYS_fchown	95	/* i386 sys_fchown16 */
#define SYS_fchown32	207	/* i386 sys_fchown */
#define SYS_fchownat	298	/* i386 sys_fchownat */
#define SYS_fcntl	55	/* i386 sys_fcntl */
#define SYS_fcntl64	221	/* i386 sys_fcntl64 */
#define SYS_fdatasync	148	/* i386 sys_fdatasync */
#define SYS_fgetxattr	231	/* i386 sys_fgetxattr */
#define SYS_finit_module	350	/* i386 sys_finit_module */
#define SYS_flistxattr	234	/* i386 sys_flistxattr */
#define SYS_flock	143	/* i386 sys_flock */
#define SYS_fork	2	/* i386 sys_fork */
#define SYS_fremovexattr	237	/* i386 sys_fremovexattr */
#define SYS_fsetxattr	228	/* i386 sys_fsetxattr */
#define SYS_fstat	108	/* i386 sys_newfstat */
#define SYS_fstat64	197	/* i386 sys_fstat64 */
#define SYS_fstatat64	300	/* i386 sys_fstatat64 */
#define SYS_fstatfs	100	/* i386 sys_fstatfs */
#define SYS_fstatfs64	269	/* i386 sys_fstatfs64 */
#define SYS_fsync	118	/* i386 sys_fsync */
#define SYS_ftime	35	/* i386  */
#define SYS_ftruncate	93	/* i386 sys_ftruncate */
#define SYS_ftruncate64	194	/* i386 sys_ftruncate64 */
#define SYS_futex	240	/* i386 sys_futex */
#define SYS_futimesat	299	/* i386 sys_futimesat */
#define SYS_get_kernel_syms	130	/* i386  */
#define SYS_get_mempolicy	275	/* i386 sys_get_mempolicy */
#define SYS_get_robust_list	312	/* i386 sys_get_robust_list */
#define SYS_get_thread_area	244	/* i386 sys_get_thread_area */
#define SYS_getcpu	318	/* i386 sys_getcpu */
#define SYS_getcwd	183	/* i386 sys_getcwd */
#define SYS_getdents	141	/* i386 sys_getdents */
#define SYS_getdents64	220	/* i386 sys_getdents64 */
#define SYS_getegid	50	/* i386 sys_getegid16 */
#define SYS_getegid32	202	/* i386 sys_getegid */
#define SYS_geteuid	49	/* i386 sys_geteuid16 */
#define SYS_geteuid32	201	/* i386 sys_geteuid */
#define SYS_getgid	47	/* i386 sys_getgid16 */
#define SYS_getgid32	200	/* i386 sys_getgid */
#define SYS_getgroups	80	/* i386 sys_getgroups16 */
#define SYS_getgroups32	205	/* i386 sys_getgroups */
#define SYS_getitimer	105	/* i386 sys_getitimer */
#define SYS_getpeername	368	/* i386 sys_getpeername */
#define SYS_getpgid	132	/* i386 sys_getpgid */
#define SYS_getpgrp	65	/* i386 sys_getpgrp */
#define SYS_getpid	20	/* i386 sys_getpid */
#define SYS_getpmsg	188	/* i386  */
#define SYS_getppid	64	/* i386 sys_getppid */
#define SYS_getpriority	96	/* i386 sys_getpriority */
#define SYS_getrandom	355	/* i386 sys_getrandom */
#define SYS_getresgid	171	/* i386 sys_getresgid16 */
#define SYS_getresgid32	211	/* i386 sys_getresgid */
#define SYS_getresuid	165	/* i386 sys_getresuid16 */
#define SYS_getresuid32	209	/* i386 sys_getresuid */
#define SYS_getrlimit	76	/* i386 sys_old_getrlimit */
#define SYS_getrusage	77	/* i386 sys_getrusage */
#define SYS_getsid	147	/* i386 sys_getsid */
#define SYS_getsockname	367	/* i386 sys_getsockname */
#define SYS_getsockopt	365	/* i386 sys_getsockopt */
#define SYS_gettid	224	/* i386 sys_gettid */
#define SYS_gettimeofday	78	/* i386 sys_gettimeofday */
#define SYS_getuid	24	/* i386 sys_getuid16 */
#define SYS_getuid32	199	/* i386 sys_getuid */
#define SYS_getxattr	229	/* i386 sys_getxattr */
#define SYS_gtty	32	/* i386  */
#define SYS_idle	112	/* i386  */
#define SYS_init_module	128	/* i386 sys_init_module */
#define SYS_inotify_add_watch	292	/* i386 sys_inotify_add_watch */
#define SYS_inotify_init	291	/* i386 sys_inotify_init */
#define SYS_inotify_init1	332	/* i386 sys_inotify_init1 */
#define SYS_inotify_rm_watch	293	/* i386 sys_inotify_rm_watch */
#define SYS_io_cancel	249	/* i386 sys_io_cancel */
#define SYS_io_destroy	246	/* i386 sys_io_destroy */
#define SYS_io_getevents	247	/* i386 sys_io_getevents */
#define SYS_io_setup	245	/* i386 sys_io_setup */
#define SYS_io_submit	248	/* i386 sys_io_submit */
#define SYS_ioctl	54	/* i386 sys_ioctl */
#define SYS_ioperm	101	/* i386 sys_ioperm */
#define SYS_iopl	110	/* i386 sys_iopl */
#define SYS_ioprio_get	290	/* i386 sys_ioprio_get */
#define SYS_ioprio_set	289	/* i386 sys_ioprio_set */
#define SYS_ipc	117		/* i386 sys_ipc */
#define SYS_kcmp	349	/* i386 sys_kcmp */
#define SYS_kexec_load	283	/* i386 sys_kexec_load */
#define SYS_keyctl	288	/* i386 sys_keyctl */
#define SYS_kill	37	/* i386 sys_kill */
#define SYS_lchown	16	/* i386 sys_lchown16 */
#define SYS_lchown32	198	/* i386 sys_lchown */
#define SYS_lgetxattr	230	/* i386 sys_lgetxattr */
#define SYS_link	9	/* i386 sys_link */
#define SYS_linkat	303	/* i386 sys_linkat */
#define SYS_listen	363	/* i386 sys_listen */
#define SYS_listxattr	232	/* i386 sys_listxattr */
#define SYS_llistxattr	233	/* i386 sys_llistxattr */
#define SYS_lock	53	/* i386  */
#define SYS_lookup_dcookie	253	/* i386 sys_lookup_dcookie */
#define SYS_lremovexattr	236	/* i386 sys_lremovexattr */
#define SYS_lseek	19	/* i386 sys_lseek */
#define SYS_lsetxattr	227	/* i386 sys_lsetxattr */
#define SYS_lstat	107	/* i386 sys_newlstat */
#define SYS_lstat64	196	/* i386 sys_lstat64 */
#define SYS_madvise	219	/* i386 sys_madvise */
#define SYS_mbind	274	/* i386 sys_mbind */
#define SYS_membarrier	375	/* i386 sys_membarrier */
#define SYS_memfd_create	356	/* i386 sys_memfd_create */
#define SYS_migrate_pages	294	/* i386 sys_migrate_pages */
#define SYS_mincore	218	/* i386 sys_mincore */
#define SYS_mkdir	39	/* i386 sys_mkdir */
#define SYS_mkdirat	296	/* i386 sys_mkdirat */
#define SYS_mknod	14	/* i386 sys_mknod */
#define SYS_mknodat	297	/* i386 sys_mknodat */
#define SYS_mlock	150	/* i386 sys_mlock */
#define SYS_mlock2	376	/* i386 sys_mlock2 */
#define SYS_mlockall	152	/* i386 sys_mlockall */
#define SYS_mmap	90	/* i386 sys_old_mmap */
#define SYS_mmap2	192	/* i386 sys_mmap_pgoff */
#define SYS_modify_ldt	123	/* i386 sys_modify_ldt */
#define SYS_mount	21	/* i386 sys_mount */
#define SYS_move_pages	317	/* i386 sys_move_pages */
#define SYS_mprotect	125	/* i386 sys_mprotect */
#define SYS_mpx	56		/* i386  */
#define SYS_mq_getsetattr	282	/* i386 sys_mq_getsetattr */
#define SYS_mq_notify	281	/* i386 sys_mq_notify */
#define SYS_mq_open	277	/* i386 sys_mq_open */
#define SYS_mq_timedreceive	280	/* i386 sys_mq_timedreceive */
#define SYS_mq_timedsend	279	/* i386 sys_mq_timedsend */
#define SYS_mq_unlink	278	/* i386 sys_mq_unlink */
#define SYS_mremap	163	/* i386 sys_mremap */
#define SYS_msync	144	/* i386 sys_msync */
#define SYS_munlock	151	/* i386 sys_munlock */
#define SYS_munlockall	153	/* i386 sys_munlockall */
#define SYS_munmap	91	/* i386 sys_munmap */
#define SYS_name_to_handle_at	341	/* i386 sys_name_to_handle_at */
#define SYS_nanosleep	162	/* i386 sys_nanosleep */
#define SYS_nfsservctl	169	/* i386  */
#define SYS_nice	34	/* i386 sys_nice */
#define SYS_oldfstat	28	/* i386 sys_fstat */
#define SYS_oldlstat	84	/* i386 sys_lstat */
#define SYS_oldolduname	59	/* i386 sys_olduname */
#define SYS_oldstat	18	/* i386 sys_stat */
#define SYS_olduname	109	/* i386 sys_uname */
#define SYS_open	5	/* i386 sys_open */
#define SYS_open_by_handle_at	342	/* i386 sys_open_by_handle_at */
#define SYS_openat	295	/* i386 sys_openat */
#define SYS_pause	29	/* i386 sys_pause */
#define SYS_perf_event_open	336	/* i386 sys_perf_event_open */
#define SYS_personality	136	/* i386 sys_personality */
#define SYS_pipe	42	/* i386 sys_pipe */
#define SYS_pipe2	331	/* i386 sys_pipe2 */
#define SYS_pivot_root	217	/* i386 sys_pivot_root */
#define SYS_pkey_alloc	381	/* i386 sys_pkey_alloc */
#define SYS_pkey_free	382	/* i386 sys_pkey_free */
#define SYS_pkey_mprotect	380	/* i386 sys_pkey_mprotect */
#define SYS_poll	168	/* i386 sys_poll */
#define SYS_ppoll	309	/* i386 sys_ppoll */
#define SYS_prctl	172	/* i386 sys_prctl */
#define SYS_pread64	180	/* i386 sys_pread64 */
#define SYS_preadv	333	/* i386 sys_preadv */
#define SYS_preadv2	378	/* i386 sys_preadv2 */
#define SYS_prlimit64	340	/* i386 sys_prlimit64 */
#define SYS_process_vm_readv	347	/* i386 sys_process_vm_readv */
#define SYS_process_vm_writev	348	/* i386 sys_process_vm_writev */
#define SYS_prof	44	/* i386  */
#define SYS_profil	98	/* i386  */
#define SYS_pselect6	308	/* i386 sys_pselect6 */
#define SYS_ptrace	26	/* i386 sys_ptrace */
#define SYS_putpmsg	189	/* i386  */
#define SYS_pwrite64	181	/* i386 sys_pwrite64 */
#define SYS_pwritev	334	/* i386 sys_pwritev */
#define SYS_pwritev2	379	/* i386 sys_pwritev2 */
#define SYS_query_module	167	/* i386  */
#define SYS_quotactl	131	/* i386 sys_quotactl */
#define SYS_read	3	/* i386 sys_read */
#define SYS_readahead	225	/* i386 sys_readahead */
#define SYS_readdir	89	/* i386 sys_old_readdir */
#define SYS_readlink	85	/* i386 sys_readlink */
#define SYS_readlinkat	305	/* i386 sys_readlinkat */
#define SYS_readv	145	/* i386 sys_readv */
#define SYS_reboot	88	/* i386 sys_reboot */
#define SYS_recvfrom	371	/* i386 sys_recvfrom */
#define SYS_recvmmsg	337	/* i386 sys_recvmmsg */
#define SYS_recvmsg	372	/* i386 sys_recvmsg */
#define SYS_remap_file_pages	257	/* i386 sys_remap_file_pages */
#define SYS_removexattr	235	/* i386 sys_removexattr */
#define SYS_rename	38	/* i386 sys_rename */
#define SYS_renameat	302	/* i386 sys_renameat */
#define SYS_renameat2	353	/* i386 sys_renameat2 */
#define SYS_request_key	287	/* i386 sys_request_key */
#define SYS_restart_syscall	0	/* i386 sys_restart_syscall */
#define SYS_rmdir	40	/* i386 sys_rmdir */
#define SYS_rt_sigaction	174	/* i386 sys_rt_sigaction */
#define SYS_rt_sigpending	176	/* i386 sys_rt_sigpending */
#define SYS_rt_sigprocmask	175	/* i386 sys_rt_sigprocmask */
#define SYS_rt_sigqueueinfo	178	/* i386 sys_rt_sigqueueinfo */
#define SYS_rt_sigreturn	173	/* i386 sys_rt_sigreturn */
#define SYS_rt_sigsuspend	179	/* i386 sys_rt_sigsuspend */
#define SYS_rt_sigtimedwait	177	/* i386 sys_rt_sigtimedwait */
#define SYS_rt_tgsigqueueinfo	335	/* i386 sys_rt_tgsigqueueinfo */
#define SYS_sched_get_priority_max	159	/* i386 sys_sched_get_priority_max */
#define SYS_sched_get_priority_min	160	/* i386 sys_sched_get_priority_min */
#define SYS_sched_getaffinity	242	/* i386 sys_sched_getaffinity */
#define SYS_sched_getattr	352	/* i386 sys_sched_getattr */
#define SYS_sched_getparam	155	/* i386 sys_sched_getparam */
#define SYS_sched_getscheduler	157	/* i386 sys_sched_getscheduler */
#define SYS_sched_rr_get_interval	161	/* i386 sys_sched_rr_get_interval */
#define SYS_sched_setaffinity	241	/* i386 sys_sched_setaffinity */
#define SYS_sched_setattr	351	/* i386 sys_sched_setattr */
#define SYS_sched_setparam	154	/* i386 sys_sched_setparam */
#define SYS_sched_setscheduler	156	/* i386 sys_sched_setscheduler */
#define SYS_sched_yield	158	/* i386 sys_sched_yield */
#define SYS_seccomp	354	/* i386 sys_seccomp */
#define SYS_select	82	/* i386 sys_old_select */
#define SYS_sendfile	187	/* i386 sys_sendfile */
#define SYS_sendfile64	239	/* i386 sys_sendfile64 */
#define SYS_sendmmsg	345	/* i386 sys_sendmmsg */
#define SYS_sendmsg	370	/* i386 sys_sendmsg */
#define SYS_sendto	369	/* i386 sys_sendto */
#define SYS_set_mempolicy	276	/* i386 sys_set_mempolicy */
#define SYS_set_robust_list	311	/* i386 sys_set_robust_list */
#define SYS_set_thread_area	243	/* i386 sys_set_thread_area */
#define SYS_set_tid_address	258	/* i386 sys_set_tid_address */
#define SYS_setdomainname	121	/* i386 sys_setdomainname */
#define SYS_setfsgid	139	/* i386 sys_setfsgid16 */
#define SYS_setfsgid32	216	/* i386 sys_setfsgid */
#define SYS_setfsuid	138	/* i386 sys_setfsuid16 */
#define SYS_setfsuid32	215	/* i386 sys_setfsuid */
#define SYS_setgid	46	/* i386 sys_setgid16 */
#define SYS_setgid32	214	/* i386 sys_setgid */
#define SYS_setgroups	81	/* i386 sys_setgroups16 */
#define SYS_setgroups32	206	/* i386 sys_setgroups */
#define SYS_sethostname	74	/* i386 sys_sethostname */
#define SYS_setitimer	104	/* i386 sys_setitimer */
#define SYS_setns	346	/* i386 sys_setns */
#define SYS_setpgid	57	/* i386 sys_setpgid */
#define SYS_setpriority	97	/* i386 sys_setpriority */
#define SYS_setregid	71	/* i386 sys_setregid16 */
#define SYS_setregid32	204	/* i386 sys_setregid */
#define SYS_setresgid	170	/* i386 sys_setresgid16 */
#define SYS_setresgid32	210	/* i386 sys_setresgid */
#define SYS_setresuid	164	/* i386 sys_setresuid16 */
#define SYS_setresuid32	208	/* i386 sys_setresuid */
#define SYS_setreuid	70	/* i386 sys_setreuid16 */
#define SYS_setreuid32	203	/* i386 sys_setreuid */
#define SYS_setrlimit	75	/* i386 sys_setrlimit */
#define SYS_setsid	66	/* i386 sys_setsid */
#define SYS_setsockopt	366	/* i386 sys_setsockopt */
#define SYS_settimeofday	79	/* i386 sys_settimeofday */
#define SYS_setuid	23	/* i386 sys_setuid16 */
#define SYS_setuid32	213	/* i386 sys_setuid */
#define SYS_setxattr	226	/* i386 sys_setxattr */
#define SYS_sgetmask	68	/* i386 sys_sgetmask */
#define SYS_shutdown	373	/* i386 sys_shutdown */
#define SYS_sigaction	67	/* i386 sys_sigaction */
#define SYS_sigaltstack	186	/* i386 sys_sigaltstack */
#define SYS_signal	48	/* i386 sys_signal */
#define SYS_signalfd	321	/* i386 sys_signalfd */
#define SYS_signalfd4	327	/* i386 sys_signalfd4 */
#define SYS_sigpending	73	/* i386 sys_sigpending */
#define SYS_sigprocmask	126	/* i386 sys_sigprocmask */
#define SYS_sigreturn	119	/* i386 sys_sigreturn */
#define SYS_sigsuspend	72	/* i386 sys_sigsuspend */
#define SYS_socket	359	/* i386 sys_socket */
#define SYS_socketcall	102	/* i386 sys_socketcall */
#define SYS_socketpair	360	/* i386 sys_socketpair */
#define SYS_splice	313	/* i386 sys_splice */
#define SYS_ssetmask	69	/* i386 sys_ssetmask */
#define SYS_stat	106	/* i386 sys_newstat */
#define SYS_stat64	195	/* i386 sys_stat64 */
#define SYS_statfs	99	/* i386 sys_statfs */
#define SYS_statfs64	268	/* i386 sys_statfs64 */
#define SYS_statx	383	/* i386 sys_statx */
#define SYS_stime	25	/* i386 sys_stime */
#define SYS_stty	31	/* i386  */
#define SYS_swapoff	115	/* i386 sys_swapoff */
#define SYS_swapon	87	/* i386 sys_swapon */
#define SYS_symlink	83	/* i386 sys_symlink */
#define SYS_symlinkat	304	/* i386 sys_symlinkat */
#define SYS_sync	36	/* i386 sys_sync */
#define SYS_sync_file_range	314	/* i386 sys_sync_file_range */
#define SYS_syncfs	344	/* i386 sys_syncfs */
#define SYS_sysfs	135	/* i386 sys_sysfs */
#define SYS_sysinfo	116	/* i386 sys_sysinfo */
#define SYS_syslog	103	/* i386 sys_syslog */
#define SYS_tee	315		/* i386 sys_tee */
#define SYS_tgkill	270	/* i386 sys_tgkill */
#define SYS_time	13	/* i386 sys_time */
#define SYS_timer_create	259	/* i386 sys_timer_create */
#define SYS_timer_delete	263	/* i386 sys_timer_delete */
#define SYS_timer_getoverrun	262	/* i386 sys_timer_getoverrun */
#define SYS_timer_gettime	261	/* i386 sys_timer_gettime */
#define SYS_timer_settime	260	/* i386 sys_timer_settime */
#define SYS_timerfd_create	322	/* i386 sys_timerfd_create */
#define SYS_timerfd_gettime	326	/* i386 sys_timerfd_gettime */
#define SYS_timerfd_settime	325	/* i386 sys_timerfd_settime */
#define SYS_times	43	/* i386 sys_times */
#define SYS_tkill	238	/* i386 sys_tkill */
#define SYS_truncate	92	/* i386 sys_truncate */
#define SYS_truncate64	193	/* i386 sys_truncate64 */
#define SYS_ugetrlimit	191	/* i386 sys_getrlimit */
#define SYS_ulimit	58	/* i386  */
#define SYS_umask	60	/* i386 sys_umask */
#define SYS_umount	22	/* i386 sys_oldumount */
#define SYS_umount2	52	/* i386 sys_umount */
#define SYS_uname	122	/* i386 sys_newuname */
#define SYS_unlink	10	/* i386 sys_unlink */
#define SYS_unlinkat	301	/* i386 sys_unlinkat */
#define SYS_unshare	310	/* i386 sys_unshare */
#define SYS_uselib	86	/* i386 sys_uselib */
#define SYS_userfaultfd	374	/* i386 sys_userfaultfd */
#define SYS_ustat	62	/* i386 sys_ustat */
#define SYS_utime	30	/* i386 sys_utime */
#define SYS_utimensat	320	/* i386 sys_utimensat */
#define SYS_utimes	271	/* i386 sys_utimes */
#define SYS_vfork	190	/* i386 sys_vfork */
#define SYS_vhangup	111	/* i386 sys_vhangup */
#define SYS_vm86	166	/* i386 sys_vm86 */
#define SYS_vm86old	113	/* i386 sys_vm86old */
#define SYS_vmsplice	316	/* i386 sys_vmsplice */
#define SYS_vserver	273	/* i386  */
#define SYS_wait4	114	/* i386 sys_wait4 */
#define SYS_waitid	284	/* i386 sys_waitid */
#define SYS_waitpid	7	/* i386 sys_waitpid */
#define SYS_write	4	/* i386 sys_write */
#define SYS_writev	146	/* i386 sys_writev */

#endif /* SYSCALLS_H */
