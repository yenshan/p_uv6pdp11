#!/usr/bin/env sh
./pkginst.sh "http://www.ring.gr.jp/archives/GNU/gcc/gcc-8.2.0/gcc-8.2.0.tar.gz" \
	"" \
	"--target=pdp11-aout \
	--disable-nls \
	--disable-threads \
	--disable-shared \
	--disable-libssp \
	--enable-languages=c \
	--with-gmp=/usr/local/gmp \
	--with-mpfr=/usr/local/mpfr \
	--with-mpc=/usr/local/mpc \
	--prefix=/usr/local/pdp11-aout"
