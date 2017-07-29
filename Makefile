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
 src/linux-amd64/types.h \
 src/linux-amd64/limits.h \
 src/linux-amd64/syscalls.h \
 src/linux-amd64/start.S
else
ARCH_DEFINES=-m32 -DLINUX_I386
ARCH_SRC=\
 src/linux-i386/types.h \
 src/linux-i386/limits.h \
 src/linux-i386/syscalls.h \
 src/linux-i386/start.S
endif

EHLIBC_SRC=$(ARCH_SRC) \
 src/ehlibc.h \
 src/config.h \
 src/syscall.h \
 src/stdarg.h \
 src/eh-printf.h \
 src/eh-printf-private.h \
 src/eh-printf.c \
 src/eh-sys-context.h \
 src/eh-sys-context-linux.c \
 src/errno.h \
 src/errno.c \
 src/limits.h \
 src/stdarg.h \
 src/stdint.h \
 src/stdio.h \
 src/stdio.c \
 src/string.h \
 src/string.c \
 src/sys/stat.h \
 src/sys/time.h \
 src/syscall.h \
 src/unistd.h \
 src/unistd.c

CSTD_CFLAGS=-std=c89 -Wno-long-long

NOISY_CFLAGS=-Wall -Werror -Wextra -Wa,--noexecstack

NOCLIB_CFLAGS=-nostdlib $(USE_HOST_SYS_SYSCALL_H) $(ARCH_DEFINES) $(EHLIBC_SRC)


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

SRC=demo/hello.c
EXE=hello

STAT_SRC=demo/stat.c
STAT_EXE=stat

PUTS_SRC=demo/puts.c
PUTS_EXE=puts

$(EXE): $(SRC) $(EHLIBC_SRC)
	gcc $(OUR_CFLAGS) -Isrc $(SRC) -o $(EXE)
	$(STRIP) ./$(EXE)

$(STAT_EXE): $(STAT_SRC) $(EHLIBC_SRC)
	gcc $(OUR_CFLAGS) -Isrc $(STAT_SRC) -o $(STAT_EXE)
	$(STRIP) ./$(STAT_EXE)

$(PUTS_EXE): $(PUTS_SRC) $(EHLIBC_SRC)
	gcc $(OUR_CFLAGS) -Isrc $(PUTS_SRC) -o $(PUTS_EXE)
	$(STRIP) ./$(PUTS_EXE)

check: $(PUTS_EXE) $(STAT_EXE) $(EXE)
	./$(PUTS_EXE)
	./$(STAT_EXE) | hexdump
	./$(EXE)

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
		`find src demo -name '*.h' -o -name '*.c'`
	patch -Rp1 -i misc/pre-tidy.patch


clean:
	rm -fv $(EXE) $(STAT_EXE) $(PUTS_EXE)
	find . -name '*~' -exec rm -v \{} \;
