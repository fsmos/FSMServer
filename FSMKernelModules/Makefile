KDIR = /usr/src/linux-source-4.2.0/
PWD = $(shell pwd) 
TARGET1 =FSMClientProtocol
TARGET2 =FSM_DeviceProcess
TARGET3 =FSM_E1Device
TARGET4 =FSM_AudioStream
TARGET5 =FSM_ClientModule
TARGET6 =FSM_StatisticServer
TARGET7 =FSM_PO06Device
TARGET8 =FSM_Crypt
TARGET9 =FSM_SettingServer
TARGET10 =FSM_Commutator
TARGET11 =FSMFIFOAudioStream
TARGET12 =FSM_SkyNet
TARGET13 =FSM_E1CAS1

obj-m   += $(TARGET1).o
obj-m   += ${TARGET2}.o
obj-m   += ${TARGET3}.o
obj-m   += ${TARGET4}.o
obj-m   += ${TARGET5}.o
obj-m   += ${TARGET6}.o
obj-m   += ${TARGET7}.o
obj-m   += ${TARGET8}.o
obj-m   += ${TARGET9}.o
obj-m   += ${TARGET10}.o
obj-m   += ${TARGET11}.o
obj-m   += ${TARGET12}.o
obj-m   += ${TARGET13}.o


all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
