dpkg --purge libfsmctl
rm -r libfsmctl/usr/include/FSM
cp -rp FSMHeader/FSM libfsmctl/usr/include/FSM
fakeroot dpkg-deb --build libfsmctl
dpkg -i libfsmctl.deb
