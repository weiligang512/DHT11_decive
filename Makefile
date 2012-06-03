obj-m := dht11.o

KERNELDIR := /home/zhouligen/ok6410/linux-3.0.1

$(PWD) = $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	rm -rf *.o *.mod.c *.order *.symvers

.PHONY: clean

clean:
	rm -rf *.ko



