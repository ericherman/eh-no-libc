ifndef ($(TARGET))
 ifeq ($(shell uname), Linux)
   ifeq ($(shell arch), x86_64)
TARGET=LINUX_AMD64
   endif
 endif
endif

#USE_HOST_SYS_SYSCALL_H=-DUSE_HOST_SYS_SYSCALL_H=1

ifeq ($(TARGET), LINUX_AMD64)
ARCH_DEFINES=-DLINUX_AMD64
ARCH_SRC=\
 src/linux-amd64/start.S \
 src/linux-amd64/types.h \
 src/linux-amd64/limits.h \
 src/linux-amd64/float.h \
 src/linux-amd64/syscalls.h
else
ARCH_DEFINES=-m32 -DLINUX_I386
ARCH_SRC=\
 src/linux-i386/start.S \
 src/linux-i386/types.h \
 src/linux-i386/limits.h \
 src/linux-i386/float.h \
 src/linux-i386/syscalls.h
endif

EH_PRINTF_SRC=\
 src/eh-printf/eh-printf.h \
 src/eh-printf/eh-printf.c \
 src/eh-printf/eh-printf-parse-float.h \
 src/eh-printf/eh-printf-parse-float.c \
 src/eh-printf/eh-printf-private.h \
 src/eh-printf/eh-printf-sys-context.h \
 src/eh-printf/eh-printf-sys-context-linux.c

DUMB_ALLOC_SRC=\
 src/dumb-alloc/dumb-alloc.h \
 src/dumb-alloc/dumb-alloc.c \
 src/dumb-alloc/dumb-alloc-global.h \
 src/dumb-alloc/dumb-alloc-global.c \
 src/dumb-alloc/dumb-alloc-private.h \
 src/dumb-alloc/dumb-printf-defines.h \
 src/dumb-alloc/dumb-os-alloc.h \
 src/dumb-alloc/dumb-os-alloc.c

EHLIBC_SRC=$(ARCH_SRC) \
 src/alloca.h \
 src/stdarg.h \
 src/errno.h \
 src/errno.c \
 src/float.h \
 src/libio.h \
 src/limits.h \
 src/mman.h \
 src/stdarg.h \
 src/stddef.h \
 src/stdint.h \
 src/stdio.h \
 src/stdio.c \
 src/stdlib.h \
 src/stdlib.c \
 src/string.h \
 src/string.c \
 src/sys/mman.h \
 src/sys/mman.c \
 src/sys/stat.h \
 src/sys/time.h \
 src/time.h \
 src/syscall.h \
 src/syscall.c \
 src/unistd.h \
 src/unistd.c \
 src/wchar.h \
 $(DUMB_ALLOC_SRC) \
 $(EH_PRINTF_SRC)


CSTD_CFLAGS=-std=gnu89 -Wno-long-long

NOISY_CFLAGS=-Wall -Werror -Wextra -Wa,--noexecstack

NOCLIB_CFLAGS=\
 -nostdlib \
 $(ARCH_DEFINES) \
 -DHAVE_FLOAT_H=1 \
 -DHAVE_LIMITS_H=1 \
 -DHAVE_STDARG_H=1 \
 -DHAVE_STDDEF_H=1 \
 -DHAVE_STDINT_H=1 \
 -I./src \
 -I./src/dumb-alloc \
 $(EHLIBC_SRC)

FILE=file

ifeq ($(DEBUG), 1)
DEBUG_CFLAGS=-g -O0 -fdata-sections -DDEBUG
STRIP=ls -l
else
DEBUG_CFLAGS=\
 -O2 -s \
 -fomit-frame-pointer \
 -fdata-sections \
 -fno-stack-protector \
 -fno-unwind-tables \
 -fno-asynchronous-unwind-tables \
 -fno-builtin \
 -Wl,--gc-sections \
 -DNDEBUG
STRIP=strip -R .comment
endif

OUR_CFLAGS=\
 -pipe \
 $(CSTD_CFLAGS) \
 $(NOISY_CFLAGS) \
 $(DEBUG_CFLAGS) \
 $(CFLAGS) \
 $(NOCLIB_CFLAGS)


# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

HELLO_SRC=demo/hello.c
HELLO_EXE=hello

STAT_SRC=demo/stat.c
STAT_EXE=stat

PUTS_SRC=demo/puts.c
PUTS_EXE=puts

MALLOC_FREE_SRC=demo/malloc-free.c
MALLOC_FREE_EXE=malloc-free

default: hello

$(HELLO_EXE): $(HELLO_SRC) $(EHLIBC_SRC)
	gcc -o $(HELLO_EXE) $(OUR_CFLAGS) $(HELLO_SRC)
	$(STRIP) ./$(HELLO_EXE)
	$(FILE) ./$(HELLO_EXE)
	./$(HELLO_EXE) $(USER)

$(STAT_EXE): $(STAT_SRC) $(EHLIBC_SRC)
	gcc -o $(STAT_EXE) $(OUR_CFLAGS) $(STAT_SRC)
	$(STRIP) ./$(STAT_EXE)

$(PUTS_EXE): $(PUTS_SRC) $(EHLIBC_SRC)
	gcc -o $(PUTS_EXE) $(OUR_CFLAGS) $(PUTS_SRC)
	$(STRIP) ./$(PUTS_EXE)

$(MALLOC_FREE_EXE): $(MALLOC_FREE_SRC) $(EHLIBC_SRC)
	gcc -o $(MALLOC_FREE_EXE) $(OUR_CFLAGS) $(MALLOC_FREE_SRC)
	$(STRIP) ./$(MALLOC_FREE_EXE)

check: $(PUTS_EXE) $(STAT_EXE) $(HELLO_EXE)
	./$(HELLO_EXE)
	./$(PUTS_EXE)
	./$(STAT_EXE) | hexdump

tidy:
	patch -Np1 -i misc/pre-tidy.patch
	$(LINDENT) \
		-T FILE \
		-T size_t \
		-T ssize_t \
		-T uint64_t \
		-T int64_t \
		-T uint32_t \
		-T int32_t \
		-T uint16_t \
		-T int16_t \
		-T uint8_t \
		-T int8_t \
		-T dev_t \
		-T time_t \
		-T syscall_slong_t \
		-T eh_printf_context_s \
		`find src demo -name '*.h' -o -name '*.c'`
	patch -Rp1 -i misc/pre-tidy.patch


clean:
	rm -fv $(HELLO_EXE) $(STAT_EXE) $(PUTS_EXE) $(MALLOC_FREE_EXE)
	find . -name '*~' -exec rm -v \{} \;
