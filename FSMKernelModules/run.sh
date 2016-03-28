rmmod FSM_E1Device.ko
rmmod FSMClientProtocol.ko
rmmod FSM_AudioStream.ko
rmmod FSM_DeviceProcess.ko


insmod FSM_DeviceProcess.ko
insmod FSM_AudioStream.ko
insmod FSMClientProtocol.ko
insmod FSM_E1Device.ko
./FSMSendPack lo 1
./FSMSendPack lo 3
./FSMSendPack lo 2
