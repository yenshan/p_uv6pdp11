
TARGET = read_blk

OBJS = start.o main.o

CC = pdp11-aout-gcc
AS = pdp11-aout-as

CFLAGS = -Wall -nostdinc -nostdlib -fno-builtin
CFLAGS += -std=c99

all: $(TARGET).lda

$(TARGET).lda: $(TARGET).out
	aout2simhbin $(TARGET).out $(TARGET).lda

$(TARGET).out: $(OBJS)
	pdp11-aout-ld -T ld.scr $(OBJS) -o $(TARGET).out

.c.o:
	$(CC) $(CFLAGS) -c $<
	$(CC) -S $(CFLAGS) -c $<

.s.o:
	$(CC) -c $<

clean:
	rm *.lda
	rm *.out
	rm *.o
