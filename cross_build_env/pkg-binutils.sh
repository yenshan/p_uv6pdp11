 #!/usr/bin/env sh
 ./pkginst.sh "http://www.ring.gr.jp/archives/GNU/binutils/binutils-2.31.tar.bz2" \
	 "-Wno-error=deprecated-declarations" \
	 "--target=pdp11-aout --disable-nls --prefix=/usr/local/pdp11-aout"


