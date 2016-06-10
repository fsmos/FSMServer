rmmod FSM_SkyNet.ko
rmmod FSM_SettingServer.ko
rmmod FSM_StatisticServer.ko
rmmod FSM_PO06Device.ko
rmmod FSM_E1Device.ko
rmmod FSM_E1CAS1.ko
rmmod FSM_Commutator.ko
rmmod FSMFIFOAudioStream.ko
rmmod FSM_AudioStream.ko
rmmod FSM_Crypt.ko
rmmod FSMClientProtocol.ko
rmmod FSM_DeviceProcess.ko

path=""

insmod FSM_DeviceProcess.ko
a+=""
a+="add-symbol-file $path FSM_DeviceProcess.ko $(cat /sys/module/FSM_DeviceProcess/sections/.text) -s .bss $(cat /sys/module/FSM_DeviceProcess/sections/.bss)  \n"

insmod FSMClientProtocol.ko
a+="add-symbol-file $path FSMClientProtocol.ko $(cat /sys/module/FSMClientProtocol/sections/.text) -s .bss $(cat /sys/module/FSMClientProtocol/sections/.bss) \n"

insmod FSM_AudioStream.ko
a+="add-symbol-file $path FSM_AudioStream.ko $(cat /sys/module/FSM_AudioStream/sections/.text) -s .bss $(cat /sys/module/FSM_AudioStream/sections/.bss) \n"

insmod FSMFIFOAudioStream.ko
a+="add-symbol-file $path FSMFIFOAudioStream.ko $(cat /sys/module/FSMFIFOAudioStream/sections/.text) -s .bss $(cat /sys/module/FSMFIFOAudioStream/sections/.bss)\n"

insmod FSM_Commutator.ko
a+="add-symbol-file $path FSM_Commutator.ko $(cat /sys/module/FSM_Commutator/sections/.text) -s .bss $(cat /sys/module/FSM_Commutator/sections/.bss)\n"

insmod FSM_E1CAS1.ko
a+="add-symbol-file $path FSM_E1CAS1.ko $(cat /sys/module/FSM_E1CAS1/sections/.text) -s .bss $(cat /sys/module/FSM_E1CAS1/sections/.bss)\n"

insmod FSM_E1Device.ko
a+="add-symbol-file $path FSM_E1Device.ko $(cat /sys/module/FSM_E1Device/sections/.text) -s .bss $(cat /sys/module/FSM_E1Device/sections/.bss) \n"

insmod FSM_PO06Device.ko
a+="add-symbol-file $path FSM_PO06Device.ko $(cat /sys/module/FSM_PO06Device/sections/.text) -s .bss $(cat /sys/module/FSM_PO06Device/sections/.bss)\n"

insmod FSM_StatisticServer.ko
a+="add-symbol-file $path FSM_StatisticServer.ko $(cat /sys/module/FSM_StatisticServer/sections/.text) -s .bss $(cat /sys/module/FSM_StatisticServer/sections/.bss)\n"

insmod FSM_SettingServer.ko
a+="add-symbol-file $path FSM_SettingServer.ko $(cat /sys/module/FSM_SettingServer/sections/.text) -s .bss $(cat /sys/module/FSM_SettingServer/sections/.bss)\n"

insmod FSM_SkyNet.ko
a+="add-symbol-file $path FSM_SkyNet.ko $(cat /sys/module/FSM_SkyNet/sections/.text) -s .bss $(cat /sys/module/FSM_SkyNet/sections/.bss)\n"

//insmod FSM_Crypt.ko
//a+="add-symbol-file $path FSM_Crypt.ko $(cat /sys/module/FSM_Crypt/sections/.text) -s .bss $(cat /sys/module/FSM_Crypt/sections/.bss)\n"

//./FSMSendPack lo 1
//./FSMSendPack lo 3
//./FSMSendPack lo 4
//./FSMSendPack lo 2
echo -e $a > runs.prog
