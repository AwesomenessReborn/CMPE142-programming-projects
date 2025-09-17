# Makefile (Temporarily modified for Part II)

obj-m += simple.o
# obj-m += jiffies_module.o
# obj-m += seconds_module.o

# By default, KERN_DIR points to the headers for the running kernel.
# You can override this on the command line. E.g., make KERN_DIR=/path/to/headers
KERN_DIR ?= /lib/modules/$(shell uname -r)

all:
	make -C $(KERN_DIR)/build M=$(PWD) modules

clean:
	make -C $(KERN_DIR)/build M=$(PWD) clean