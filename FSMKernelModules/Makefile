KDIR = /usr/src/linux-source-4.15.0/
PWD = $(shell pwd) 
TARGET1 =FSMClientProtocol
TARGET2 =FSM_DeviceProcess
TARGET3 =FSM_E1Device
TARGET4 =FSM_AudioStream
TARGET6 =FSM_StatisticServer
TARGET7 =FSM_PO06Device
TARGET8 =FSM_Crypt
TARGET9 =FSM_SettingServer
TARGET10 =FSM_Commutator
TARGET11 =FSMFIFOAudioStream
TARGET12 =FSM_SkyNet
TARGET13 =FSM_E1CAS1
TARGET14 =FSMServerIODev
TARGET15 =FSM_Client
TARGET16 =FSM_ControlDevice
TARGET17 =FSM_ControlDeviceClass
TARGET18 =FSM_StatisticClient
TARGET19 =FSM_SettingClient
TARGET20 =FSM_SendSignalToPipe
TARGET21 =FSMClientIOCtl
TARGET22 =FSM_MN825Device
TARGET23 =FSM_Beep
TARGET24 =FSM_MN111Device
TARGET25 =FSM_MN921Device
TARGET26 =FSM_PO07Device
TARGET27 =FSM_PO08Device
TARGET28 =FSM_SocialAnalytic
TARGET29 =FSM_GPIO
TARGET30 =FSM_CCKControl
TARGET31 =FSMTreeSetting
TARGET32 =FSM_Flash
TARGET33 =FSM_CRC
TARGET34 =FSM_ControlPower
TARGET35 =FSM_Filter
TARGET36 =FSMStatisticCtl
TARGET37 =FSMTransportP
TARGET38 =FSM_ADConsole
TARGET39 =FSM_TCPServer

TARGET41 =FSM_CCKConfig

obj-m   += $(TARGET1).o
obj-m   += ${TARGET2}.o
obj-m   += ${TARGET3}.o
obj-m   += ${TARGET4}.o
obj-m   += ${TARGET6}.o
obj-m   += ${TARGET7}.o
obj-m   += ${TARGET8}.o
obj-m   += ${TARGET9}.o
obj-m   += ${TARGET10}.o
obj-m   += ${TARGET11}.o
obj-m   += ${TARGET12}.o
obj-m   += ${TARGET13}.o
obj-m   += ${TARGET14}.o
obj-m   += ${TARGET15}.o
obj-m   += ${TARGET16}.o
obj-m   += ${TARGET17}.o
obj-m   += ${TARGET18}.o
obj-m   += ${TARGET19}.o
obj-m   += ${TARGET20}.o
obj-m   += ${TARGET21}.o
obj-m   += ${TARGET22}.o
obj-m   += ${TARGET23}.o
obj-m   += ${TARGET24}.o
obj-m   += ${TARGET25}.o
obj-m   += ${TARGET26}.o
obj-m   += ${TARGET27}.o
obj-m   += ${TARGET28}.o
obj-m   += ${TARGET29}.o
obj-m   += ${TARGET30}.o
obj-m   += ${TARGET31}.o
obj-m   += ${TARGET32}.o
obj-m   += ${TARGET33}.o
obj-m   += ${TARGET34}.o
obj-m   += ${TARGET35}.o
obj-m   += ${TARGET36}.o
obj-m   += ${TARGET37}.o
obj-m   += ${TARGET38}.o
obj-m   += ${TARGET39}.o
obj-m   += ${TARGET41}.o

all:
	make -C $(KDIR) M=$(PWD) modules
	sh mw_dm.sh
	
clean:
	make -C $(KDIR) M=$(PWD) clean
	
module:
	make -C $(KDIR) M=$(PWD) modules
	sh mw_module.sh
	make -C $(KDIR) M=$(PWD) clean
