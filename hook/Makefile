KERNDIR := /lib/modules/`uname -r`/build
BUILD_DIR := $(shell pwd)
VERBOSE = 0

obj-m := syscall_replace.o
smallmod-objs := syscall_replace.o

all:
	make -C $(KERNDIR) SUBDIRS=$(BUILD_DIR) KBUILD_VERBOSE=$(VERBOSE) modules

clean:
	rm -f *.o
	rm -f *.ko
	rm -f *.mod.c
	rm -f *~
