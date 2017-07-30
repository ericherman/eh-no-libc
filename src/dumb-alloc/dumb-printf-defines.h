#ifndef DUMB_PRINTF_DEFINES_H
#define DUMB_PRINTF_DEFINES_H

#ifdef __LP64__			/* if 64 bit environment */
#define FMT_SIZEOF "%lu"
#define FMT_SIZE_T "%lu"
#define CAST_SIZE_T unsigned long
#else
#define FMT_SIZEOF "%u"
#define FMT_SIZE_T "%u"
#define CAST_SIZE_T unsigned int
#endif

#endif /* DUMB_PRINTF_DEFINES_H */
