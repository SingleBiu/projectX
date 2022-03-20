#KERNELRELEASE这个变量，在内核源码的根目录下面的Makefile会初始化
ifeq ($(KERNELRELEASE),)

KERN_DIR := /home/china/6818GEC/kernel

#在Makefile中可以调用shell的命令，调用方法如下:
# $(shell  shell命令) -> 整个这个表达式，表示调用该shell命令的输出结果
PWD := $(shell pwd)

CROSS_COMPILE := /home/china/6818GEC/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-

modules:
	make -C $(KERN_DIR)  M=$(PWD) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE)  modules
clean:
	rm -rf *.o
	rm -rf  modules.order  .tmp_versions *.ko  Module.symvers
	rm -f  *.cmd .*.cmd  *.mod.c

else
	
	obj-m += drv_firedetect.o

endif