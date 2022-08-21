# Maintainer: Calvin Reu <j.calvin.reu@protonmail.com>
# License: MIT
# Repository: https://gitlab.com/input-configuration/kbdmod

pkgname=kbdmod
pkgver=0.1.0
pkgrel=1
epoch=
pkgdesc="modify your keyboard functionality with multi functions per key"
arch=('any')
url="https://gitlab.com/input-configuration/$pkgname"
license=('MIT')
groups=()
depends=(libevdev yaml-cpp interception-tools)
makedepends=(cmake)
checkdepends=(make)
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelo=
source=("https://gitlab.com/input-configuration/$pkgname/-/archive/v$pkgver/kbdmod-v$pkgver.tar.gz")
noextract=()
sha256sums=(b5d564eccbc1a63db85fbb98cb4335c5d5c96b81521a1c080d79a3068f397d04)
validpgpkeys=()

build() {
	cd "$pkgname-v$pkgver"
	mkdir -p build
	cd build
	cmake .. -DCMAKE_BUILD_TYPE=Release
	make -j 8
}

check() {
	cd "$pkgname-v$pkgver/build"
	make -k cmake_check_build_system
}

package() {
	cd "$pkgname-v$pkgver/build"
	cp kbdmod.bin "$pkgdir/kbdmod"
}
