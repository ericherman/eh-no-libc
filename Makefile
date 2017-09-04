ifndef ($(TARGET))
 ifeq ($(shell uname), Linux)
   ifeq ($(shell arch), x86_64)
TARGET=LINUX_AMD64
   endif
 endif
endif

ifeq ($(TARGET), LINUX_AMD64)
ARCH_DEFINES=-DLINUX_AMD64
ARCH_DIR=linux-amd64
else
ARCH_DEFINES=-m32 -DLINUX_I386
ARCH_DIR=linux-i386
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
 src/dumb-alloc/dumb-os-alloc.h

EHLIBC_SRC=\
 src/stdc-predef.h \
 src/$(ARCH_DIR)/start.S \
 src/$(ARCH_DIR)/syscalls.S \
 src/assert.c \
 src/ctype.c \
 src/errno.c \
 src/math.c \
 src/stdio.c \
 src/stdlib.c \
 src/string.c \
 src/strings.c \
 src/sys/mman.c \
 src/syscall.c \
 src/unistd.c \
 $(DUMB_ALLOC_SRC) \
 $(EH_PRINTF_SRC)

EHLIBC_HEADERS=\
 src/stdc-predef.h \
 src/$(ARCH_DIR)/types.h \
 src/alloca.h \
 src/assert.h \
 src/stdarg.h \
 src/ctype.h \
 src/errno.h \
 src/fcntl.h \
 src/float.h \
 src/$(ARCH_DIR)/float.h \
 src/inttypes.h \
 src/$(ARCH_DIR)/inttypes.h \
 src/iso646.h \
 src/libio.h \
 src/limits.h \
 src/$(ARCH_DIR)/limits.h \
 src/math.h \
 src/mman.h \
 src/stdarg.h \
 src/stddef.h \
 src/stdint.h \
 src/stdio.h \
 src/stdlib.h \
 src/string.h \
 src/strings.h \
 src/sys/mman.h \
 src/sys/stat.h \
 src/sys/time.h \
 src/sys/types.h \
 src/$(ARCH_DIR)/types.h \
 src/syscall.h \
 src/$(ARCH_DIR)/syscalls.h \
 src/time.h \
 src/unistd.h \
 src/wchar.h

ECHECK_HEADERS=\
 tests/echeck.h

HEADERS=$(EHLIBC_HEADERS) $(DUMB_ALLOC_HEADERS) $(EH_PRINTF_HEADERS)

TEST_HEADERS=$(HEADERS) $(ECHECK_HEADERS)

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
 -DDUMB_ALLOC_MEM_LIMIT=0 \
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

EXIT_SRC=demo/exit.c
EXIT_EXE=exit

HELLO_SRC=demo/hello.c
HELLO_EXE=hello

STAT_SRC=demo/stat.c
STAT_EXE=stat

PUTS_SRC=demo/puts.c
PUTS_EXE=puts

CTYPES_SRC=demo/ctypes.c
CTYPES_EXE=ctypes

CHECKERED_ALLOC_FREE_SRC=demo/malloc-free.c
CHECKERED_ALLOC_FREE_EXE=malloc-free

TEST_FGETC_SRC=tests/echeck.c tests/test-fgetc.c
TEST_FGETC_EXE=test-fgetc

TEST_FILE_IO_ROUNDTRIP_SRC=tests/echeck.c tests/test-file-io-roundtrip.c
TEST_FILE_IO_ROUNDTRIP_EXE=test-file-io-roundtrip

TEST_FFS_SRC=tests/echeck.c tests/test-ffs.c
TEST_FFS_EXE=test-ffs

TEST_ISINF_SRC=tests/echeck.c tests/test-isinf.c
TEST_ISINF_EXE=test-isinf

TEST_MEMCCPY_SRC=tests/echeck.c tests/test-memccpy.c
TEST_MEMCCPY_EXE=test-memccpy

TEST_MEMCHR_SRC=tests/echeck.c tests/test-memchr.c
TEST_MEMCHR_EXE=test-memchr

TEST_MEMCMP_SRC=tests/echeck.c tests/test-memcmp.c
TEST_MEMCMP_EXE=test-memcmp

TEST_MEMCPY_SRC=tests/echeck.c tests/test-memcpy.c
TEST_MEMCPY_EXE=test-memcpy

TEST_MEMMOVE_SRC=tests/echeck.c tests/test-memmove.c
TEST_MEMMOVE_EXE=test-memmove

TEST_MEMSET_SRC=tests/echeck.c tests/test-memset.c
TEST_MEMSET_EXE=test-memset

TEST_STRCAT_SRC=tests/echeck.c tests/test-strcat.c
TEST_STRCAT_EXE=test-strcat

TEST_STRCASECMP_SRC=tests/echeck.c tests/test-strcasecmp.c
TEST_STRCASECMP_EXE=test-strcasecmp

TEST_STRCHR_SRC=tests/echeck.c tests/test-strchr.c
TEST_STRCHR_EXE=test-strchr

TEST_STRCPY_SRC=tests/echeck.c tests/test-strcpy.c
TEST_STRCPY_EXE=test-strcpy

TEST_STRDUP_SRC=tests/echeck.c tests/test-strdup.c
TEST_STRDUP_EXE=test-strdup

TEST_STRSPN_SRC=tests/echeck.c tests/test-strspn.c
TEST_STRSPN_EXE=test-strspn

TEST_STRPBRK_SRC=tests/echeck.c tests/test-strpbrk.c
TEST_STRPBRK_EXE=test-strpbrk

TEST_STRSTR_SRC=tests/echeck.c tests/test-strstr.c
TEST_STRSTR_EXE=test-strstr

TEST_STRTOK_SRC=tests/echeck.c tests/test-strtok.c
TEST_STRTOK_EXE=test-strtok

TEST_STRTOL_SRC=tests/echeck.c tests/test-strtol.c
TEST_STRTOL_EXE=test-strtol

TESTS=\
 $(TEST_FILE_IO_ROUNDTRIP_EXE) \
 $(TEST_FGETC_EXE) \
 $(TEST_FFS_EXE) \
 $(TEST_ISINF_EXE) \
 $(TEST_MEMCCPY_EXE) \
 $(TEST_MEMCHR_EXE) \
 $(TEST_MEMCMP_EXE) \
 $(TEST_MEMCPY_EXE) \
 $(TEST_MEMMOVE_EXE) \
 $(TEST_MEMSET_EXE) \
 $(TEST_STRCASECMP_EXE) \
 $(TEST_STRCAT_EXE) \
 $(TEST_STRCHR_EXE) \
 $(TEST_STRCPY_EXE) \
 $(TEST_STRDUP_EXE) \
 $(TEST_STRSPN_EXE) \
 $(TEST_STRPBRK_EXE) \
 $(TEST_STRSTR_EXE) \
 $(TEST_STRTOK_EXE) \
 $(TEST_STRTOL_EXE) \


SANITY=$(EXIT_EXE) $(PUTS_EXE) $(STAT_EXE) $(HELLO_EXE) $(CHECKERED_ALLOC_FREE_EXE) $(CTYPES_EXE)

default: hello


$(EXIT_EXE): $(EXIT_SRC) $(EHLIBC_SRC) $(HEADERS)
	gcc -o $(EXIT_EXE) $(OUR_CFLAGS) $(EXIT_SRC)

$(HELLO_EXE): $(HELLO_SRC) $(EHLIBC_SRC) $(HEADERS)
	gcc -o $(HELLO_EXE) $(OUR_CFLAGS) $(HELLO_SRC)
	($(FILE) ./$(HELLO_EXE))
	(./$(HELLO_EXE) $(USER))

$(STAT_EXE): $(STAT_SRC) $(EHLIBC_SRC) $(HEADERS)
	gcc -o $(STAT_EXE) $(OUR_CFLAGS) $(STAT_SRC)

$(PUTS_EXE): $(PUTS_SRC) $(EHLIBC_SRC) $(HEADERS)
	gcc -o $(PUTS_EXE) $(OUR_CFLAGS) $(PUTS_SRC)

$(CTYPES_EXE): $(CTYPES_SRC) $(EHLIBC_SRC) $(HEADERS)
	gcc -o $(CTYPES_EXE) $(OUR_CFLAGS) $(CTYPES_SRC)

$(CHECKERED_ALLOC_FREE_EXE): $(CHECKERED_ALLOC_FREE_SRC) $(EHLIBC_SRC) \
		$(HEADERS)
	gcc -o $(CHECKERED_ALLOC_FREE_EXE) $(OUR_CFLAGS) \
		$(CHECKERED_ALLOC_FREE_SRC)

$(TEST_FGETC_EXE): $(TEST_FGETC_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_FGETC_EXE) $(OUR_CFLAGS) $(TEST_FGETC_SRC)

$(TEST_FILE_IO_ROUNDTRIP_EXE): $(TEST_FILE_IO_ROUNDTRIP_SRC) $(EHLIBC_SRC) \
		$(TEST_HEADERS)
	gcc -o $(TEST_FILE_IO_ROUNDTRIP_EXE) $(OUR_CFLAGS) \
		$(TEST_FILE_IO_ROUNDTRIP_SRC)

$(TEST_FFS_EXE): $(TEST_FFS_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_FFS_EXE) $(OUR_CFLAGS) $(TEST_FFS_SRC)

$(TEST_ISINF_EXE): $(TEST_ISINF_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_ISINF_EXE) $(OUR_CFLAGS) \
		-Wno-error=div-by-zero -Wno-div-by-zero \
		$(TEST_ISINF_SRC)

$(TEST_MEMCCPY_EXE): $(TEST_MEMCCPY_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_MEMCCPY_EXE) $(OUR_CFLAGS) $(TEST_MEMCCPY_SRC)

$(TEST_MEMCHR_EXE): $(TEST_MEMCHR_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_MEMCHR_EXE) $(OUR_CFLAGS) $(TEST_MEMCHR_SRC)

$(TEST_MEMCMP_EXE): $(TEST_MEMCMP_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_MEMCMP_EXE) $(OUR_CFLAGS) $(TEST_MEMCMP_SRC)

$(TEST_MEMCPY_EXE): $(TEST_MEMCPY_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_MEMCPY_EXE) $(OUR_CFLAGS) $(TEST_MEMCPY_SRC)

$(TEST_MEMMOVE_EXE): $(TEST_MEMMOVE_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_MEMMOVE_EXE) $(OUR_CFLAGS) $(TEST_MEMMOVE_SRC)

$(TEST_MEMSET_EXE): $(TEST_MEMSET_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_MEMSET_EXE) $(OUR_CFLAGS) $(TEST_MEMSET_SRC)

$(TEST_STRCAT_EXE): $(TEST_STRCAT_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRCAT_EXE) $(OUR_CFLAGS) $(TEST_STRCAT_SRC)

$(TEST_STRCASECMP_EXE): $(TEST_STRCASECMP_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRCASECMP_EXE) $(OUR_CFLAGS) $(TEST_STRCASECMP_SRC)

$(TEST_STRCHR_EXE): $(TEST_STRCHR_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRCHR_EXE) $(OUR_CFLAGS) $(TEST_STRCHR_SRC)

$(TEST_STRCPY_EXE): $(TEST_STRCPY_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRCPY_EXE) $(OUR_CFLAGS) $(TEST_STRCPY_SRC)

$(TEST_STRDUP_EXE): $(TEST_STRDUP_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRDUP_EXE) $(OUR_CFLAGS) $(TEST_STRDUP_SRC)

$(TEST_STRSPN_EXE): $(TEST_STRSPN_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRSPN_EXE) $(OUR_CFLAGS) $(TEST_STRSPN_SRC)

$(TEST_STRPBRK_EXE): $(TEST_STRPBRK_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRPBRK_EXE) $(OUR_CFLAGS) $(TEST_STRPBRK_SRC)

$(TEST_STRSTR_EXE): $(TEST_STRSTR_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRSTR_EXE) $(OUR_CFLAGS) $(TEST_STRSTR_SRC)

$(TEST_STRTOK_EXE): $(TEST_STRTOK_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRTOK_EXE) $(OUR_CFLAGS) $(TEST_STRTOK_SRC)

$(TEST_STRTOL_EXE): $(TEST_STRTOL_SRC) $(EHLIBC_SRC) $(TEST_HEADERS)
	gcc -o $(TEST_STRTOL_EXE) $(OUR_CFLAGS) $(TEST_STRTOL_SRC)

test: $(TESTS)
	./$(TEST_FILE_IO_ROUNDTRIP_EXE)
	./$(TEST_FGETC_EXE)
	./$(TEST_FFS_EXE)
	./$(TEST_ISINF_EXE)
	./$(TEST_MEMCCPY_EXE)
	./$(TEST_MEMCHR_EXE)
	./$(TEST_MEMCMP_EXE)
	./$(TEST_MEMCPY_EXE)
	./$(TEST_MEMMOVE_EXE)
	./$(TEST_MEMSET_EXE)
	./$(TEST_STRCASECMP_EXE)
	./$(TEST_STRCAT_EXE)
	./$(TEST_STRCHR_EXE)
	./$(TEST_STRCPY_EXE)
	./$(TEST_STRDUP_EXE)
	./$(TEST_STRSPN_EXE)
	./$(TEST_STRPBRK_EXE)
	./$(TEST_STRSTR_EXE)
	./$(TEST_STRTOK_EXE)
	./$(TEST_STRTOL_EXE)

demo: sanity

sanity: $(SANITY)
	./$(EXIT_EXE)
	./$(HELLO_EXE)
	./$(PUTS_EXE)
	./$(STAT_EXE) | hexdump
	./$(CHECKERED_ALLOC_FREE_EXE)

check: sanity test

tidy:
	patch -Np1 -i misc/pre-tidy.patch
	$(LINDENT) \
		-T FILE \
		-T dev_t \
		-T fpos64_t \
		-T fpos_t \
		-T imaxdiv_t \
		-T int16_t \
		-T int16_t \
		-T int32_t \
		-T int32_t \
		-T int64_t \
		-T int64_t \
		-T int8_t \
		-T int8_t \
		-T int_fast16_t \
		-T int_fast32_t \
		-T int_fast64_t \
		-T int_fast8_t \
		-T int_least16_t \
		-T int_least32_t \
		-T int_least64_t \
		-T int_least8_t \
		-T intmax_t \
		-T intptr_t \
		-T max_align_t \
		-T mbstate_t \
		-T mode_t \
		-T mode_t \
		-T off64_t \
		-T off_t \
		-T ptrdiff_t \
		-T size_t \
		-T size_t \
		-T ssize_t \
		-T ssize_t \
		-T sys_get_t \
		-T sys_mq_t \
		-T sys_name_t \
		-T sys_rt_t \
		-T sys_set_t \
		-T sys_t \
		-T syscall_slong_t \
		-T time_t \
		-T uint16_t \
		-T uint16_t \
		-T uint32_t \
		-T uint32_t \
		-T uint64_t \
		-T uint64_t \
		-T uint8_t \
		-T uint8_t \
		-T uint_fast16_t \
		-T uint_fast32_t \
		-T uint_fast64_t \
		-T uint_fast8_t \
		-T uint_least16_t \
		-T uint_least32_t \
		-T uint_least64_t \
		-T uint_least8_t \
		-T uintmax_t \
		-T uintptr_t \
		-T wchar_t \
		-T wctype_t \
		-T wint_t \
		-T eh_printf_context_s \
		-T dumb_alloc \
		`find src tests demo -name '*.h' -o -name '*.c'`
	patch -Rp1 -i misc/pre-tidy.patch


clean:
	rm -rfv `cat .gitignore | sed -e 's/#.*//'`
	pushd src && rm -rfv `cat ../.gitignore | sed -e 's/#.*//'`; popd
	pushd tests && rm -rfv `cat ../.gitignore | sed -e 's/#.*//'`; popd
