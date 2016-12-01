WORDSIZE=64
ARCH_LIB=syscall_amd64.S

CSTD_CFLAGS=-std=C89 -pedantic

NOISY_CFLAGS=-Wall -Werror -Wextra -Wa,--noexecstack

NOCLIB_CFLAGS=-nostdlib -D__WORDSIZE=$(WORDSIZE) $(ARCH_LIB)

#DEBUG_CFLAGS=-g -O0 -fdata-sections
DEBUG_CFLAGS=\
 -O2 -s \
 -Wl,--gc-sections \
 -fdata-sections \
 -fno-stack-protector \
 -fno-builtin \
 -fno-unwind-tables \
 -fno-asynchronous-unwind-tables

OUR_CFLAGS=$(CSTD_FLAGS) $(NOISY_CFLAGS) $(NOCLIB_CFLAGS) $(DEBUG_CFLAGS) $(CFLAGS)

SRC=hello.c
EXE=hello

hello:
	gcc $(OUR_CFLAGS) $(SRC) -o $(EXE)
	strip -R .comment ./$(EXE)

clean:
	rm -f hello
