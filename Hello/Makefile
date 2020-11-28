	obj-m := hello.o
	KERNELDIR = /lib/modules/$(shell uname -r)/build

pwd :=$(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

prepare:
	$(MAKE) -C $(KERNELDIR) M= $(PWD) modules_prepare

install:
	$(MAKE) -C $(KERNELDIR) M= $(PWD) modules_install

cleam:
	$(MAKE) -C$(KERNELDIR) M= $(PWD) clean
