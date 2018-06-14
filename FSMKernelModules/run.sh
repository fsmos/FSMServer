rmmod FSM_ControlPower.ko
rmmod FSM_ControlDeviceClass.ko
rmmod FSM_SocialAnalytic.ko
rmmod FSM_MN825Device.ko
rmmod FSM_MN921Device.ko
rmmod FSM_MN111Device.ko
rmmod FSM_PO06Device.ko
rmmod FSM_PO07Device.ko
rmmod FSM_PO08Device.ko
rmmod FSM_CCKControl.ko
rmmod FSM_SkyNet.ko
rmmod FSM_SettingServer.ko
rmmod FSM_StatisticServer.ko
rmmod FSM_E1Device.ko
rmmod FSM_E1CAS1.ko
rmmod FSM_Commutator.ko
rmmod FSMFIFOAudioStream.ko
rmmod FSM_AudioStream.ko
rmmod FSM_Crypt.ko
rmmod FSMClientProtocol.ko
rmmod FSMTransportP.ko
rmmod FSMServerIODev.ko
rmmod FSM_GPIO.ko
rmmod FSMTreeSetting.ko
rmmod FSM_Flash.ko
rmmod FSM_DeviceProcess.ko
rmmod FSM_Beep.ko
rmmod FSM_CRC.ko
rmmod FSM_Filter.ko
rmmod FSM_ADConsole.ko

path=""
a+=""

insmod FSM_ADConsole.ko
a+="add-symbol-file $path FSM_ADConsole.ko $(cat /sys/module/FSM_ADConsole/sections/.text) -s .bss $(cat /sys/module/FSM_ADConsole/sections/.bss)\n"

insmod FSM_Filter.ko
a+="add-symbol-file $path FSM_Filter.ko $(cat /sys/module/FSM_Filter/sections/.text) -s .bss $(cat /sys/module/FSM_Filter/sections/.bss)\n"

insmod FSM_Beep.ko
a+="add-symbol-file $path FSM_Beep.ko $(cat /sys/module/FSM_Beep/sections/.text) -s .bss $(cat /sys/module/FSM_Beep/sections/.bss)\n"

insmod FSM_CRC.ko
a+="add-symbol-file $path FSM_CRC.ko $(cat /sys/module/FSM_CRC/sections/.text) -s .bss $(cat /sys/module/FSM_CRC/sections/.bss)\n"

insmod FSM_DeviceProcess.ko
a+="add-symbol-file $path FSM_DeviceProcess.ko $(cat /sys/module/FSM_DeviceProcess/sections/.text) -s .bss $(cat /sys/module/FSM_DeviceProcess/sections/.bss)  \n"

insmod FSM_Flash.ko
a+="add-symbol-file $path FSM_Flash.ko $(cat /sys/module/FSM_Flash/sections/.text) -s .bss $(cat /sys/module/FSM_Flash/sections/.bss)  \n"

insmod FSMTreeSetting.ko
a+="add-symbol-file $path FSMTreeSetting.ko $(cat /sys/module/FSMTreeSetting/sections/.text) -s .bss $(cat /sys/module/FSMTreeSetting/sections/.bss)\n"

insmod FSM_GPIO.ko
a+="add-symbol-file $path FSM_GPIO.ko $(cat /sys/module/FSM_GPIO/sections/.text) -s .bss $(cat /sys/module/FSM_GPIO/sections/.bss)\n"

insmod FSMClientProtocol.ko
a+="add-symbol-file $path FSMClientProtocol.ko $(cat /sys/module/FSMClientProtocol/sections/.text) -s .bss $(cat /sys/module/FSMClientProtocol/sections/.bss) \n"

insmod FSMTransportP.ko
a+="add-symbol-file $path FSMTransportP.ko $(cat /sys/module/FSMTransportP/sections/.text) -s .bss $(cat /sys/module/FSMTransportP/sections/.bss)\n"

insmod FSMServerIODev.ko
a+="add-symbol-file $path FSMServerIODev.ko $(cat /sys/module/FSMServerIODev/sections/.text) -s .bss $(cat /sys/module/FSMServerIODev/sections/.bss) \n"

insmod FSM_AudioStream.ko
a+="add-symbol-file $path FSM_AudioStream.ko $(cat /sys/module/FSM_AudioStream/sections/.text) -s .bss $(cat /sys/module/FSM_AudioStream/sections/.bss) \n"

insmod FSMFIFOAudioStream.ko
a+="add-symbol-file $path FSMFIFOAudioStream.ko $(cat /sys/module/FSMFIFOAudioStream/sections/.text) -s .bss $(cat /sys/module/FSMFIFOAudioStream/sections/.bss)\n"

insmod FSM_Commutator.ko
a+="add-symbol-file $path FSM_Commutator.ko $(cat /sys/module/FSM_Commutator/sections/.text) -s .bss $(cat /sys/module/FSM_Commutator/sections/.bss)\n"

insmod FSM_CCKControl.ko
a+="add-symbol-file $path FSM_CCKControl.ko $(cat /sys/module/FSM_CCKControl/sections/.text) -s .bss $(cat /sys/module/FSM_CCKControl/sections/.bss)\n"

insmod FSM_E1CAS1.ko
a+="add-symbol-file $path FSM_E1CAS1.ko $(cat /sys/module/FSM_E1CAS1/sections/.text) -s .bss $(cat /sys/module/FSM_E1CAS1/sections/.bss)\n"

insmod FSM_E1Device.ko
a+="add-symbol-file $path FSM_E1Device.ko $(cat /sys/module/FSM_E1Device/sections/.text) -s .bss $(cat /sys/module/FSM_E1Device/sections/.bss) \n"

insmod FSM_PO06Device.ko
a+="add-symbol-file $path FSM_PO06Device.ko $(cat /sys/module/FSM_PO06Device/sections/.text) -s .bss $(cat /sys/module/FSM_PO06Device/sections/.bss)\n"

insmod FSM_PO07Device.ko
a+="add-symbol-file $path FSM_PO07Device.ko $(cat /sys/module/FSM_PO07Device/sections/.text) -s .bss $(cat /sys/module/FSM_PO07Device/sections/.bss)\n"

insmod FSM_PO08Device.ko
a+="add-symbol-file $path FSM_PO08Device.ko $(cat /sys/module/FSM_PO08Device/sections/.text) -s .bss $(cat /sys/module/FSM_PO08Device/sections/.bss)\n"

insmod FSM_StatisticServer.ko
a+="add-symbol-file $path FSM_StatisticServer.ko $(cat /sys/module/FSM_StatisticServer/sections/.text) -s .bss $(cat /sys/module/FSM_StatisticServer/sections/.bss)\n"

insmod FSM_SettingServer.ko
a+="add-symbol-file $path FSM_SettingServer.ko $(cat /sys/module/FSM_SettingServer/sections/.text) -s .bss $(cat /sys/module/FSM_SettingServer/sections/.bss)\n"

insmod FSM_SkyNet.ko
a+="add-symbol-file $path FSM_SkyNet.ko $(cat /sys/module/FSM_SkyNet/sections/.text) -s .bss $(cat /sys/module/FSM_SkyNet/sections/.bss)\n"

insmod FSM_ControlDeviceClass.ko
a+="add-symbol-file $path FSM_ControlDeviceClass.ko $(cat /sys/module/FSM_ControlDeviceClass/sections/.text) -s .bss $(cat /sys/module/FSM_ControlDeviceClass/sections/.bss)\n"

insmod FSM_Crypt.ko
a+="add-symbol-file $path FSM_Crypt.ko $(cat /sys/module/FSM_Crypt/sections/.text) -s .bss $(cat /sys/module/FSM_Crypt/sections/.bss)\n"

insmod FSM_MN825Device.ko
a+="add-symbol-file $path FSM_MN825Device.ko $(cat /sys/module/FSM_MN825Device/sections/.text) -s .bss $(cat /sys/module/FSM_MN825Device/sections/.bss)\n"

insmod FSM_MN921Device.ko
a+="add-symbol-file $path FSM_MN921Device.ko $(cat /sys/module/FSM_MN921Device/sections/.text) -s .bss $(cat /sys/module/FSM_MN921Device/sections/.bss)\n"

insmod FSM_MN111Device.ko
a+="add-symbol-file $path FSM_MN111Device.ko $(cat /sys/module/FSM_MN111Device/sections/.text) -s .bss $(cat /sys/module/FSM_MN111Device/sections/.bss)\n"

insmod FSM_SocialAnalytic.ko
a+="add-symbol-file $path FSM_SocialAnalytic.ko $(cat /sys/module/FSM_SocialAnalytic/sections/.text) -s .bss $(cat /sys/module/FSM_SocialAnalytic/sections/.bss)\n"

insmod FSM_ControlPower.ko
a+="add-symbol-file $path FSM_ControlPower.ko $(cat /sys/module/FSM_ControlPower/sections/.text) -s .bss $(cat /sys/module/FSM_ControlPower/sections/.bss)\n"

insmod FSM_UDPModule.ko
a+="add-symbol-file $path FSM_ControlPower.ko $(cat /sys/module/FSM_UDPModule/sections/.text) -s .bss $(cat /sys/module/FSM_UDPModule/sections/.bss)\n"



//./FSMSendPack 
echo -e $a > runs.prog
