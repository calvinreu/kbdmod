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
	DESTDIR="/usr/bin"
fi

# get package version
VERSION=$(grep pkgver PKGBUILD | cut -d "=" -f 2)

# build
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -Dversion="$VERSION"
make -j 8
cd ../

mkdir -p $DESTDIR
cp -f build/kbdmod.bin $DESTDIR/kbdmod
chmod 755 $DESTDIR/kbdmod
echo "kbdmod installed to $DESTDIR/kbdmod"

