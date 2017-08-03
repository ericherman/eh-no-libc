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
 src/linux-amd64/syscalls.S
ARCH_HEADERS=\
 src/linux-amd64/syscalls.h \
 src/linux-amd64/types.h \
 src/linux-amd64/limits.h \
 src/linux-amd64/float.h
else
ARCH_DEFINES=-m32 -DLINUX_I386
ARCH_SRC=\
 src/linux-i386/start.S \
 src/linux-i386/syscalls.S
ARCH_HEADERS=\
 src/linux-i386/syscalls.h \
 src/linux-i386/types.h \
 src/linux-i386/limits.h \
 src/linux-i386/float.h
endif

EH_PRINTF_SRC=\
 src/eh-printf/eh-printf.c \
 src/eh-printf/eh-printf-parse-float.c \
 src/eh-printf/eh-printf-sys-context-linux.c
EH_PRINTF_HEADERS=\
 src/eh-printf/eh-printf.h \
 src/eh-printf/eh-printf-parse-float.h \
 src/eh-printf/eh-printf-private.h \
 src/eh-printf/eh-printf-sys-context.h

DUMB_ALLOC_SRC=\
 src/dumb-alloc/dumb-alloc.c \
 src/dumb-alloc/dumb-alloc-global.c \
 src/dumb-alloc/dumb-os-alloc.c
DUMB_ALLOC_HEADERS=\
 src/dumb-alloc/dumb-alloc.h \
 src/dumb-alloc/dumb-alloc-global.h \
 src/dumb-alloc/dumb-alloc-private.h \
 src/dumb-alloc/dumb-printf-defines.h \
 src/dumb-alloc/dumb-os-alloc.h

EHLIBC_SRC=$(ARCH_SRC) \
 src/errno.c \
 src/stdio.c \
 src/stdlib.c \
 src/string.c \
 src/sys/mman.c \
 src/syscall.c \
 src/unistd.c \
 $(DUMB_ALLOC_SRC) \
 $(EH_PRINTF_SRC)

EHLIBC_HEADERS=$(ARCH_HEADERS) \
 src/alloca.h \
 src/stdarg.h \
 src/errno.h \
 src/float.h \
 src/libio.h \
 src/limits.h \
 src/mman.h \
 src/stdarg.h \
 src/stddef.h \
 src/stdint.h \
 src/stdio.h \
 src/stdlib.h \
 src/string.h \
 src/sys/mman.h \
 src/sys/stat.h \
 src/sys/time.h \
 src/time.h \
 src/syscall.h \
 src/unistd.h \
 src/wchar.h

HEADERS=$(EHLIBC_HEADERS) $(DUMB_ALLOC_HEADERS) $(EH_PRINTF_HEADERS)

EHLIBC_HEADERS=$(ARCH_HEADERS) \
 src/alloca.h \

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

COMMON_CFLAGS=\
 -fdata-sections \
 -Wl,--gc-sections \
 -fno-builtin

ifeq ($(DEBUG), 1)
DEBUG_CFLAGS=-g -O0 -DDEBUG
else
DEBUG_CFLAGS=-g -O2 -DNDEBUG \
 -fomit-frame-pointer \
 -fno-stack-protector \
 -fno-unwind-tables \
 -fno-asynchronous-unwind-tables
endif

OUR_CFLAGS=\
 -pipe \
 $(CSTD_CFLAGS) \
 $(NOISY_CFLAGS) \
 $(DEBUG_CFLAGS) \
 $(COMMON_CFLAGS) \
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

$(HELLO_EXE): $(HELLO_SRC) $(EHLIBC_SRC) $(HEADERS)
	gcc -o $(HELLO_EXE) $(OUR_CFLAGS) $(HELLO_SRC)
	$(FILE) ./$(HELLO_EXE)
	./$(HELLO_EXE) $(USER)

$(STAT_EXE): $(STAT_SRC) $(EHLIBC_SRC) $(HEADERS)
	gcc -o $(STAT_EXE) $(OUR_CFLAGS) $(STAT_SRC)

$(PUTS_EXE): $(PUTS_SRC) $(EHLIBC_SRC) $(HEADERS)
	gcc -o $(PUTS_EXE) $(OUR_CFLAGS) $(PUTS_SRC)

$(MALLOC_FREE_EXE): $(MALLOC_FREE_SRC) $(EHLIBC_SRC) $(HEADERS)
	gcc -o $(MALLOC_FREE_EXE) $(OUR_CFLAGS) $(MALLOC_FREE_SRC)

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
