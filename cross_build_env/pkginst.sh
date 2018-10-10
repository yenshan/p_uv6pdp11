#!/usr/bin/env bash

download(){
	URL=$1
	FILE=`basename $URL`
	if [ ! -e $FILE ] ;then
		curl -O $URL
	fi
	echo $FILE
}
expand(){
	FILE=$1
	case $FILE in
		*\.gz)
			tar xfz $FILE
			;;
		*\.bz2)
			tar xfj $FILE
			;;
	esac
	echo $FILE | sed -e "s/.tar.*//g"
}
mkinst(){
	DIR=$1
	FLGS=$2
	OPTS=$3
	pushd $DIR
	mkdir build; cd build
	echo "configure ..."
	CFLAGS=$FLGS ../configure $OPTS
	echo "make ..."
	make
	sudo make install
	popd
}

FILE=`download $1`
DIR=`expand $FILE`
mkinst $DIR "$2" "$3"

