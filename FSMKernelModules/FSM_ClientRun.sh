
rmmod FSM_StatisticClient.ko
rmmod FSM_SettingClient.ko
rmmod FSM_ControlDevice.ko
rmmod FSM_Client.ko
rmmod FSM_SendSignalToPipe.ko
rmmod FSMClientIOCtl.ko

insmod FSMClientIOCtl.ko
insmod FSM_SendSignalToPipe.ko
insmod FSM_Client.ko
insmod FSM_ControlDevice.ko
insmod FSM_SettingClient.ko
insmod FSM_StatisticClient.ko
