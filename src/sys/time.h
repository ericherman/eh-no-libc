#ifndef _TIME_H
#define _TIME_H	1

#include "stdint.h"

typedef ssize_t syscall_slong_t;
typedef ssize_t time_t;

/*
  http://pubs.opengroup.org/onlinepubs/007908775/xsh/time.h.html
*/
typedef struct {
	time_t sec;
	syscall_slong_t nsec;
} timespec;

#endif /* _TIME_H */
