TARGET = read_dsk

OBJS = start.o main.o io.o rk.o

CC = pdp11-aout-gcc
AS = pdp11-aout-as
LD = pdp11-aout-ld 
PDP11TOOL = aout2simhbin

CFLAGS = -Wall -nostdinc -nostdlib -fno-builtin

all: $(TARGET).lda

$(TARGET).lda: $(TARGET).out
	$(PDP11TOOL) $(TARGET).out $(TARGET).lda

$(TARGET).out: $(OBJS)
	$(LD) -T ld.scr $(OBJS) -o $(TARGET).out

.c.o:
	$(CC) $(CFLAGS) -c $<

.s.o:
	$(CC) -c $<

clean:
	rm *.lda
	rm *.out
	rm *.o
