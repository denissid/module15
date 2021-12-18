obj-m += keylog.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

load:
	sudo insmod keylog.ko
	sudo dmesg -c

unload:
	sudo rmmod keylog.ko
	sudo dmesg -c
