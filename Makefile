WORDSIZE=64
ARCH_LIB=syscall_amd64.S

hello:
	gcc -D__WORDSIZE=$(WORDSIZE) -s -O2 -nostdlib $(ARCH_LIB) hello.c -o hello

clean:
	rm -f hello
