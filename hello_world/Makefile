all: 
	gcc aout2simhbin.c -o aout2simhbin -std=c99
	chmod +x ./aout2simhbin
	pdp11-aout-gcc -c hello.c -o hello.o
	pdp11-aout-as start.S -o start.o
	pdp11-aout-ld -T ld.scr start.o hello.o -o hello.out
	./aout2simhbin hello.out hello.lda

clean:
	rm *.lda
	rm *.out
	rm *.o
	rm aout2simhbin
