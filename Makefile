
#ARCH_DEFINES=-DLINUX_AMD64
#ARCH_SRC=src/linux-amd64/types.h \
# src/linux-amd64/syscalls.h \
# src/linux-amd64/start.S

ARCH_DEFINES=-m32 -DLINUX_I386
ARCH_SRC=src/linux-i386/types.h \
 src/linux-i386/syscalls.h \
 src/linux-i386/start.S

EHLIBC_SRC=$(ARCH_SRC) \
 src/platform-types.h \
 src/platform-syscalls.h \
 src/ehlibc.h \
 src/ehlibc.c

CSTD_CFLAGS=-std=C89 -pedantic

NOISY_CFLAGS=-Wall -Werror -Wextra -Wa,--noexecstack

NOCLIB_CFLAGS=-nostdlib $(ARCH_DEFINES) $(EHLIBC_SRC)

#DEBUG_CFLAGS=-g -O0 -fdata-sections
DEBUG_CFLAGS=\
 -O2 -s \
 -Wl,--gc-sections \
 -fdata-sections \
 -fno-stack-protector \
 -fno-builtin \
 -fno-unwind-tables \
 -fno-asynchronous-unwind-tables

OUR_CFLAGS=$(CSTD_FLAGS) $(NOISY_CFLAGS) $(DEBUG_CFLAGS) \
 $(CFLAGS) \
 $(NOCLIB_CFLAGS)


SRC=demo/hello.c
EXE=hello

$(EXE): $(SRC) $(EHLIBC_SRC)
	gcc $(OUR_CFLAGS) -Isrc $(SRC) -o $(EXE)
	strip -R .comment ./$(EXE)

check: $(EXE)
	./$(EXE)

clean:
	rm -f hello
