KDIR = /usr/src/linux-source-4.2.0/
PWD = $(shell pwd) 
TARGET1 =FSMClientProtocol
obj-m   += $(TARGET1).o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean