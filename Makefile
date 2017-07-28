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
ARCH_SRC=src/linux-amd64/types.h \
 src/linux-amd64/syscalls.h \
 src/linux-amd64/start.S
else
ARCH_DEFINES=-m32 -DLINUX_I386
ARCH_SRC=src/linux-i386/types.h \
 src/linux-i386/syscalls.h \
 src/linux-i386/start.S
endif

EHLIBC_SRC=$(ARCH_SRC) \
 src/platform-types.h \
 src/platform-syscalls.h \
 src/platform-syscalls.c \
 src/ehlibc.h \
 src/ehlibc.c

CSTD_CFLAGS=-std=C89 -pedantic

NOISY_CFLAGS=-Wall -Werror -Wextra -Wa,--noexecstack

NOCLIB_CFLAGS=-nostdlib $(USE_HOST_SYS_SYSCALL_H) $(ARCH_DEFINES) $(EHLIBC_SRC)

#DEBUG_CFLAGS=-g -O0 -fdata-sections
DEBUG_CFLAGS=\
 -O2 -s \
 -fomit-frame-pointer \
 -Wl,--gc-sections \
 -fdata-sections \
 -fno-stack-protector \
 -fno-builtin \
 -fno-unwind-tables \
 -fno-asynchronous-unwind-tables

OUR_CFLAGS=$(CSTD_FLAGS) $(NOISY_CFLAGS) $(DEBUG_CFLAGS) \
 $(CFLAGS) \
 $(NOCLIB_CFLAGS) \
 -pipe


# extracted from https://github.com/torvalds/linux/blob/master/scripts/Lindent
LINDENT=indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0

SRC=demo/hello.c
EXE=hello

STAT_SRC=demo/stat.c
STAT_EXE=stat

$(EXE): $(SRC) $(EHLIBC_SRC)
	gcc $(OUR_CFLAGS) -Isrc $(SRC) -o $(EXE)
	strip -R .comment ./$(EXE)

$(STAT_EXE): $(STAT_SRC) $(EHLIBC_SRC)
	gcc $(OUR_CFLAGS) -Isrc $(STAT_SRC) -o $(STAT_EXE)
	strip -R .comment ./$(STAT_EXE)

check: $(EXE) $(STAT_EXE)
	./$(EXE)
	./$(STAT_EXE) | hexdump

tidy:
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
		-T stat_info_s \
		`find src demo -name '*.h' -o -name '*.c'`


clean:
	rm -fv $(EXE) $(STAT_EXE)
	find . -name '*~' -exec rm -v \{} \;
