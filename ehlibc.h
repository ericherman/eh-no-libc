#ifndef EHLIBC_H
#define EHLIBC_H

#ifdef __WORDSIZE
#if ( __WORDSIZE == 64 )
/* size_t */
#define uptr unsigned long
/* ssize_t */
#define iptr long
#elif ( __WORDSIZE == 32 )
/* size_t */
#define uptr unsigned int
/* ssize_t */
#define iptr int
#endif
#endif

void *syscall5(uptr number, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);

iptr write(int fd, void const *data, uptr nbytes);

uptr strlen(char const *str);

#endif /* EHLIBC_H */
