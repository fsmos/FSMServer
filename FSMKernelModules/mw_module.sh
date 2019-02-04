rm ../fsm_mn401_firmware/fsmcore/lib/modules/4.15.15-fsm/kernel/fsm/*
cp *.ko ../fsm_mn401_firmware/fsmcore/lib/modules/4.15.15-fsm/kernel/fsm
cd ../fsm_mn401_firmware
rm fsmcore.deb
./build_fsmcore.sh
rm ../mn401_firmware.deb
cp fsmcore.deb ../mn401_firmware.deb