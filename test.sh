#! /bin/bash

echo "config has to be set up before testing"

# install
./install.sh --DESTDIR=/tmp/usr/local/bin

# test
systemctl restart udevmon
sleep 20
systemctl stop udevmon
systemctl disable udevmon

