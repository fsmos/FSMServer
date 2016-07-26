rm FSM_E1CAS1.ko
rm FSMServerIODev.ko
rm FSM_SettingServer.ko
rm FSMClientProtocol.ko
rm FSM_DeviceProcess.ko
rm FSM_E1Device.ko
rm FSMFIFOAudioStream.ko
rm FSM_AudioStream.ko
rm FSM_StatisticServer.ko
rm FSM_PO06Device.ko
rm FSM_PO07Device.ko
rm FSM_PO08Device.ko
rm FSM_Commutator.ko
rm FSM_Crypt.ko
rm FSM_SkyNet.ko
rm FSM_ControlDeviceClass.ko
rm FSM_MN825Device.ko
rm FSM_MN921Device.ko
rm FSM_MN111Device.ko
rm FSM_Beep.ko
rm run.sh
rm FSM_SocialAnalytic.ko
rm FSM_GPIO.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSMClientProtocol.ko FSMClientProtocol.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/run.sh run.sh
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMSenPckg/Debug/FSMSendPack FSMSendPack
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_DeviceProcess.ko FSM_DeviceProcess.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_E1Device.ko FSM_E1Device.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_AudioStream.ko FSM_AudioStream.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_StatisticServer.ko FSM_StatisticServer.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_PO06Device.ko FSM_PO06Device.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_PO07Device.ko FSM_PO07Device.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_PO08Device.ko FSM_PO08Device.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_SettingServer.ko FSM_SettingServer.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSMFIFOAudioStream.ko FSMFIFOAudioStream.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_Commutator.ko FSM_Commutator.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_Crypt.ko FSM_Crypt.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_SkyNet.ko FSM_SkyNet.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSMServerIODev.ko FSMServerIODev.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_E1CAS1.ko FSM_E1CAS1.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_ControlDeviceClass.ko FSM_ControlDeviceClass.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_MN825Device.ko FSM_MN825Device.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_MN921Device.ko FSM_MN921Device.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_MN111Device.ko FSM_MN111Device.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_Beep.ko FSM_Beep.ko
scp gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/FSM_SocialAnalytic.ko FSM_SocialAnalytic.ko
scp gusenkovs@192.168.169.220:~/FSMCorefile/FSMKernelModules/FSM_GPIO.ko FSM_GPIO.ko
chmod +x FSMSendPack
chmod +x run.sh
./run.sh
scp runs.prog gusenkovs@192.168.169.220:~/FSMCoreFile/FSMKernelModules/runs.prog
