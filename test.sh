#! /bin/bash

echo "config has to be set up before testing"

# install
./install.sh

# test
systemctl restart udevmon
sleep 20
systemctl stop udevmon
systemctl disable udevmon

