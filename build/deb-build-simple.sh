#!/bin/bash
# A very lame binary-level DEB package builder ... :-/
# Part of the Xemu project: https://github.com/lgblgblgb/xemu
# (C)2016-2021 LGB Gabor Lenart

PROJECT="xemu"
DEPENDENCY="libsdl2-2.0-0 (>= 2.0.4), libc6 (>= 2.15), `dpkg -s libreadline-dev | grep ^Depends: | grep -o 'libreadline[0-9]*'`, libgtk-3-0 (>= 3.18)"
AUTHOR="Gábor Lénárt <lgblgblgb@gmail.com>"
WEBSITE="https://github.com/lgblgblgb/xemu"
BUGSITE="https://github.com/lgblgblgb/xemu/issues"
ARCH=`dpkg --print-architecture`
BINDIRREAL="/usr/bin"
DATADIRREAL="/usr/share/xemu"

cd `dirname $0` || exit 1

VERSION="`cat ../build/objs/cdate.data`"
ROOT=".dist/${PROJECT}_${VERSION}"
BINDIR="${ROOT}${BINDIRREAL}"
DATADIR="${ROOT}${DATADIRREAL}"
DEB="${PROJECT}_${VERSION}_${ARCH}.deb"

echo "* Cur.dir.  : `pwd`"
echo "* Arch.     : ${ARCH}"
echo "* Version   : ${VERSION}"
echo "* Build root: ${ROOT}"
echo "* Dependency: ${DEPENDENCY}"

rm -fr .dist || exit 1

mkdir -p $BINDIR $DATADIR $ROOT/DEBIAN $ROOT/usr/share/doc/$PROJECT $ROOT/usr/share/applications $ROOT/usr/share/pixmaps || exit 1

cp xemu-48x48.xpm $ROOT/usr/share/pixmaps/xemu-48x48.xpm

for a in bin/*.native ; do
	b="$BINDIR/xemu-`basename $a .native`"
	echo "Adding project binary: $b"
	cp $a $b
	strip $b
done

for a in ../targets/*/Makefile ; do
	if [ -s $a ]; then
		prgtarget="`sed -n 's/^PRG_TARGET[\t ]*=[\t ]*//p' $a`"
		machine="`sed -n 's/^EMU_DESCRIPTION[\t ]*=[\t ]*//p' $a`"
		if [ "$prgtarget" != "" -a "$machine" != "" -a -x "bin/$prgtarget.native" ]; then
			cat xemu.desktop | sed "s/%machine/$machine/g;s/%binary/xemu-$prgtarget/g" > $ROOT/usr/share/applications/xemu-$prgtarget.desktop
		fi
	fi
done

gzip -9 < ../LICENSE > $ROOT/usr/share/doc/$PROJECT/COPYING.gz
gzip -9 < ../README.md > $ROOT/usr/share/doc/$PROJECT/README.gz
echo "Ugly, direct binary build, without source package :(" > $ROOT/usr/share/doc/$PROJECT/README.Debian
git log --max-count=100 | gzip -9 > $ROOT/usr/share/doc/$PROJECT/changelog.Debian.gz
echo "(C) $AUTHOR" > $ROOT/usr/share/doc/$PROJECT/copyright
echo "$WEBSITE" >> $ROOT/usr/share/doc/$PROJECT/copyright
echo >> $ROOT/usr/share/doc/$PROJECT/copyright
cat ../LICENSE >> $ROOT/usr/share/doc/$PROJECT/copyright
cat ../AUTHORS >> $ROOT/usr/share/doc/$PROJECT/AUTHORS

# I disable this, since it seems it's a legality problem to ship the package with a helper inside which downloads ROM images copyrighted by some angry companies ...
## awk -vromdir=$DATADIRREAL/ 'BEGIN { print "#!/bin/sh" ; print "mkdir -p " romdir " || exit $?" } END { print "exit 0" } NF == 3 && $1 ~ /^[a-zA-Z0-9]/ { print "test -s " romdir $1 " || { rm -f " romdir $1 ".tmp && wget -O " romdir $1 ".tmp " $2 " && mv " romdir $1 ".tmp " romdir $1 "; } || exit $?" }' ../rom/rom-fetch-list.txt > $BINDIR/xemu-download-data

SIZE="`find $ROOT -type f -exec stat -c '%s' {} \; | awk '{ s += $1 } END { print int(s / 1024) }'`"

echo "Package: $PROJECT
Version: $VERSION
Section: otherosfs
Priority: optional
Architecture: $ARCH
Depends: $DEPENDENCY
Maintainer: $AUTHOR
Installed-Size: $SIZE
Description: Collection of software emulations of some (mainly 8 bit) computers.
  X-Emulators (Xemu) is a kind of collection of software emulators
  targeting various computers, including the quite rare Commodore LCD,
  Commodore 65, and MEGA65 as well. Xemu uses SDL2, and can run on Linux/UNIX,
  Windows and MacOS, also there is the limited possibility to use it within a
  web-browser with the help of the Emscripten compiler.
Homepage: $WEBSITE
Bugs: $BUGSITE
Original-Maintainer: $AUTHOR" > $ROOT/DEBIAN/control

find $ROOT -type d -exec chmod u-s,g-s,g-w,o-w,u+rwx,g+rx,o+rx {} \;
find $ROOT -type f -exec chmod 0644 {} \;
chmod 0755 $BINDIR/*
touch $DATADIR/.placeholder

fakeroot dpkg-deb --build $ROOT || exit 1

mv .dist/*.deb bin/$DEB
rm -fr .dist

cd bin
echo "Current directory now: `pwd`"

ls -l $DEB || exit 1

rm -f *.rpm
fakeroot alien -r $DEB || true
ls -l *.rpm || true
echo "!! If you see an error with 'alien' and/or anything with RPM files, do not panic."
echo "!! It is only an ugly extra to convert DEB package to RPM, so you can have an RPM"
echo "!! package as well. Which may fail anyway on an RPM based distro, since dependency"
echo "!! problems."

exit 0
