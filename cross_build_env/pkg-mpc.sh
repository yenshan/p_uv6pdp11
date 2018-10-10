#!/usr/bin/env sh
./pkginst.sh "http://www.ring.gr.jp/archives/GNU/mpc/mpc-1.1.0.tar.gz" \
	"" \
	"--prefix=/usr/local/mpc --with-gmp=/usr/local/gmp --with-mpfr=/usr/local/mpfr"
