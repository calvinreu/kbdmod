#! /bin/bash

# get the path to this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ../$DIR
# install
./install.sh --DESTDIR=/tmp

cd $DIR
# install the test config
echo "replacing config with test config"
mkdir udevmon
mv /etc/interception/udevmon.d/* udevmon/
cp udevmon.yaml /etc/interception/udevmon.d/test.yaml
cp manual_testing.yaml /tmp/kbdmod_test.yaml

# test
echo "starting test"
systemctl restart udevmon
sleep 20
systemctl stop udevmon


# clean up
echo "reverting changes"
cp udevmon/* /etc/interception/udevmon.d
rm -f /etc/interception/udevmon.d/test.yaml
rm -rf udevmon
