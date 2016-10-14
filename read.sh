rm  /home/gusenkovs/FSM_Core/*
scp gusenkovs@192.168.169.220:/home/gusenkovs/FSMCoreFile/FSMKernelModules/modules/* /home/gusenkovs/FSM_Core/
scp gusenkovs@192.168.169.220:/home/gusenkovs/FSMCoreFile/FSMKernelModules/run.sh /home/gusenkovs/FSM_Core/run.sh
chmod +x FSM_Core/run.sh
cd FSM_Core
./run.sh
