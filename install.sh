#! /bin/bash

# loop parameters
for i in "$@"; do
	case $i in
		-h|--help)
			echo "Usage: install.sh [OPTION]..."
			echo "Install the project"
			echo "  -h, --help              display this help and exit"
			echo "  --DESTDIR=DIR           install to DIR"
			exit 0
			;;
		--DESTDIR=*)
			DESTDIR="${i#*=}"
			shift
			;;
	esac
done

# check if DESTDIR is set
if [ -z $DESTDIR ]; then
	DESTDIR="/usr/local/bin"
fi

# build
mkdir -p build
cd build
cmake ..
make -j 8
cd ../

mkdir -p $DESTDIR
cp -f build/keyboard_modify.bin $DESTDIR/keyboard_modify
chmod 755 $DESTDIR/keyboard_modify

