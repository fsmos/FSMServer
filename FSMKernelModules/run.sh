rmmod FSM_SettingServer.ko
rmmod FSM_StatisticServer.ko
rmmod FSM_PO06Device.ko
rmmod FSM_E1Device.ko
rmmod FSM_AudioStream.ko
rmmod FSMClientProtocol.ko
rmmod FSM_DeviceProcess.ko


insmod FSM_DeviceProcess.ko
insmod FSMClientProtocol.ko
insmod FSM_AudioStream.ko
insmod FSM_E1Device.ko
insmod FSM_PO06Device.ko
insmod FSM_StatisticServer.ko
insmod FSM_SettingServer.ko
./FSMSendPack lo 1
./FSMSendPack lo 3
./FSMSendPack lo 4
//./FSMSendPack lo 2
