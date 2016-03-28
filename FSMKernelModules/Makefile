KDIR = /usr/src/linux-source-4.2.0/
PWD = $(shell pwd) 
TARGET1 =FSMClientProtocol
TARGET2 =FSM_DeviceProcess
TARGET3 =FSM_E1Device
TARGET4 =FSM_AudioStream

obj-m   += $(TARGET1).o
obj-m   += ${TARGET2}.o
obj-m   += ${TARGET3}.o
obj-m   += ${TARGET4}.o
all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
