WORDSIZE=64
ARCH_LIB=syscall_amd64.S

#DEBUG_CFLAGS=-g
DEBUG_CFLAGS=\
 -fno-unwind-tables \
 -fno-asynchronous-unwind-tables


hello:
	gcc -D__WORDSIZE=$(WORDSIZE) \
		-s -O2 -nostdlib $(ARCH_LIB) \
		$(DEBUG_CFLAGS) \
		hello.c -o hello
	strip -R .comment ./hello

clean:
	rm -f hello
