rmmod FSM_E1Device.ko
rmmod FSMClientProtocol.ko
rmmod FSM_DeviceProcess.ko


insmod FSM_DeviceProcess.ko
insmod FSMClientProtocol.ko
insmod FSM_E1Device.ko
./FSMSendPack lo
